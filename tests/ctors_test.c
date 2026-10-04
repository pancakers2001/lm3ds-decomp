#include <assert.h>
#include <stdint.h>

typedef void (*StaticConstructor)(void);
void run_relocations_and_ctors(uint32_t *table, uint32_t *table_end);
void run_static_ctors(StaticConstructor *table, StaticConstructor *table_end);

static int call_order[8];
static int call_count;

static void record_first(void)
{
    call_order[call_count++] = 1;
}

static void record_second(void)
{
    call_order[call_count++] = 2;
}

static void record_third(void)
{
    call_order[call_count++] = 3;
}

void run_constructor_tests(void)
{
    call_count = 0;

    static uint32_t reloc_table[2];
    reloc_table[0] = (uint32_t)(uintptr_t)record_first - (uint32_t)(uintptr_t)&reloc_table[0];
    reloc_table[1] = (uint32_t)(uintptr_t)record_second - (uint32_t)(uintptr_t)&reloc_table[1];
    run_relocations_and_ctors(reloc_table, reloc_table + 2);

    static StaticConstructor absolute_table[] = { record_third };
    run_static_ctors(absolute_table, absolute_table + 1);
    run_static_ctors(absolute_table, absolute_table);

    assert(call_count == 3);
    assert(call_order[0] == 1);
    assert(call_order[1] == 2);
    assert(call_order[2] == 3);
}
