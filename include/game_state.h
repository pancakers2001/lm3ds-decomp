#ifndef LM3DS_GAME_STATE_H
#define LM3DS_GAME_STATE_H

#include "system_interface.h"
#include <stdint.h>

typedef struct GameContext GameContext;
typedef struct GameObject GameObject;
typedef struct GameService GameService;
typedef struct GameThread GameThread;

struct GameObject {
    uint32_t type;
    uint32_t flags;
    void *data;
    GameObject *next;
    GameObject *prev;
};

struct GameService {
    uint32_t type;
    uint32_t state;
    Handle handle;
    void *data;
    GameService *next;
};

struct GameThread {
    uint32_t id;
    uint32_t priority;
    uint32_t state;
    void *stack;
    void *argument;
    GameThread *next;
};

struct GameContext {
    GameObject *objects;
    GameService *services;
    GameThread *threads;
    uint32_t frame_count;
    uint32_t state;
    void *allocator;
    void *resource_manager;
};

GameContext *game_context_create(void);
void game_context_destroy(GameContext *context);
Result game_context_initialize(GameContext *context);
Result game_context_run(GameContext *context);
void game_context_shutdown(GameContext *context);

GameObject *game_object_create(GameContext *context, uint32_t type, void *data);
void game_object_destroy(GameContext *context, GameObject *object);
Result game_object_initialize(GameObject *object);
void game_object_update(GameObject *object);
void game_object_render(GameObject *object);

GameService *game_service_create(GameContext *context, uint32_t type, const char *name);
void game_service_destroy(GameContext *context, GameService *service);
Result game_service_initialize(GameService *service);
Result game_service_process(GameService *service);
void game_service_shutdown(GameService *service);

GameThread *game_thread_create(GameContext *context, void (*entry)(void *), void *argument);
void game_thread_destroy(GameContext *context, GameThread *thread);
Result game_thread_start(GameThread *thread);
Result game_thread_join(GameThread *thread);
void game_thread_suspend(GameThread *thread);
void game_thread_resume(GameThread *thread);

int validate_game_mode(uint32_t mode);
uint32_t get_game_version_tag(void);
uint32_t get_game_build_tag(void);
void initialize_game_entry(uint32_t *entry, uint32_t type_tag);
void initialize_name_entry(uint32_t *entry, uint32_t type_tag, const char *name);
void clear_object_counters(uint32_t *object);
void initialize_command_entry(uint32_t *entry, uint32_t type_tag, uint32_t mode,
                              uint32_t address, uint32_t size);

#endif
