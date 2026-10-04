#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "format_context.h"
#include "format_arithmetic.h"

void run_constructor_tests(void);
void run_locale_tests(void);
void run_runtime_tests(void);
void run_system_state_tests(void);
void run_sleep_state_tests(void);
void run_stack_setup_tests(void);
void run_process_state_tests(void);
void run_sleep_wait_tests(void);
void run_runtime_wrapper_tests(void);

static char output[64];
static uint32_t captured_characters[64];
static uint32_t output_length;
static int32_t count_storage;

static uint32_t read_character(FormatContext *context)
{
    const uint8_t *input = (const uint8_t *)(uintptr_t)context->input;
    ++context->input;
    return *input;
}

static void write_character(uint32_t character, uint32_t context)
{
    (void)context;
    assert(output_length < sizeof(output));
    captured_characters[output_length] = character;
    output[output_length++] = (char)character;
}

static void initialize_context(FormatContext *context, const char *format)
{
    memset(context, 0, sizeof(*context));
    context->write_callback = (uint32_t)(uintptr_t)write_character;
    context->read_callback = (uint32_t)(uintptr_t)read_character;
    context->input = (uint32_t)(uintptr_t)format;
    output_length = 0;
}

static void assert_output(const char *expected)
{
    size_t expected_length = strlen(expected);
    assert(output_length == expected_length);
    assert(memcmp(output, expected, expected_length) == 0);
}

static void test_literal_output(void)
{
    static const char format[] = "plain text";
    FormatContext context;
    uint32_t arguments[1] = { 0 };

    initialize_context(&context, format);
    assert(format_to_sink(&context, arguments) == 10);
    assert_output("plain text");
}

static void test_flags_and_fields(void)
{
    static const char format[] = "%0-+ #10.4d";
    FormatContext context;
    uint32_t arguments[1] = { 12 };

    initialize_context(&context, format);
    assert(format_to_sink(&context, arguments) == 10);
    assert_output("+0012     ");
    assert(context.flags == (FORMAT_FLAG_LEFT_JUSTIFY | FORMAT_FLAG_PLUS |
        FORMAT_FLAG_ALTERNATE | FORMAT_FLAG_HAS_PRECISION));
    assert(context.width == 5);
}

static void test_negative_star_fields(void)
{
    static const char format[] = "%*.*d";
    FormatContext context;
    uint32_t arguments[3] = { (uint32_t)-5, (uint32_t)-1, 7 };

    initialize_context(&context, format);
    assert(format_to_sink(&context, arguments) == 5);
    assert_output("7    ");
    assert(context.flags == FORMAT_FLAG_LEFT_JUSTIFY);
    assert(context.width == 4);
    assert(context.precision == UINT32_MAX);
}

static void test_padding_and_precision(void)
{
    static const uint8_t text[] = "abcd";
    FormatContext context;

    initialize_context(&context, "");
    context.width = 5;
    emit_formatted_bytes(&context, text, 2);
    assert_output("   ab");
    assert(context.width == 3);
    assert(context.output_count == 5);

    initialize_context(&context, "");
    context.flags = FORMAT_FLAG_LEFT_JUSTIFY;
    context.width = 5;
    emit_formatted_bytes(&context, text, 2);
    assert_output("ab   ");
    assert(context.output_count == 5);

    initialize_context(&context, "");
    context.flags = FORMAT_FLAG_ZERO_PAD | FORMAT_FLAG_HAS_PRECISION;
    context.width = 4;
    context.precision = 2;
    emit_formatted_bytes(&context, text, 4);
    assert_output("00ab");
    assert(context.output_count == 4);
}

static void test_u16_buffer_write(void)
{
    static uint16_t buffer[4];
    uint16_t *cursor = buffer;
    uint16_t *limit = buffer + 2;

    write_u16_to_buffer(0x1234, &cursor, limit);
    write_u16_to_buffer(0x5678, &cursor, limit);
    write_u16_to_buffer(0x9abc, &cursor, limit);

    assert(buffer[0] == 0x1234);
    assert(buffer[1] == 0x5678);
    assert(cursor == limit);
}

static char format_buffer[64];

static void test_format_to_buffer(void)
{
    uint32_t arguments[1] = { 42 };
    uint32_t count = format_to_buffer(format_buffer, "value=%d", arguments);
    assert(count == 8);
    assert(memcmp(format_buffer, "value=42", 9) == 0);
}

