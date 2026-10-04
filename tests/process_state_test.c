#include <assert.h>
#include <stdint.h>

uint8_t get_process_flags(const uint8_t *process_state);
uint8_t get_service_state(const uint8_t *service_block);

static uint8_t process_state;
static uint8_t service_block[4];

void run_process_state_tests(void)
{
    process_state = 0;
    assert(get_process_flags(&process_state) == 0);
    process_state = 0xff;
    assert(get_process_flags(&process_state) == 0xff);

    service_block[2] = 0;
    assert(get_service_state(service_block) == 0);
    service_block[2] = 0xa5;
    assert(get_service_state(service_block) == 0xa5);
}
