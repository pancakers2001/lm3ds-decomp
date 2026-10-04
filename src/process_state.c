#include <stdint.h>

uint8_t get_process_flags(const uint8_t *process_state)
{
    return *process_state;
}

uint8_t get_service_state(const uint8_t *service_block)
{
    return service_block[2];
}
