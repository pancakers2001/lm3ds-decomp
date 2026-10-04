#include "game_state.h"
#include "system_interface.h"
#include <stddef.h>
#include <stdint.h>

uint32_t get_heap_info_field(void);
int32_t claim_once(uint32_t *flag);
const void *get_system_service_object(void);
const void *initialize_lookup_table(void);

static uint32_t game_once_flag;
static uint32_t game_heap_field;
static const void *game_service_object;

static void game_entry_trampoline(void *argument)
{
    (void)argument;
}

int32_t main_game_entry(void)
{
    (void)game_heap_field;
    (void)game_service_object;

    if (claim_once(&game_once_flag) != 0) {
    }

    GameContext *context = game_context_create();
    if (context == NULL) {
        return -1;
    }

    game_context_initialize(context);

    GameObject *game_object = game_object_create(context, 1, NULL);
    if (game_object != NULL) {
        game_object_initialize(game_object);
    }

    GameService *service = game_service_create(context, 2, "game");
    if (service != NULL) {
        game_service_initialize(service);
    }

    GameThread *thread = game_thread_create(context, game_entry_trampoline, NULL);
    if (thread != NULL) {
        game_thread_start(thread);
    }

    game_context_run(context);

    if (thread != NULL) {
        game_thread_join(thread);
    }

    game_context_shutdown(context);
    game_context_destroy(context);

    return 0;
}
