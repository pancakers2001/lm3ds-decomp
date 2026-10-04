#include "format_context.h"
#include "format_arithmetic.h"

#include <limits.h>
#include <stdio.h>
#include <string.h>

static const uint32_t *align_arguments(const uint32_t *arguments)
{
    uintptr_t address = (uintptr_t)arguments;
    return (const uint32_t *)((address + 7u) & ~(uintptr_t)7u);
}

static uint64_t read_u64(const uint32_t *arguments)
{
    const uint32_t *aligned = align_arguments(arguments);
    return ((uint64_t)aligned[1] << 32) | aligned[0];
}

static void write_number_character(FormatContext *context, uint32_t character);

static int emit_number(
    FormatContext *context,
    uint32_t digit_count,
    const char *prefix,
    uint32_t prefix_length,
    int argument_words)
{
    int32_t minimum_digits = 1;
    if ((context->flags & FORMAT_FLAG_HAS_PRECISION) != 0) {
        minimum_digits = (int32_t)context->precision;
        context->flags &= ~FORMAT_FLAG_ZERO_PAD;
    }

    uint32_t zero_count = minimum_digits > (int32_t)digit_count
        ? (uint32_t)(minimum_digits - (int32_t)digit_count)
        : 0;
    context->width -= (int32_t)(zero_count + digit_count + prefix_length);

    if ((context->flags & FORMAT_FLAG_ZERO_PAD) == 0) {
        format_pad_before(context);
    }
    for (uint32_t index = 0; index < prefix_length; ++index) {
        write_number_character(context, (uint8_t)prefix[index]);
    }
    context->output_count += prefix_length;

    if ((context->flags & FORMAT_FLAG_ZERO_PAD) != 0) {
        format_pad_before(context);
    }
    while (zero_count != 0) {
        write_number_character(context, '0');
        ++context->output_count;
        --zero_count;
    }
    while (digit_count != 0) {
        write_number_character(context, context->conversion_buffer[--digit_count]);
        ++context->output_count;
    }
    format_pad_after(context);
    return argument_words;
}

static void write_number_character(FormatContext *context, uint32_t character)
{
    FormatWriteCallback callback =
        (FormatWriteCallback)(uintptr_t)context->write_callback;
    callback(character, context->write_context);
}

static int emit_unsigned(
    FormatContext *context,
    uint64_t value,
    uint32_t base,
    const char *prefix,
    uint32_t prefix_length,
    int argument_words)
{
    int value_is_nonzero = value != 0;
    const char *alphabet = (context->flags & FORMAT_FLAG_UPPERCASE) != 0
        ? "0123456789ABCDEF"
        : "0123456789abcdef";
    uint32_t digit_count = 0;
    while (value != 0) {
        uint32_t digit;
        if (base == 10) {
            value = divmod_u64_by_10(value, &digit);
        } else {
            digit = (uint32_t)(value % base);
            value /= base;
        }
        context->conversion_buffer[digit_count++] = (uint8_t)alphabet[digit];
    }

    if (base == 8 && (context->flags & FORMAT_FLAG_ALTERNATE) != 0 &&
        ((context->flags & FORMAT_FLAG_HAS_PRECISION) != 0 || digit_count != 0)) {
        prefix = "0";
        prefix_length = 1;
        if ((context->flags & FORMAT_FLAG_HAS_PRECISION) != 0) {
            --context->precision;
        }
    } else if (base == 16 && value_is_nonzero &&
        (context->flags & FORMAT_FLAG_ALTERNATE) != 0) {
        prefix = (context->flags & FORMAT_FLAG_UPPERCASE) != 0 ? "0X" : "0x";
        prefix_length = 2;
    }

    return emit_number(context, digit_count, prefix, prefix_length, argument_words);
}

