#include <assert.h>
#include <stdint.h>
#include <string.h>

void initialize_list_head(uint32_t *head);

typedef struct {
    uint32_t list_head;
    uint32_t field_4;
    uint32_t field_8;
} SleepWaitState;

void initialize_sleep_wait_state(SleepWaitState *state);

void run_sleep_state_tests(void)
{
    uint32_t head = 0;
    initialize_list_head(&head);
    assert(head == 1);

    SleepWaitState state;
    memset(&state, 0xff, sizeof(state));
    initialize_sleep_wait_state(&state);
    assert(state.list_head == 1);
    assert(state.field_4 == 0);
    assert(state.field_8 == 0);
}
