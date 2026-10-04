#include <stdint.h>

int32_t wait_for_sleep_mode(uint32_t process_state, uint32_t service_state);
void store_runtime_flag(uint8_t *target, uint8_t value);
uint32_t compute_stack_size(int32_t current_top, int32_t heap_end);
uint8_t get_process_flags(const uint8_t *process_state);
uint8_t get_service_state(const uint8_t *service_block);

static int32_t setup_thread_and_pool(void)
{
    return -1;
}

static int32_t create_service_thread(void)
{
    return -1;
}

void initialize_runtime(uint8_t *runtime_flag)
{
    uint8_t process_state = 0;
    uint8_t service_state = 0;

    wait_for_sleep_mode((uint32_t)(uintptr_t)&process_state,
        (uint32_t)(uintptr_t)&service_state);
    store_runtime_flag(runtime_flag, 0);
    compute_stack_size(0, 0);
    setup_thread_and_pool();
    create_service_thread();
}
