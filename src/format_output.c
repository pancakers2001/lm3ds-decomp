#include "format_context.h"

static void write_character(FormatContext *context, uint32_t character)
{
    FormatWriteCallback callback =
        (FormatWriteCallback)(uintptr_t)context->write_callback;
    callback(character, context->write_context);
}

void format_pad_before(FormatContext *context)
{
    uint32_t character = (context->flags & FORMAT_FLAG_ZERO_PAD) != 0 ? '0' : ' ';

    if ((context->flags & FORMAT_FLAG_LEFT_JUSTIFY) != 0) {
        return;
    }

    for (int32_t remaining = context->width; remaining > 0; --remaining) {
        write_character(context, character);
        ++context->output_count;
    }
}

void format_pad_after(FormatContext *context)
{
    if ((context->flags & FORMAT_FLAG_LEFT_JUSTIFY) == 0) {
        return;
    }

    for (int32_t remaining = context->width; remaining > 0; --remaining) {
        write_character(context, ' ');
        ++context->output_count;
    }
}

void emit_formatted_bytes(FormatContext *context, const uint8_t *bytes, uint32_t length)
{
    uint32_t emitted;

    if (length == 1) {
        emitted = 1;
    } else {
        if ((context->flags & FORMAT_FLAG_HAS_PRECISION) != 0) {
            length = context->precision;
        }

        for (emitted = 0; emitted < length && bytes[emitted] != '\0'; ++emitted) {
        }
    }

    context->width -= (int32_t)emitted;
    context->output_count += emitted;
    format_pad_before(context);

    for (uint32_t index = 0; index < emitted; ++index) {
        write_character(context, bytes[index]);
    }

    format_pad_after(context);
}

void write_u16_to_buffer(uint16_t value, uint16_t **cursor, uint16_t *limit)
{
    uint16_t *position = *cursor;
    if (position < limit) {
        *cursor = position + 1;
        *position = value;
    }
}