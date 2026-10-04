#include "format_context.h"

uint32_t read_format_byte(FormatContext *context)
{
    const uint8_t *input = (const uint8_t *)(uintptr_t)context->input;
    context->input += 1;
    return *input;
}

uint32_t read_format_utf16(FormatContext *context)
{
    const uint16_t *input = (const uint16_t *)(uintptr_t)context->input;
    context->input += 2;
    return *input;
}

void write_buffer_character(uint32_t character, uint32_t cursor)
{
    uint8_t **position = (uint8_t **)(uintptr_t)cursor;
    uint8_t *write_at = *position;
    *write_at = (uint8_t)character;
    *position = write_at + 1;
}

uint32_t format_string_to_sink(
    const char *format,
    uint32_t write_context,
    uint32_t *arguments,
    FormatWriteCallback write_callback)
{
    FormatContext context;
    context.write_callback = (uint32_t)(uintptr_t)write_callback;
    context.write_context = write_context;
    context.read_callback = (uint32_t)(uintptr_t)read_format_byte;
    context.input = (uint32_t)(uintptr_t)format;
    context.mode = 0;
    return format_to_sink(&context, arguments);
}

uint32_t format_wstring_to_sink(
    const uint16_t *format,
    uint32_t write_context,
    uint32_t *arguments,
    FormatWriteCallback write_callback)
{
    FormatContext context;
    context.write_callback = (uint32_t)(uintptr_t)write_callback;
    context.write_context = write_context;
    context.read_callback = (uint32_t)(uintptr_t)read_format_utf16;
    context.input = (uint32_t)(uintptr_t)format;
    context.mode = 1;
    return format_to_sink(&context, arguments);
}

uint32_t format_to_buffer(
    char *buffer,
    const char *format,
    uint32_t *arguments)
{
    static uint8_t *cursor;
    cursor = (uint8_t *)buffer;
    uint32_t count = format_string_to_sink(format,
        (uint32_t)(uintptr_t)&cursor, arguments, write_buffer_character);
    write_buffer_character(0, (uint32_t)(uintptr_t)&cursor);
    return count;
}

void copy_string_bounded(char *destination, const char *source, uint32_t limit)
{
    char *write_at = destination;
    for (;;) {
        if (limit == 0) {
            *write_at = '\0';
            return;
        }
        --limit;
        char character = *source++;
        *write_at++ = character;
        if (character == '\0') {
            return;
        }
    }
}

char *find_last_character(char *string, char target)
{
    char *result = NULL;
    char *cursor = string;
    for (;;) {
        char character = *cursor;
        if (character == target) {
            result = cursor;
        }
        if (character == '\0') {
            return result;
        }
        ++cursor;
    }
}

static const uint8_t character_class_table[256] = {
    [0x20] = 1, [0x21] = 1, [0x22] = 1, [0x23] = 1, [0x24] = 1,
    [0x25] = 1, [0x26] = 1, [0x27] = 1, [0x28] = 1, [0x29] = 1,
    [0x2a] = 1, [0x2b] = 1, [0x2c] = 1, [0x2d] = 1, [0x2e] = 1,
    [0x2f] = 1, [0x30] = 1, [0x31] = 1, [0x32] = 1, [0x33] = 1,
    [0x34] = 1, [0x35] = 1, [0x36] = 1, [0x37] = 1, [0x38] = 1,
    [0x39] = 1, [0x3a] = 1, [0x3b] = 1, [0x3c] = 1, [0x3d] = 1,
    [0x3e] = 1, [0x3f] = 1, [0x40] = 1, [0x41] = 1, [0x42] = 1,
    [0x43] = 1, [0x44] = 1, [0x45] = 1, [0x46] = 1, [0x47] = 1,
    [0x48] = 1, [0x49] = 1, [0x4a] = 1, [0x4b] = 1, [0x4c] = 1,
    [0x4d] = 1, [0x4e] = 1, [0x4f] = 1, [0x50] = 1, [0x51] = 1,
    [0x52] = 1, [0x53] = 1, [0x54] = 1, [0x55] = 1, [0x56] = 1,
    [0x57] = 1, [0x58] = 1, [0x59] = 1, [0x5a] = 1, [0x5b] = 1,
    [0x5c] = 1, [0x5d] = 1, [0x5e] = 1, [0x5f] = 1, [0x60] = 1,
    [0x61] = 1, [0x62] = 1, [0x63] = 1, [0x64] = 1, [0x65] = 1,
    [0x66] = 1, [0x67] = 1, [0x68] = 1, [0x69] = 1, [0x6a] = 1,
    [0x6b] = 1, [0x6c] = 1, [0x6d] = 1, [0x6e] = 1, [0x6f] = 1,
    [0x70] = 1, [0x71] = 1, [0x72] = 1, [0x73] = 1, [0x74] = 1,
    [0x75] = 1, [0x76] = 1, [0x77] = 1, [0x78] = 1, [0x79] = 1,
    [0x7a] = 1, [0x7b] = 1, [0x7c] = 1, [0x7d] = 1, [0x7e] = 1,
    [0x7f] = 1
};

uint8_t is_character_class(uint32_t character)
{
    return character_class_table[character & 0xff] & 1;
}

int find_wide_character(const uint16_t *string, uint32_t length, uint32_t target)
{
    for (uint32_t index = 0; index < length; ++index) {
        if (string[index] == (uint16_t)target) {
            return 1;
        }
    }
    return 0;
}
