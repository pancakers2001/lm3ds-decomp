#include <stdint.h>

typedef struct {
    uint32_t list_head;
    uint32_t field_4;
    uint32_t field_8;
} SleepWaitState;

void initialize_sleep_wait_state(SleepWaitState *state);

uint32_t get_heap_info_field_deep(const uint32_t *heap_info)
{
    return heap_info[16];
}

uint32_t compute_stack_size(int32_t current_top, int32_t heap_end)
{
    uint32_t system_limit = 0x4000000 - (uint32_t)heap_end;
    uint32_t available = (uint32_t)(current_top - heap_end);
    if (system_limit < available) {
        return system_limit;
    }
    return available;
}

typedef struct {
    uint32_t region_start;
    uint32_t region_end;
    uint32_t field_8;
    SleepWaitState wait_state;
    int32_t last_error;
    uint32_t field_14;
} StackRegion;

void initialize_stack_region(StackRegion *region, uint32_t start, uint32_t size)
{
    if (region->region_start == 0 && region->region_end == 0) {
        initialize_sleep_wait_state(&region->wait_state);
        region->region_end = start + size;
        region->region_start = start;
    }
}
