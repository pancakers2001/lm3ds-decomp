#include "format_context.h"

static uint32_t read_format_character(FormatContext *context)
{
    FormatReadCallback callback =
        (FormatReadCallback)(uintptr_t)context->read_callback;
    return callback(context);
}

static void write_format_character(FormatContext *context, uint32_t character)
{
    FormatWriteCallback callback =
        (FormatWriteCallback)(uintptr_t)context->write_callback;
    callback(character, context->write_context);
}

static uint32_t flag_for_character(uint32_t character)
{
    switch (character) {
    case ' ':
        return FORMAT_FLAG_SPACE;
    case '#':
        return FORMAT_FLAG_ALTERNATE;
    case '+':
        return FORMAT_FLAG_PLUS;
    case '-':
        return FORMAT_FLAG_LEFT_JUSTIFY;
    case '0':
        return FORMAT_FLAG_ZERO_PAD;
    default:
        return 0;
    }
}

static int is_decimal_digit(uint32_t character)
{
    return character >= '0' && character <= '9';
}

static uint32_t *align_argument_cursor(uint32_t *arguments)
{
    uintptr_t address = (uintptr_t)arguments;
    return (uint32_t *)(((address + 7u) & ~(uintptr_t)7u) + 8u);
}

uint32_t format_to_sink(FormatContext *context, uint32_t *arguments)
{
    uint32_t character;

    context->output_count = 0;
    for (;;) {
        character = read_format_character(context);
        if (character == '\0') {
            return context->output_count;
        }
        if (character != '%') {
            write_format_character(context, character);
            ++context->output_count;
            continue;
        }

        uint32_t flags = 0;
        for (;;) {
            uint32_t flag = flag_for_character(character = read_format_character(context));
            if (flag == 0) {
                break;
            }
            flags |= flag;
        }
        if ((flags & FORMAT_FLAG_PLUS) != 0) {
            flags &= ~FORMAT_FLAG_SPACE;
        }

        context->width = 0;
        context->precision = 0;
        int field_index = 0;
        do {
            if (character == '*') {
                int32_t field = (int32_t)*arguments++;
                if (field_index == 0) {
                    context->width = field;
                } else {
                    context->precision = (uint32_t)field;
                    if (field < 0) {
                        flags &= ~FORMAT_FLAG_HAS_PRECISION;
                    }
                    character = read_format_character(context);
                    break;
                }
                character = read_format_character(context);
            } else if (is_decimal_digit(character)) {
                uint32_t field = character - '0';
                for (;;) {
                    character = read_format_character(context);
                    if (!is_decimal_digit(character)) {
                        break;
                    }
                    field = field * 10 + character - '0';
                }
                if (field_index == 0) {
                    context->width = (int32_t)field;
                } else {
                    context->precision = field;
                }
                if (field_index == 1) {
                    break;
                }
            } else if (field_index == 1) {
                break;
            }

            if (character != '.') {
                break;
            }
            character = read_format_character(context);
            flags |= FORMAT_FLAG_HAS_PRECISION;
            ++field_index;
        } while (field_index < 2);

        if (context->width < 0) {
            context->width = -context->width;
            flags |= FORMAT_FLAG_LEFT_JUSTIFY;
        }
        if ((flags & FORMAT_FLAG_LEFT_JUSTIFY) != 0) {
            flags &= ~FORMAT_FLAG_ZERO_PAD;
        }

        if (character == 'l' || character == 'h') {
            uint32_t next = read_format_character(context);
            if (next == character) {
                flags |= character == 'l' ? FORMAT_FLAG_INTMAX : FORMAT_FLAG_SHORT_SHORT;
                character = read_format_character(context);
            } else {
                flags |= character == 'l' ? FORMAT_FLAG_LONG : FORMAT_FLAG_SHORT;
                character = next;
            }
        } else if (character == 'j') {
            flags |= FORMAT_FLAG_INTMAX;
            character = read_format_character(context);
        } else if (character == 'L' || character == 't' || character == 'z') {
            character = read_format_character(context);
        }

        if (character == '\0') {
            return context->output_count;
        }
        if (character >= 'A' && character <= 'Z') {
            flags |= FORMAT_FLAG_UPPERCASE;
            character += 'a' - 'A';
        }

        context->flags = flags;
        int consumed = format_specifier(context, character, arguments);
        if (consumed == 1) {
            ++arguments;
        } else if (consumed != 0) {
            arguments = align_argument_cursor(arguments);
        } else {
            write_format_character(context, character);
            ++context->output_count;
        }
    }
}