static int format_signed(FormatContext *context, const uint32_t *arguments)
{
    uint64_t magnitude;
    int argument_words;
    int negative;

    if ((context->flags & FORMAT_FLAG_INTMAX) != 0) {
        uint64_t value = read_u64(arguments);
        int64_t signed_value = (int64_t)value;
        negative = signed_value < 0;
        magnitude = negative ? 0 - value : value;
        argument_words = 2;
    } else {
        int32_t value = (int32_t)*arguments;
        if ((context->flags & FORMAT_FLAG_SHORT_SHORT) != 0) {
            value = (int8_t)value;
        } else if ((context->flags & FORMAT_FLAG_SHORT) != 0) {
            value = (int16_t)value;
        }
        negative = value < 0;
        magnitude = negative ? 0u - (uint32_t)value : (uint32_t)value;
        argument_words = 1;
    }

    const char *prefix = "";
    uint32_t prefix_length = 0;
    if (negative) {
        prefix = "-";
        prefix_length = 1;
    } else if ((context->flags & FORMAT_FLAG_PLUS) != 0) {
        prefix = "+";
        prefix_length = 1;
    } else if ((context->flags & FORMAT_FLAG_SPACE) != 0) {
        prefix = " ";
        prefix_length = 1;
    }
    return emit_unsigned(context, magnitude, 10, prefix, prefix_length, argument_words);
}

static int format_unsigned(
    FormatContext *context,
    const uint32_t *arguments,
    uint32_t base,
    const char *prefix,
    uint32_t prefix_length)
{
    uint64_t value;
    int argument_words;
    if ((context->flags & FORMAT_FLAG_INTMAX) != 0) {
        value = read_u64(arguments);
        argument_words = 2;
    } else {
        value = *arguments;
        if ((context->flags & FORMAT_FLAG_SHORT_SHORT) != 0) {
            value &= 0xff;
        } else if ((context->flags & FORMAT_FLAG_SHORT) != 0) {
            value &= 0xffff;
        }
        argument_words = 1;
    }
    return emit_unsigned(context, value, base, prefix, prefix_length, argument_words);
}

static int format_count_store(FormatContext *context, const uint32_t *arguments)
{
    uintptr_t address = *arguments;
    if ((context->flags & FORMAT_FLAG_SHORT_SHORT) != 0) {
        *(int8_t *)address = (int8_t)context->output_count;
    } else if ((context->flags & FORMAT_FLAG_SHORT) != 0) {
        *(int16_t *)address = (int16_t)context->output_count;
    } else if ((context->flags & FORMAT_FLAG_INTMAX) != 0) {
        *(int64_t *)address = (int32_t)context->output_count;
    } else {
        *(int32_t *)address = (int32_t)context->output_count;
    }
    return 1;
}

