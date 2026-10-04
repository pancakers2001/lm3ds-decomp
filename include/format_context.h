#ifndef LM3DS_FORMAT_CONTEXT_H
#define LM3DS_FORMAT_CONTEXT_H

#include <stddef.h>
#include <stdint.h>

enum {
    FORMAT_FLAG_LEFT_JUSTIFY = 0x01,
    FORMAT_FLAG_PLUS = 0x02,
    FORMAT_FLAG_SPACE = 0x04,
    FORMAT_FLAG_ALTERNATE = 0x08,
    FORMAT_FLAG_ZERO_PAD = 0x10,
    FORMAT_FLAG_HAS_PRECISION = 0x20,
    FORMAT_FLAG_LONG = 0x40,
    FORMAT_FLAG_INTMAX = 0x80,
    FORMAT_FLAG_SHORT = 0x100,
    FORMAT_FLAG_SHORT_SHORT = 0x400,
    FORMAT_FLAG_UPPERCASE = 0x800
};

enum {
    FORMAT_CONTEXT_BUFFER_SIZE = 24,
    FORMAT_CONTEXT_SIZE = 0x3c
};

typedef struct FormatContext FormatContext;

typedef void (*FormatWriteCallback)(uint32_t character, uint32_t context);
typedef uint32_t (*FormatReadCallback)(FormatContext *context);

struct FormatContext {
    uint32_t flags;
    uint32_t write_callback;
    uint32_t write_context;
    uint32_t read_callback;
    uint32_t input;
    uint32_t mode;
    int32_t width;
    uint32_t precision;
    uint32_t output_count;
    uint8_t conversion_buffer[FORMAT_CONTEXT_BUFFER_SIZE];
};

_Static_assert(offsetof(FormatContext, write_callback) == 0x04, "write callback offset");
_Static_assert(offsetof(FormatContext, read_callback) == 0x0C, "read callback offset");
_Static_assert(offsetof(FormatContext, mode) == 0x14, "mode offset");
_Static_assert(offsetof(FormatContext, width) == 0x18, "width offset");
_Static_assert(offsetof(FormatContext, precision) == 0x1C, "precision offset");
_Static_assert(offsetof(FormatContext, output_count) == 0x20, "output count offset");
_Static_assert(offsetof(FormatContext, conversion_buffer) == 0x24, "conversion buffer offset");
_Static_assert(sizeof(FormatContext) == FORMAT_CONTEXT_SIZE, "context size");

void format_pad_before(FormatContext *context);
void format_pad_after(FormatContext *context);
void emit_formatted_bytes(FormatContext *context, const uint8_t *bytes, uint32_t length);
void write_u16_to_buffer(uint16_t value, uint16_t **cursor, uint16_t *limit);
uint32_t format_to_sink(FormatContext *context, uint32_t *arguments);
int format_specifier(FormatContext *context, uint32_t specifier, uint32_t *arguments);

uint32_t read_format_byte(FormatContext *context);
uint32_t read_format_utf16(FormatContext *context);
void write_buffer_character(uint32_t character, uint32_t cursor);
uint32_t format_string_to_sink(
    const char *format,
    uint32_t write_context,
    uint32_t *arguments,
    FormatWriteCallback write_callback);
uint32_t format_wstring_to_sink(
    const uint16_t *format,
    uint32_t write_context,
    uint32_t *arguments,
    FormatWriteCallback write_callback);
uint32_t format_to_buffer(
    char *buffer,
    const char *format,
    uint32_t *arguments);
void copy_string_bounded(char *destination, const char *source, uint32_t limit);
char *find_last_character(char *string, char target);
uint8_t is_character_class(uint32_t character);
int find_wide_character(const uint16_t *string, uint32_t length, uint32_t target);

#endif