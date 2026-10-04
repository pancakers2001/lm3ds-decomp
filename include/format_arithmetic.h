#ifndef LM3DS_FORMAT_ARITHMETIC_H
#define LM3DS_FORMAT_ARITHMETIC_H

#include <stdint.h>

typedef struct {
	uint32_t exponent_word;
	uint32_t significand_high;
	uint32_t significand_low;
} NormalizedBinary64;

_Static_assert(sizeof(NormalizedBinary64) == 12, "normalized binary64 ABI size");

uint64_t divmod_u64_by_10(uint64_t value, uint32_t *remainder);
NormalizedBinary64 unpack_binary64_normalized(uint32_t high_word, uint32_t low_word);
uint32_t classify_binary64(uint32_t high_word, uint32_t low_word);
NormalizedBinary64 round_extended96(
	uint32_t sign_word,
	uint32_t significand_high,
	uint32_t significand_low,
	int32_t exponent,
	uint32_t round_sticky,
	int32_t rounding_mode);
NormalizedBinary64 multiply_extended96(
	const NormalizedBinary64 *operand_a,
	const NormalizedBinary64 *operand_b,
	int32_t rounding_mode);
NormalizedBinary64 divide_extended96(
	const NormalizedBinary64 *dividend,
	const NormalizedBinary64 *divisor,
	int32_t rounding_mode);

#endif