static int format_hex_float(FormatContext *context, const uint32_t *arguments)
{
    uint64_t bits = read_u64(arguments);
    uint64_t fraction = bits & UINT64_C(0x000fffffffffffff);
    uint32_t exponent_bits = (uint32_t)((bits >> 52) & 0x7ff);
    int exponent = exponent_bits == 0 ? -1022 : (int)exponent_bits - 1023;
    int negative = (bits >> 63) != 0;
    int uppercase = (context->flags & FORMAT_FLAG_UPPERCASE) != 0;
    int special = exponent_bits == 0x7ff;
    uint32_t precision = (context->flags & FORMAT_FLAG_HAS_PRECISION) != 0
        ? context->precision
        : 13;
    uint32_t leading_digit = 1;

    if (special) {
        const char *token = fraction == 0 ? "inf" : "nan";
        context->flags &= ~FORMAT_FLAG_ZERO_PAD;
        uint32_t sign_length = negative ||
            (context->flags & (FORMAT_FLAG_PLUS | FORMAT_FLAG_SPACE)) != 0;
        context->width -= (int32_t)(3 + sign_length);
        format_pad_before(context);
        if (negative) {
            write_number_character(context, '-');
        } else if ((context->flags & FORMAT_FLAG_PLUS) != 0) {
            write_number_character(context, '+');
        } else if ((context->flags & FORMAT_FLAG_SPACE) != 0) {
            write_number_character(context, ' ');
        }
        context->output_count += sign_length;
        if (uppercase) {
            for (uint32_t index = 0; index < 3; ++index) {
                write_number_character(context, (uint8_t)(token[index] - ('a' - 'A')));
            }
        } else {
            for (uint32_t index = 0; index < 3; ++index) {
                write_number_character(context, (uint8_t)token[index]);
            }
        }
        context->width -= 3;
        context->output_count += 3;
        format_pad_after(context);
        return 2;
    }

    if (exponent_bits == 0 && fraction == 0) {
        leading_digit = 0;
        exponent = 0;
    } else if (exponent_bits == 0) {
        while ((fraction & (UINT64_C(1) << 52)) == 0) {
            fraction <<= 1;
            --exponent;
        }
        fraction &= UINT64_C(0x000fffffffffffff);
    }

    if (precision < 13) {
        uint32_t discarded_bits = 52 - precision * 4;
        uint64_t kept = fraction >> discarded_bits;
        uint64_t discarded_mask = (UINT64_C(1) << discarded_bits) - 1;
        uint64_t discarded = fraction & discarded_mask;
        uint64_t halfway = UINT64_C(1) << (discarded_bits - 1);
        if (discarded > halfway || (discarded == halfway && (kept & 1) != 0)) {
            ++kept;
        }
        if (kept == (UINT64_C(1) << (precision * 4))) {
            kept = 0;
            ++exponent;
        }
        fraction = kept << discarded_bits;
    }

    uint32_t exponent_magnitude = (uint32_t)(exponent < 0 ? -exponent : exponent);
    char exponent_digits[12];
    uint32_t exponent_digit_count = 0;
    do {
        exponent_digits[exponent_digit_count++] = (char)('0' + exponent_magnitude % 10);
        exponent_magnitude /= 10;
    } while (exponent_magnitude != 0);

    int has_point = precision != 0 || (context->flags & FORMAT_FLAG_ALTERNATE) != 0;
    uint32_t sign_length = negative || (context->flags & (FORMAT_FLAG_PLUS | FORMAT_FLAG_SPACE)) != 0;
    uint32_t total_length = sign_length + 2 + 1 + (uint32_t)has_point + precision +
        2 + exponent_digit_count;
    context->width -= (int32_t)total_length;

    if ((context->flags & FORMAT_FLAG_ZERO_PAD) == 0) {
        format_pad_before(context);
    }
    if (negative) {
        write_number_character(context, '-');
    } else if ((context->flags & FORMAT_FLAG_PLUS) != 0) {
        write_number_character(context, '+');
    } else if ((context->flags & FORMAT_FLAG_SPACE) != 0) {
        write_number_character(context, ' ');
    }
    context->output_count += sign_length;

    if ((context->flags & FORMAT_FLAG_ZERO_PAD) != 0) {
        format_pad_before(context);
    }

    write_number_character(context, '0');
    write_number_character(context, uppercase ? 'X' : 'x');
    write_number_character(context, (uint8_t)(leading_digit == 0 ? '0' : '1'));
    context->output_count += 3;
    if (has_point) {
        write_number_character(context, '.');
        ++context->output_count;
    }

    const char *alphabet = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    for (uint32_t index = 0; index < precision; ++index) {
        uint32_t digit = index < 13
            ? (uint32_t)((fraction >> (48 - index * 4)) & 0xf)
            : 0;
        write_number_character(context, (uint8_t)alphabet[digit]);
        ++context->output_count;
    }

    write_number_character(context, uppercase ? 'P' : 'p');
    write_number_character(context, exponent < 0 ? '-' : '+');
    context->output_count += 2;
    for (uint32_t index = exponent_digit_count; index != 0; --index) {
        write_number_character(context, (uint8_t)exponent_digits[index - 1]);
        ++context->output_count;
    }

    format_pad_after(context);
    return 2;
}