static void test_bounded_string_copy(void)
{
    static char buffer[16];
    copy_string_bounded(buffer, "hello", 16);
    assert(strcmp(buffer, "hello") == 0);

    copy_string_bounded(buffer, "this is a long string", 8);
    assert(strcmp(buffer, "this is ") == 0);

    copy_string_bounded(buffer, "", 8);
    assert(buffer[0] == '\0');
}

static void test_find_last_character(void)
{
    static char text[] = "hello world";
    assert(find_last_character(text, 'l') == text + 9);
    assert(find_last_character(text, 'o') == text + 7);
    assert(find_last_character(text, 'h') == text);
    assert(find_last_character(text, 'z') == NULL);
    assert(find_last_character(text, '\0') == text + 11);
}

static void test_character_class(void)
{
    assert(is_character_class('a') == 1);
    assert(is_character_class('Z') == 1);
    assert(is_character_class('0') == 1);
    assert(is_character_class(' ') == 1);
    assert(is_character_class(0) == 0);
    assert(is_character_class(0x1f) == 0);
}

static void test_find_wide_character(void)
{
    static const uint16_t text[] = { 'h', 'e', 'l', 'l', 'o', 0 };
    assert(find_wide_character(text, 5, 'l') == 1);
    assert(find_wide_character(text, 5, 'o') == 1);
    assert(find_wide_character(text, 5, 'z') == 0);
    assert(find_wide_character(text, 0, 'h') == 0);
}

static void test_integer_conversions(void)
{
    static const char format[] = "%d|%u|%#x|%#o";
    FormatContext context;
    uint32_t arguments[4] = { (uint32_t)-42, 42, 0x2a, 8 };

    initialize_context(&context, format);
    assert(format_to_sink(&context, arguments) == 15);
    assert_output("-42|42|0x2a|010");
}

static void test_pointer_string_and_character(void)
{
    static const char pointer_format[] = "%p";
    static const char text_format[] = "%s:%c";
    static const char text[] = "ok";
    FormatContext context;
    uint32_t pointer_arguments[1] = { 0x12 };
    uint32_t text_arguments[2] = { (uint32_t)(uintptr_t)text, 'Z' };

    initialize_context(&context, pointer_format);
    assert(format_to_sink(&context, pointer_arguments) == 8);
    assert_output("00000012");

    initialize_context(&context, text_format);
    assert(format_to_sink(&context, text_arguments) == 4);
    assert_output("ok:Z");
}

static void test_count_and_long_long(void)
{
    static const char count_format[] = "ab%ncd";
    static const char long_long_format[] = "%lld";
    FormatContext context;
    uint32_t count_arguments[1] = { (uint32_t)(uintptr_t)&count_storage };
    _Alignas(8) uint32_t long_long_arguments[2] = { (uint32_t)-42, UINT32_MAX };

    count_storage = 0;
    initialize_context(&context, count_format);
    assert(format_to_sink(&context, count_arguments) == 4);
    assert_output("abcd");
    assert(count_storage == 2);

    initialize_context(&context, long_long_format);
    assert(format_to_sink(&context, long_long_arguments) == 3);
    assert_output("-42");
}

static void test_numeric_edge_cases(void)
{
    static const char format[] = "%#.0o|%.0d|%+010d";
    FormatContext context;
    uint32_t arguments[3] = { 0, 0, (uint32_t)-42 };

    initialize_context(&context, format);
    assert(format_to_sink(&context, arguments) == 13);
    assert_output("0||-000000042");
}

static void test_wide_output_modes(void)
{
    static const char string_format[] = "%ls";
    static const char character_format[] = "%lc";
    static const uint16_t wide_text[] = { 0x03a9, 'x', 0 };
    static const uint16_t ascii_text[] = { 'A', 'B', 0 };
    FormatContext context;
    uint32_t string_arguments[1] = { (uint32_t)(uintptr_t)wide_text };
    uint32_t ascii_arguments[1] = { (uint32_t)(uintptr_t)ascii_text };
    uint32_t character_arguments[1] = { 0x03a9 };

    initialize_context(&context, string_format);
    context.mode = 1;
    assert(format_to_sink(&context, string_arguments) == 2);
    assert(captured_characters[0] == 0x03a9);
    assert(captured_characters[1] == 'x');

    initialize_context(&context, string_format);
    assert(format_to_sink(&context, ascii_arguments) == 2);
    assert_output("AB");

    initialize_context(&context, character_format);
    context.mode = 1;
    assert(format_to_sink(&context, character_arguments) == 1);
    assert(captured_characters[0] == 0x03a9);
}

