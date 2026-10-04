#include <stdint.h>

uint32_t get_heap_info_field(const uint32_t *heap_info)
{
    return heap_info[2];
}

const void *get_system_service_object(const void *object)
{
    return object;
}

int claim_once(uint32_t *flag)
{
    if ((*flag & 1) != 0) {
        return 0;
    }
    *flag = 1;
    return 1;
}

typedef struct {
    uint32_t entries[21];
    uint8_t tail[3];
} LookupTable;

LookupTable *initialize_lookup_table(uint32_t *once_flag, LookupTable *table)
{
    if ((*once_flag & 1) == 0 && claim_once(once_flag) != 0) {
        table->entries[0] = 0;
        for (int index = 1; index < 19; ++index) {
            table->entries[index] = 0;
        }
        table->entries[19] = 0x3f800000;
        table->entries[20] = 0x3f800000;
        table->tail[0] = 0;
        table->tail[1] = 0;
        table->tail[2] = 0;
    }
    return table;
}
