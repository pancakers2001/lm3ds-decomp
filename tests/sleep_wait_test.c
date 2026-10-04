#include <assert.h>
#include <stdint.h>
#include <string.h>

int32_t wait_for_sleep_mode(uint32_t process_state, uint32_t service_state);

static uint8_t service_block[4];

void run_sleep_wait_tests(void)
{
    assert(wait_for_sleep_mode(1, 0) == 0);
    service_block[2] = 1;
    assert(wait_for_sleep_mode(0, (uint32_t)(uintptr_t)service_block) == 0);
}
