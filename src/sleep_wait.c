#include <stdint.h>

typedef struct {
    uint32_t list_head;
    uint32_t field_4;
    uint32_t field_8;
    uint32_t field_c;
    uint32_t field_10;
    uint8_t initialized;
    uint8_t padding[3];
    uint32_t field_18;
    uint32_t field_1c;
} SleepWaitBlock;

void initialize_sleep_wait_state(uint32_t *state);
uint8_t get_process_flags(const uint8_t *process_state);
uint8_t get_service_state(const uint8_t *service_block);
int claim_once(uint32_t *flag);

static SleepWaitBlock sleep_wait_block;
static uint8_t sleep_wait_initialized;
static uint32_t sleep_wait_lock;

static int32_t wait_for_service(void)
{
    return -5;
}

static void initialize_sleep_wait_block(void)
{
    if (sleep_wait_initialized == 0) {
        sleep_wait_block.list_head = 0;
        initialize_sleep_wait_state(&sleep_wait_block.list_head);
        sleep_wait_block.field_c = 0;
        sleep_wait_block.field_10 = 0;
        sleep_wait_block.initialized = 1;
        sleep_wait_block.field_18 = 0;
        sleep_wait_block.field_1c = 0;
        sleep_wait_initialized = 1;
    }
}

static void sleep_wait_lock_acquire(void)
{
    claim_once(&sleep_wait_lock);
}

static void sleep_wait_lock_release(void)
{
    sleep_wait_lock = 0;
}

int32_t wait_for_sleep_mode(uint32_t process_state, uint32_t service_state)
{
    initialize_sleep_wait_block();

    sleep_wait_lock_acquire();

    int32_t result = 0;
    if (get_process_flags((const uint8_t *)&process_state) != 0) {
        result = 0;
    } else if (get_service_state((const uint8_t *)&service_state) != 0) {
        result = 0;
    } else {
        int32_t status;
        do {
            status = wait_for_service();
        } while (status == -5);
        result = status < 0 ? status : 0;
    }

    sleep_wait_lock_release();
    return result;
}