static void test_formatting_edge_cases(void)
{
    static const char format[] = "[%#08x][%#.0o][%#.3o][%.0d][%08.3d][%10.3s][%-5.3s]";
    static const char text[] = "abcdef";
    FormatContext context;
    uint32_t arguments[7] = { 0x2a, 0, 8, 0, 42,
        (uint32_t)(uintptr_t)text, (uint32_t)(uintptr_t)text };

    initialize_context(&context, format);
    assert(format_to_sink(&context, arguments) == 49);
    assert_output("[0x00002a][0][010][][     042][       abc][abc  ]");
}

static void test_format_wrappers(void)
{
    static const char text[] = "ok";
    static char buffer[64];
    static uint8_t *cursor;
    cursor = (uint8_t *)buffer;
    uint32_t arguments[3] = { 42, (uint32_t)(uintptr_t)text, 0x2a };

    uint32_t count = format_string_to_sink("[%5d][%-6s][%#x]",
        (uint32_t)(uintptr_t)&cursor, arguments, write_buffer_character);
    assert(count == 21);
    assert(memcmp(buffer, "[   42][ok    ][0x2a]", 21) == 0);

    static const uint16_t wide_format[] = {
        '<', '%', '3', 'd', ':', '%', 'c', '>', 0
    };
    cursor = (uint8_t *)buffer;
    uint32_t wide_arguments[2] = { 7, 'Z' };
    count = format_wstring_to_sink(wide_format,
        (uint32_t)(uintptr_t)&cursor, wide_arguments, write_buffer_character);
    assert(count == 7);
    assert(memcmp(buffer, "<  7:Z>", 7) == 0);
}

static void test_u64_divmod_by_ten(void)
{
    static const struct {
        uint64_t value;
        uint64_t quotient;
        uint32_t remainder;
    } cases[] = {
        { 0, 0, 0 },
        { 9, 0, 9 },
        { 10, 1, 0 },
        { 123456789, 12345678, 9 },
        { UINT64_MAX, UINT64_C(1844674407370955161), 5 }
    };

    for (size_t index = 0; index < sizeof(cases) / sizeof(cases[0]); ++index) {
        uint32_t remainder = UINT32_MAX;
        uint64_t quotient = divmod_u64_by_10(cases[index].value, &remainder);
        assert(quotient == cases[index].quotient);
        assert(remainder == cases[index].remainder);
    }
}

static void test_binary64_normalization(void)
{
    NormalizedBinary64 value = unpack_binary64_normalized(0x3ff00000, 0);
    assert(value.exponent_word == 0x3fff);
    assert(value.significand_high == 0x80000000);
    assert(value.significand_low == 0);

    value = unpack_binary64_normalized(0x3ff80000, 0);
    assert(value.exponent_word == 0x3fff);
    assert(value.significand_high == 0xc0000000);
    assert(value.significand_low == 0);

    value = unpack_binary64_normalized(0x3ff40000, 0);
    assert(value.exponent_word == 0x3fff);
    assert(value.significand_high == 0xa0000000);
    assert(value.significand_low == 0);

    value = unpack_binary64_normalized(0x3ff19999, 0x9999999a);
    assert(value.exponent_word == 0x3fff);
    assert(value.significand_high == 0x8ccccccc);
    assert(value.significand_low == 0xccccd000);

    value = unpack_binary64_normalized(0xc0040000, 0);
    assert(value.exponent_word == 0x80004000);
    assert(value.significand_high == 0xa0000000);
    assert(value.significand_low == 0);

    value = unpack_binary64_normalized(0, 0);
    assert(value.exponent_word == 0);
    assert(value.significand_high == 0);
    assert(value.significand_low == 0);

    value = unpack_binary64_normalized(0, 1);
    assert(value.exponent_word == 0x3bcd);
    assert(value.significand_high == 0x80000000);
    assert(value.significand_low == 0);
}

static void test_binary64_classification(void)
{
    assert(classify_binary64(0, 0) == 0);
    assert(classify_binary64(0x80000000, 0) == 0);
    assert(classify_binary64(0x3ff00000, 0) == 5);
    assert(classify_binary64(0, 1) == 4);
    assert(classify_binary64(0x7ff00000, 0) == 3);
    assert(classify_binary64(0xfff00000, 0) == 3);
    assert(classify_binary64(0x7ff80000, 1) == 7);
}

