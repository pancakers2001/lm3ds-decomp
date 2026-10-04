#include <assert.h>
#include <stdint.h>
#include <string.h>

uint32_t get_heap_info_field(const uint32_t *heap_info);
const void *get_system_service_object(const void *object);
int claim_once(uint32_t *flag);

typedef struct {
    uint32_t entries[21];
    uint8_t tail[3];
} LookupTable;

LookupTable *initialize_lookup_table(uint32_t *once_flag, LookupTable *table);

static uint32_t heap_info[4];
static int service_object;
static uint32_t once_flag;
static LookupTable table;

void run_system_state_tests(void)
{
    heap_info[2] = 0xdeadbeef;
    assert(get_heap_info_field(heap_info) == 0xdeadbeef);

    assert(get_system_service_object(&service_object) == &service_object);

    once_flag = 0;
    assert(claim_once(&once_flag) == 1);
    assert(once_flag == 1);
    assert(claim_once(&once_flag) == 0);

    memset(&table, 0xff, sizeof(table));
    once_flag = 0;
    LookupTable *result = initialize_lookup_table(&once_flag, &table);
    assert(result == &table);
    assert(once_flag == 1);
    for (int index = 0; index < 19; ++index) {
        assert(table.entries[index] == 0);
    }
    assert(table.entries[19] == 0x3f800000);
    assert(table.entries[20] == 0x3f800000);
    assert(table.tail[0] == 0 && table.tail[1] == 0 && table.tail[2] == 0);

    memset(&table, 0xff, sizeof(table));
    result = initialize_lookup_table(&once_flag, &table);
    assert(result == &table);
    assert(table.entries[0] == 0xffffffff);
}
