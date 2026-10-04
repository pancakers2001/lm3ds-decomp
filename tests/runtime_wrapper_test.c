#include <assert.h>
#include <stdint.h>

void initialize_runtime(uint8_t *runtime_flag);

static uint8_t runtime_flag;

void run_runtime_wrapper_tests(void)
{
    runtime_flag = 1;
    initialize_runtime(&runtime_flag);
    assert(runtime_flag == 0);
}
