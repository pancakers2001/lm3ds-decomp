#include "format_arithmetic.h"

uint64_t divmod_u64_by_10(uint64_t value, uint32_t *remainder)
{
    *remainder = (uint32_t)(value % 10);
    return value / 10;
}

static int32_t sign_extend_11(uint32_t value)
{
    value &= 0x7ff;
    return (value & 0x400) != 0 ? (int32_t)value - 0x800 : (int32_t)value;
}

static NormalizedBinary64 pack_normalized(
    uint32_t exponent_word,
    uint32_t significand_high,
    uint32_t significand_low)
{
    NormalizedBinary64 result = {
        exponent_word,
        significand_high,
        significand_low
    };
    return result;
}

NormalizedBinary64 unpack_binary64_normalized(uint32_t high_word, uint32_t low_word)
{
    uint32_t shifted_high = high_word << 1;
    uint32_t exponent = (high_word & 0x7fffffff) >> 19;
    uint32_t shifted_low = low_word << 11;
    uint32_t significand = (high_word << 11) | (low_word >> 21);

    if (shifted_high != 0 || low_word != 0) {
        exponent += 0x7800;
        significand |= 0x80000000;
    }
    exponent = (high_word & 0x80000000) | (exponent >> 1);

    int32_t exponent_class = sign_extend_11(shifted_high >> 21);
    if (exponent_class != 0) {
        if (exponent_class == -1) {
            exponent |= 0x40000000;
        }
        return pack_normalized(exponent, significand, shifted_low);
    }
    if ((significand & 0x80000000) == 0) {
        return pack_normalized(exponent, significand, shifted_low);
    }

    uint32_t leading_bits = significand & 0x7fffffff;
    if (leading_bits == 0) {
        int shift_count;
        if (((low_word & 0x1fffff) >> 5) == 0) {
            shifted_low = low_word << 27;
            shift_count = 16;
        } else {
            shift_count = 0;
        }
        if ((shifted_low >> 24) == 0) {
            shifted_low <<= 8;
            shift_count += 8;
        }
        if ((shifted_low >> 28) == 0) {
            shifted_low <<= 4;
            shift_count += 4;
        }
        if ((shifted_low >> 30) == 0) {
            shifted_low <<= 2;
            shift_count += 2;
        }
        if ((shifted_low & 0x80000000) == 0) {
            shifted_low <<= 1;
            ++shift_count;
        }
        return pack_normalized(
            exponent - 0x1f - (uint32_t)shift_count,
            shifted_low,
            0);
    }

    int shift_count = 0;
    if ((leading_bits >> 16) == 0) {
        leading_bits = significand << 16;
        shift_count = 16;
    }
    if ((leading_bits >> 24) == 0) {
        leading_bits <<= 8;
        shift_count += 8;
    }
    if ((leading_bits >> 28) == 0) {
        leading_bits <<= 4;
        shift_count += 4;
    }
    if ((leading_bits >> 30) == 0) {
        leading_bits <<= 2;
        shift_count += 2;
    }
    if ((leading_bits & 0x80000000) == 0) {
        ++shift_count;
        leading_bits <<= 1;
    }

    uint32_t normalized = leading_bits |
        (shifted_low >> ((32u - (uint32_t)shift_count) & 0xff));
    return pack_normalized(
        exponent - (uint32_t)shift_count + 1,
        normalized,
        0);
}

uint32_t classify_binary64(uint32_t high_word, uint32_t low_word)
{
    uint32_t exponent = (high_word & 0x7ff00000) >> 20;
    uint32_t classification = 0;

    if ((high_word & 0x000fffff) != 0 || low_word != 0) {
        classification = 4;
    }
    if (exponent != 0) {
        classification |= 1;
    }
    if (exponent == 0x7ff) {
        classification |= 2;
    }
    if (classification == 1) {
        classification = 5;
    }
    return classification;
}

