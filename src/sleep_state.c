#include <stdint.h>

void initialize_list_head(uint32_t *head)
{
    *head = 1;
}

typedef struct {
    uint32_t list_head;
    uint32_t field_4;
    uint32_t field_8;
} SleepWaitState;

void initialize_sleep_wait_state(SleepWaitState *state)
{
    initialize_list_head(&state->list_head);
    state->field_4 = 0;
    state->field_8 = 0;
}
