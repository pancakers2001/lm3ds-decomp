#include <stdint.h>

typedef void (*StaticConstructor)(void);

void run_relocations_and_ctors(uint32_t *table, uint32_t *table_end)
{
    for (uint32_t *entry = table; entry != table_end; ++entry) {
        uint32_t target = *entry + (uint32_t)(uintptr_t)entry;
        StaticConstructor constructor = (StaticConstructor)(uintptr_t)target;
        constructor();
    }
}

void run_static_ctors(StaticConstructor *table, StaticConstructor *table_end)
{
    for (StaticConstructor *entry = table; entry < table_end; ++entry) {
        (*entry)();
    }
}