static void emit_wide_text(
    FormatContext *context,
    const uint16_t *text,
    uint32_t maximum_units,
    int single_character)
{
    uint32_t unit_count = 0;

    if (context->mode != 0) {
        if (single_character) {
            unit_count = 1;
        } else {
            while (unit_count < maximum_units && text[unit_count] != 0) {
                ++unit_count;
            }
        }

        context->width -= (int32_t)unit_count;
        context->output_count += unit_count;
        format_pad_before(context);
        FormatWriteCallback callback =
            (FormatWriteCallback)(uintptr_t)context->write_callback;
        for (uint32_t index = 0; index < unit_count; ++index) {
            callback(text[index], context->write_context);
        }
        format_pad_after(context);
        return;
    }

    uint32_t byte_count = 0;
    while (unit_count < maximum_units && (single_character || text[unit_count] != 0)) {
        if ((context->flags & FORMAT_FLAG_HAS_PRECISION) != 0 &&
            byte_count >= context->precision) {
            break;
        }
        if (text[unit_count] < 0x80 && text[unit_count] != 0) {
            ++byte_count;
        }
        ++unit_count;
    }

    context->width -= (int32_t)byte_count;
    format_pad_before(context);
    FormatWriteCallback callback =
        (FormatWriteCallback)(uintptr_t)context->write_callback;
    for (uint32_t index = 0; index < unit_count; ++index) {
        if (text[index] < 0x80 && text[index] != 0) {
            callback(text[index], context->write_context);
        }
    }
    context->output_count += byte_count;
    format_pad_after(context);
}

static int format_decimal_float(FormatContext *context, const uint32_t *arguments)
{
    uint64_t bits = read_u64(arguments);
    double value;
    memcpy(&value, &bits, sizeof(value));

    char buffer[64];
    int length = 0;

    switch (context->flags & FORMAT_FLAG_UPPERCASE ? 'A' : 'a') {
    case 'a':
        length = snprintf(buffer, sizeof(buffer), "%A", value);
        break;
    default:
        length = snprintf(buffer, sizeof(buffer), "%a", value);
        break;
    }

    if (length < 0 || (size_t)length >= sizeof(buffer)) {
        return 0;
    }

    emit_formatted_bytes(context, (const uint8_t *)buffer, (uint32_t)length);
    return 2;
}

int format_specifier(FormatContext *context, uint32_t specifier, uint32_t *arguments)
{
    if (specifier == 'c' && (context->flags & FORMAT_FLAG_LONG) != 0) {
        uint16_t character = (uint16_t)*arguments;
        emit_wide_text(context, &character, 1, 1);
        return 1;
    }
    if (specifier == 's' && (context->flags & FORMAT_FLAG_LONG) != 0) {
        const uint16_t *text = (const uint16_t *)(uintptr_t)*arguments;
        if (text == NULL) {
            return 0;
        }
        emit_wide_text(context, text, UINT32_MAX, 0);
        return 1;
    }

    switch (specifier) {
    case 'd':
    case 'i':
        return format_signed(context, arguments);
    case 'u':
        return format_unsigned(context, arguments, 10, "", 0);
    case 'o':
        return format_unsigned(context, arguments, 8, "", 0);
    case 'x':
        return format_unsigned(context, arguments, 16, "", 0);
    case 'p':
        context->flags |= FORMAT_FLAG_HAS_PRECISION;
        context->precision = 8;
        return format_unsigned(context, arguments, 16, "", 0);
    case 'c':
        context->conversion_buffer[0] = (uint8_t)*arguments;
        emit_formatted_bytes(context, context->conversion_buffer, 1);
        return 1;
    case 's': {
        const uint8_t *text = (const uint8_t *)(uintptr_t)*arguments;
        if (text == NULL) {
            text = (const uint8_t *)"(null)";
        }
        emit_formatted_bytes(context, text, UINT32_MAX);
        return 1;
    }
    case 'n':
        return format_count_store(context, arguments);
    case 'a':
        return format_hex_float(context, arguments);
    case 'e':
    case 'f':
    case 'g':
        return format_decimal_float(context, arguments);
    default:
        return 0;
    }
}