static void test_extended_rounding(void)
{
    NormalizedBinary64 result = round_extended96(
        0x80000000, 0x80000000, 0x12345678, 0x3fff, 0, 0);
    assert(result.exponent_word == 0x80003fff);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 0x12345678);

    result = round_extended96(0, 0x80000000, 2, 0x3fff, 0x40000001, 0);
    assert(result.significand_low == 2);
    result = round_extended96(0, 0x80000000, 2, 0x3fff, 0x40000001, -1);
    assert(result.significand_low == 2);
    result = round_extended96(0, 0x80000000, 2, 0x3fff, 0x40000001, 1);
    assert(result.significand_low == 3);

    result = round_extended96(0, 0x80000000, 2, 0x3fff, 0x80000000, 0);
    assert(result.significand_low == 2);
    result = round_extended96(0, 0x80000000, 3, 0x3fff, 0x80000000, 0);
    assert(result.significand_low == 4);
    result = round_extended96(0, 0x80000000, 2, 0x3fff, 0x80000000, 1);
    assert(result.significand_low == 3);

    result = round_extended96(0, 0x80000000, 2, 0x3fff, 0xc0000000, 0);
    assert(result.significand_low == 3);
    result = round_extended96(0, 0x80000000, 2, 0x3fff, 0xc0000000, -1);
    assert(result.significand_low == 2);

    result = round_extended96(0, UINT32_MAX, UINT32_MAX, 0x3fff, 0x80000000, 0);
    assert(result.exponent_word == 0x4000);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 0);

    result = round_extended96(0, 0x80000000, 0, -1, 0, 0);
    assert(result.exponent_word == 0);
    assert(result.significand_high == 0x40000000);
    assert(result.significand_low == 0);

    result = round_extended96(0, 0x80000000, 0x80000003, -1, 0, 0);
    assert(result.exponent_word == 0);
    assert(result.significand_high == 0x40000000);
    assert(result.significand_low == 0x40000002);
}

static void test_extended_multiply(void)
{
    NormalizedBinary64 one = { 0x3fff, 0x80000000, 0 };
    NormalizedBinary64 one_and_half = { 0x3fff, 0xc0000000, 0 };
    NormalizedBinary64 one_and_quarter = { 0x3fff, 0xa0000000, 0 };
    NormalizedBinary64 negative_half = { 0x80003fff, 0xc0000000, 0 };
    NormalizedBinary64 one_plus_epsilon = { 0x3fff, 0x80000000, 1 };
    NormalizedBinary64 scaled_a = { 0x4001, 0x80000000, 0 };
    NormalizedBinary64 scaled_b = { 0x4000, 0x80000000, 0 };

    NormalizedBinary64 result = multiply_extended96(&one, &one, 0);
    assert(result.exponent_word == 0x3fff);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 0);

    result = multiply_extended96(&one_and_half, &one_and_quarter, 0);
    assert(result.exponent_word == 0x3fff);
    assert(result.significand_high == 0xf0000000);
    assert(result.significand_low == 0);

    result = multiply_extended96(&negative_half, &one_and_quarter, 0);
    assert(result.exponent_word == 0x80003fff);
    assert(result.significand_high == 0xf0000000);
    assert(result.significand_low == 0);

    result = multiply_extended96(&one_plus_epsilon, &one_plus_epsilon, 0);
    assert(result.exponent_word == 0x3fff);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 2);

    result = multiply_extended96(&scaled_a, &scaled_b, 0);
    assert(result.exponent_word == 0x4002);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 0);
}