NormalizedBinary64 round_extended96(
    uint32_t sign_word,
    uint32_t significand_high,
    uint32_t significand_low,
    int32_t exponent,
    uint32_t round_sticky,
    int32_t rounding_mode)
{
    if (exponent < 0) {
        round_sticky |= round_sticky << 16;
        round_sticky >>= 16;
        if (exponent <= -64) {
            round_sticky |= significand_low;
            significand_low = 0;
            round_sticky |= round_sticky << 16;
            round_sticky >>= 16;
            round_sticky |= significand_high;
            significand_high = 0;
            if (exponent < -64) {
                round_sticky |= round_sticky << 16;
                round_sticky >>= 16;
            }
            exponent = 0;
        } else {
            if (exponent <= -32) {
                round_sticky |= significand_low;
                significand_low = significand_high;
                significand_high = 0;
                exponent += 32;
            }
            uint32_t shift = (uint32_t)-exponent;
            if (shift != 0) {
                uint32_t left_shift = 32u - shift;
                round_sticky |= round_sticky << 16;
                round_sticky >>= 16;
                round_sticky |= significand_low << left_shift;
                significand_low = (significand_low >> shift) |
                    (significand_high << left_shift);
                significand_high >>= shift;
                exponent = 0;
            }
        }
    }

    int round_up = 0;
    if (round_sticky != 0) {
        if (rounding_mode > 0) {
            round_up = 1;
        } else if (rounding_mode == 0 && (round_sticky & 0x80000000) != 0) {
            round_up = (round_sticky & 0x7fffffff) != 0 ||
                (significand_low & 1) != 0;
        }
    }

    if (round_up) {
        ++significand_low;
        if (significand_low == 0) {
            ++significand_high;
            if (significand_high == 0) {
                significand_high = 0x80000000;
                ++exponent;
            }
        }
    }

    return pack_normalized(
        (uint32_t)exponent | (sign_word & 0x80000000),
        significand_high,
        significand_low);
}

NormalizedBinary64 multiply_extended96(
    const NormalizedBinary64 *operand_a,
    const NormalizedBinary64 *operand_b,
    int32_t rounding_mode)
{
    uint32_t sign = (operand_a->exponent_word ^ operand_b->exponent_word) & 0x80000000;
    int32_t exponent = (int32_t)((operand_a->exponent_word & 0x00ffffff) +
        (operand_b->exponent_word & 0x00ffffff)) - 0x3ffe;

    uint64_t significand_a = ((uint64_t)operand_a->significand_high << 32) |
        operand_a->significand_low;
    uint64_t significand_b = ((uint64_t)operand_b->significand_high << 32) |
        operand_b->significand_low;
    uint32_t a_low = (uint32_t)significand_a;
    uint32_t a_high = (uint32_t)(significand_a >> 32);
    uint32_t b_low = (uint32_t)significand_b;
    uint32_t b_high = (uint32_t)(significand_b >> 32);

    uint64_t p00 = (uint64_t)a_low * b_low;
    uint64_t p01 = (uint64_t)a_low * b_high;
    uint64_t p10 = (uint64_t)a_high * b_low;
    uint64_t p11 = (uint64_t)a_high * b_high;
    uint64_t middle = p01 + p10;
    uint64_t middle_carry = middle < p01 ? UINT64_C(1) << 32 : 0;
    uint64_t product_low = p00 + (middle << 32);
    uint64_t product_high = p11 + (middle >> 32) + middle_carry +
        (product_low < p00 ? 1 : 0);

    if ((product_high & UINT64_C(0x8000000000000000)) == 0) {
        product_high = (product_high << 1) | (product_low >> 63);
        product_low <<= 1;
        --exponent;
    }

    uint32_t round_sticky = (uint32_t)(product_low >> 32);
    if ((uint32_t)product_low != 0) {
        round_sticky |= 1;
    }

    return round_extended96(
        sign,
        (uint32_t)(product_high >> 32),
        (uint32_t)product_high,
        exponent,
        round_sticky,
        rounding_mode);
}

NormalizedBinary64 divide_extended96(
    const NormalizedBinary64 *dividend,
    const NormalizedBinary64 *divisor,
    int32_t rounding_mode)
{
    uint32_t sign = (dividend->exponent_word ^ divisor->exponent_word) & 0x80000000;
    int32_t exponent = (int32_t)(dividend->exponent_word & 0x00ffffff) -
        (int32_t)(divisor->exponent_word & 0x00ffffff) + 0x3fff;

    uint64_t numerator = ((uint64_t)dividend->significand_high << 32) |
        dividend->significand_low;
    uint64_t denominator = ((uint64_t)divisor->significand_high << 32) |
        divisor->significand_low;

    uint32_t lost_bit = 0;
    if (numerator >= denominator) {
        lost_bit = (uint32_t)(numerator & 1);
        numerator >>= 1;
    }

    unsigned __int128 remainder128 = (unsigned __int128)numerator << 64;
    unsigned __int128 quotient128 = remainder128 / denominator;
    uint64_t remainder = (uint64_t)(remainder128 % denominator);
    uint64_t quotient = (uint64_t)quotient128;
    if (remainder != 0) {
        remainder += lost_bit;
    }

    uint32_t round_sticky = 0;
    if (remainder != 0) {
        uint64_t doubled = remainder * 2;
        if (doubled < denominator) {
            round_sticky = 0x40000000;
        } else if (doubled > denominator) {
            round_sticky = 0x80000000;
        } else {
            round_sticky = 0x80000001;
        }
    }

    return round_extended96(
        sign,
        (uint32_t)(quotient >> 32),
        (uint32_t)quotient,
        exponent,
        round_sticky,
        rounding_mode);
}