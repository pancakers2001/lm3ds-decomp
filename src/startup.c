#include <stdint.h>

void initialize_bss(void)
{
    volatile uint32_t *cursor = (volatile uint32_t *)(uintptr_t)0x004C0A94;
    volatile uint32_t *limit = (volatile uint32_t *)(uintptr_t)0x005220F0;

    while (cursor < limit) {
        *cursor++ = 0;
    }
}