static void test_extended_divide(void)
{
    NormalizedBinary64 one = { 0x3fff, 0x80000000, 0 };
    NormalizedBinary64 one_and_half = { 0x3fff, 0xc0000000, 0 };
    NormalizedBinary64 one_and_quarter = { 0x3fff, 0xa0000000, 0 };
    NormalizedBinary64 negative_half = { 0x80003fff, 0xc0000000, 0 };
    NormalizedBinary64 scaled_a = { 0x4001, 0x80000000, 0 };
    NormalizedBinary64 scaled_b = { 0x4000, 0x80000000, 0 };
    NormalizedBinary64 one_plus_epsilon = { 0x3fff, 0x80000000, 1 };

    NormalizedBinary64 result = divide_extended96(&one, &one, 0);
    assert(result.exponent_word == 0x3fff);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 0);

    result = divide_extended96(&one_and_half, &one_and_quarter, 0);
    assert(result.exponent_word == 0x3fff);
    assert(result.significand_high == 0x99999999);
    assert(result.significand_low == 0x9999999a);

    result = divide_extended96(&negative_half, &one_and_quarter, 0);
    assert(result.exponent_word == 0x80003fff);
    assert(result.significand_high == 0x99999999);
    assert(result.significand_low == 0x9999999a);

    result = divide_extended96(&scaled_a, &scaled_b, 0);
    assert(result.exponent_word == 0x4000);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 0);

    result = divide_extended96(&one_plus_epsilon, &one, 0);
    assert(result.exponent_word == 0x3fff);
    assert(result.significand_high == 0x80000000);
    assert(result.significand_low == 0);

    result = divide_extended96(&one, &one_plus_epsilon, 0);
    assert(result.exponent_word == 0x3fff);
    assert(result.significand_high == UINT32_MAX);
    assert(result.significand_low == 0xfffffffe);
}

static void test_hexadecimal_float(void)
{
    static const char default_format[] = "%a";
    static const char precision_format[] = "%.1a";
    static const char uppercase_format[] = "%A";
    static const char infinity_format[] = "%+012a";
    static const char subnormal_format[] = "%a";
    static const char signed_zero_format[] = "%a";
    static const char alternate_zero_precision_format[] = "%#.0a";
    static const double one_and_half = 1.5;
    static const double rounded_up = 1.96875;
    static const double infinity = INFINITY;
    static const uint64_t minimum_subnormal_bits = 1;
    static const double negative_zero = -0.0;
    FormatContext context;
    _Alignas(8) uint32_t arguments[2];

    memcpy(arguments, &one_and_half, sizeof(one_and_half));
    initialize_context(&context, default_format);
    assert(format_to_sink(&context, arguments) == 20);
    assert_output("0x1.8000000000000p+0");

    memcpy(arguments, &rounded_up, sizeof(rounded_up));
    initialize_context(&context, precision_format);
    assert(format_to_sink(&context, arguments) == 8);
    assert_output("0x1.0p+1");

    memcpy(arguments, &one_and_half, sizeof(one_and_half));
    initialize_context(&context, uppercase_format);
    assert(format_to_sink(&context, arguments) == 20);
    assert_output("0X1.8000000000000P+0");

    memcpy(arguments, &infinity, sizeof(infinity));
    initialize_context(&context, infinity_format);
    assert(format_to_sink(&context, arguments) == 12);
    assert_output("        +inf");

    memcpy(arguments, &minimum_subnormal_bits, sizeof(minimum_subnormal_bits));
    initialize_context(&context, subnormal_format);
    assert(format_to_sink(&context, arguments) == 23);
    assert_output("0x1.0000000000000p-1074");

    memcpy(arguments, &negative_zero, sizeof(negative_zero));
    initialize_context(&context, signed_zero_format);
    assert(format_to_sink(&context, arguments) == 21);
    assert_output("-0x0.0000000000000p+0");

    memcpy(arguments, &one_and_half, sizeof(one_and_half));
    initialize_context(&context, alternate_zero_precision_format);
    assert(format_to_sink(&context, arguments) == 7);
    assert_output("0x1.p+0");
}

int main(void)
{
    test_literal_output();
    test_flags_and_fields();
    test_negative_star_fields();
    test_padding_and_precision();
    test_integer_conversions();
    test_pointer_string_and_character();
    test_count_and_long_long();
    test_numeric_edge_cases();
    test_wide_output_modes();
    test_formatting_edge_cases();
    test_hexadecimal_float();
    test_format_wrappers();
    test_u16_buffer_write();
    test_format_to_buffer();
    test_bounded_string_copy();
    test_find_last_character();
    test_character_class();
    test_find_wide_character();
    run_constructor_tests();
    run_locale_tests();
    run_runtime_tests();
    run_system_state_tests();
    run_sleep_state_tests();
    run_stack_setup_tests();
    run_process_state_tests();
    run_sleep_wait_tests();
    run_runtime_wrapper_tests();
    test_u64_divmod_by_ten();
    test_binary64_normalization();
    test_binary64_classification();
    test_extended_rounding();
    test_extended_multiply();
    test_extended_divide();
    return 0;
}