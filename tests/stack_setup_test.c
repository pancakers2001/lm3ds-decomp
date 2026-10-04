#include <assert.h>
#include <stdint.h>
#include <string.h>

uint32_t get_heap_info_field_deep(const uint32_t *heap_info);
uint32_t compute_stack_size(int32_t current_top, int32_t heap_end);

typedef struct {
    uint32_t list_head;
    uint32_t field_4;
    uint32_t field_8;
} SleepWaitState;

void initialize_sleep_wait_state(SleepWaitState *state);

typedef struct {
    uint32_t region_start;
    uint32_t region_end;
    uint32_t field_8;
    SleepWaitState wait_state;
    int32_t last_error;
    uint32_t field_14;
} StackRegion;

void initialize_stack_region(StackRegion *region, uint32_t start, uint32_t size);

void run_stack_setup_tests(void)
{
    static uint32_t heap_info[17];
    heap_info[16] = 0xcafebabe;
    assert(get_heap_info_field_deep(heap_info) == 0xcafebabe);

    assert(compute_stack_size(0x1000000, 0) == 0x1000000);
    assert(compute_stack_size(0x8000000, 0) == 0x4000000);
    assert(compute_stack_size(0x1000000, 0x800000) == 0x800000);
    assert(compute_stack_size(0x1000000, 0x1000000) == 0);

    StackRegion region;
    memset(&region, 0, sizeof(region));
    initialize_stack_region(&region, 0x1000, 0x4000);
    assert(region.region_start == 0x1000);
    assert(region.region_end == 0x5000);
    assert(region.wait_state.list_head == 1);
    assert(region.wait_state.field_4 == 0);
    assert(region.wait_state.field_8 == 0);

    memset(&region, 0, sizeof(region));
    region.region_start = 0xdead;
    initialize_stack_region(&region, 0x1000, 0x4000);
    assert(region.region_start == 0xdead);
    assert(region.region_end == 0);
}
