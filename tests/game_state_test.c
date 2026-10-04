#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "game_state.h"

int32_t main_game_entry(void);

void initialize_game_object(void *object);
void update_game_object(void *object);
void render_game_object(void *object);
uint8_t get_game_object_state(const void *object);
void set_object_flag_bits(uint32_t *flags, uint8_t bits);
void clear_object_flag(uint32_t *flags);
uint32_t get_object_handle(void);
uint32_t get_object_state_handle(void);
void clear_object_bit(uint32_t *bitset, uint32_t bit);
uint32_t get_object_entry(void);
uint32_t find_object_entry(uint32_t table, uint32_t id);
void reset_object_state(uint32_t *state);
void initialize_object_state(uint32_t *state);
void initialize_game_state(uint32_t *state);
void clear_game_flag(uint32_t *flags);
void set_game_flag(uint32_t *flags, uint8_t value);
uint32_t check_game_bounds(uint32_t *bounds, uint32_t value, uint32_t limit);

void run_game_state_tests(void)
{
    GameContext *context = game_context_create();
    assert(context != NULL);

    assert(game_context_initialize(context) == 0);
    assert(game_context_run(context) == 0);

    GameObject *object = game_object_create(context, 1, NULL);
    assert(object != NULL);
    assert(object->type == 1);
    assert(game_object_initialize(object) == 0);
    game_object_update(object);
    game_object_render(object);
    game_object_destroy(context, object);

    GameService *service = game_service_create(context, 2, "test");
    assert(service != NULL);
    assert(service->type == 2);
    assert(game_service_initialize(service) == 0);
    assert(game_service_process(service) == 0);
    game_service_shutdown(service);
    game_service_destroy(context, service);

    GameThread *thread = game_thread_create(context, NULL, NULL);
    assert(thread != NULL);
    assert(game_thread_start(thread) == 0);
    assert(game_thread_join(thread) == 0);
    game_thread_suspend(thread);
    game_thread_resume(thread);
    game_thread_destroy(context, thread);

    game_context_shutdown(context);
    game_context_destroy(context);

    static uint8_t game_object_storage[0x2000];
    initialize_game_object(game_object_storage);
    update_game_object(game_object_storage);
    render_game_object(game_object_storage);
    assert(get_game_object_state(game_object_storage) == 0);

    *(uint8_t *)(game_object_storage + 0x1fc) = 1;
    update_game_object(game_object_storage);
    assert(*(uint8_t *)(game_object_storage + 0x200) == 0);

    *(uint8_t *)(game_object_storage + 0x1fc) = 1;
    *(uint8_t *)(game_object_storage + 0x200) = 5;
    *(uint8_t *)(game_object_storage + 0x201) = 0;
    update_game_object(game_object_storage);
    assert(*(uint8_t *)(game_object_storage + 0x200) == 4);
    assert(*(uint8_t *)(game_object_storage + 0x201) == 1);

    *(uint8_t *)(game_object_storage + 0x1fc) = 1;
    *(uint8_t *)(game_object_storage + 0x200) = 0;
    *(uint8_t *)(game_object_storage + 0x201) = 1;
    update_game_object(game_object_storage);
    assert(*(uint8_t *)(game_object_storage + 0x201) == 0);

    static uint32_t flag_storage[0x100];
    flag_storage[30] = 0xff;
    set_object_flag_bits(flag_storage, 0x05);
    assert((flag_storage[30] & 0xff) == 0xfd);

    flag_storage[127] = 0xff;
    clear_object_flag(flag_storage);
    assert(((uint8_t *)flag_storage)[0x1fd] == 0);

    assert(get_object_handle() == 0);
    assert(get_object_state_handle() == 0);

    static uint32_t bitset_storage[8];
    bitset_storage[0] = 0xffffffff;
    clear_object_bit(bitset_storage, 5);
    assert((bitset_storage[0] & (1 << 5)) == 0);

    assert(get_object_entry() == 0);
    assert(find_object_entry(0, 0) == 0);

    static uint32_t state_storage[32];
    state_storage[0] = 1;
    state_storage[1] = 2;
    state_storage[2] = 3;
    state_storage[3] = 4;
    reset_object_state(state_storage);
    assert(state_storage[0] == 3);
    assert(state_storage[1] == 4);
    assert(state_storage[2] == 0xffffffff);
    assert(state_storage[3] == 0xffffffff);

    initialize_object_state(state_storage);
    assert(state_storage[0] == 0);
    assert(state_storage[31] == 0);

    initialize_game_state(state_storage);
    assert(state_storage[0] == 0);
    assert(state_storage[4] == 0);

    static uint32_t game_flag_storage[0x100];
    game_flag_storage[12] = 0xff;
    clear_game_flag(game_flag_storage);
    assert(((uint8_t *)game_flag_storage)[0x30] == 0);

    set_game_flag(game_flag_storage, 0x42);
    assert(((uint8_t *)game_flag_storage)[0x8f9] == 0x42);
    assert(((uint8_t *)game_flag_storage)[0x8f8] == 1);

    static uint32_t bounds_storage[16];
    bounds_storage[14] = 0x200000;
    bounds_storage[15] = 0x100000;
    assert(check_game_bounds(bounds_storage, 0x150000, 0x100000) == 0);

    assert(validate_game_mode(0) == 1);
    assert(validate_game_mode(11) == 1);
    assert(validate_game_mode(253) == 1);
    assert(validate_game_mode(12) == 0);
    assert(validate_game_mode(254) == 0);

    assert(get_game_version_tag() == 0x38d);
    assert(get_game_build_tag() == 899);

    static uint32_t entry_storage[8];
    initialize_game_entry(entry_storage, 0xdeadbeef);
    assert(entry_storage[0] == 0xdeadbeef);
    assert(((uint8_t *)entry_storage)[4] == 0);
    assert(entry_storage[2] == 0);
    assert(entry_storage[7] == 0);

    static uint32_t name_storage[5];
    initialize_name_entry(name_storage, 0x1234, "Luigi");
    assert(name_storage[0] == 0x1234);
    assert(name_storage[3] == 5);
    assert(((uint8_t *)name_storage)[16] == 1);
    assert(name_storage[2] == 0);

    static uint32_t counter_storage[0x48 / 4];
    counter_storage[0x38 / 4] = 1;
    counter_storage[0x44 / 4] = 2;
    clear_object_counters(counter_storage);
    assert(counter_storage[0x38 / 4] == 0);
    assert(counter_storage[0x3c / 4] == 0);
    assert(counter_storage[0x40 / 4] == 0);
    assert(counter_storage[0x44 / 4] == 0);

    static uint32_t command_storage[4];
    initialize_command_entry(command_storage, 0xaa, 0, 0x150000, 0x40);
    assert(command_storage[0] == 0xaa);
    assert(((uint8_t *)command_storage)[4] == 0);
    assert(command_storage[2] == 0);
    initialize_command_entry(command_storage, 0xbb, 1, 0x150000, 0x40);
    assert(((uint8_t *)command_storage)[4] == 1);
    assert(command_storage[2] == 0x150000);
    assert(command_storage[3] == 0x40);
    initialize_command_entry(command_storage, 0xcc, 1, 0x250000, 0x40);
    assert(((uint8_t *)command_storage)[4] == 0);
    assert(command_storage[2] == 0);
    initialize_command_entry(command_storage, 0xdd, 2, 0x150000, 0x40);
    assert(((uint8_t *)command_storage)[4] == 0);
}

int main(void)
{
    run_game_state_tests();
    assert(main_game_entry() == 0);
    return 0;
}
