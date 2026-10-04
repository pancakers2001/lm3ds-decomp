#include "game_state.h"
#include "system_interface.h"
#include <stdlib.h>
#include <string.h>

GameContext *game_context_create(void)
{
    return calloc(1, sizeof(GameContext));
}

void game_context_destroy(GameContext *context)
{
    free(context);
}

Result game_context_initialize(GameContext *context)
{
    context->objects = NULL;
    context->services = NULL;
    context->threads = NULL;
    context->frame_count = 0;
    context->state = 0;
    context->allocator = NULL;
    context->resource_manager = NULL;
    return 0;
}

Result game_context_run(GameContext *context)
{
    (void)context;
    return 0;
}

void game_context_shutdown(GameContext *context)
{
    (void)context;
}

GameObject *game_object_create(GameContext *context, uint32_t type, void *data)
{
    GameObject *object = calloc(1, sizeof(GameObject));
    object->type = type;
    object->data = data;
    object->next = context->objects;
    context->objects = object;
    return object;
}

void game_object_destroy(GameContext *context, GameObject *object)
{
    (void)context;
    free(object);
}

Result game_object_initialize(GameObject *object)
{
    (void)object;
    return 0;
}

void game_object_update(GameObject *object)
{
    (void)object;
}

void game_object_render(GameObject *object)
{
    (void)object;
}

GameService *game_service_create(GameContext *context, uint32_t type, const char *name)
{
    (void)name;
    GameService *service = calloc(1, sizeof(GameService));
    service->type = type;
    service->next = context->services;
    context->services = service;
    return service;
}

void game_service_destroy(GameContext *context, GameService *service)
{
    (void)context;
    free(service);
}

Result game_service_initialize(GameService *service)
{
    (void)service;
    return 0;
}

Result game_service_process(GameService *service)
{
    (void)service;
    return 0;
}

void game_service_shutdown(GameService *service)
{
    (void)service;
}

GameThread *game_thread_create(GameContext *context, void (*entry)(void *), void *argument)
{
    (void)entry;
    (void)argument;
    GameThread *thread = calloc(1, sizeof(GameThread));
    thread->next = context->threads;
    context->threads = thread;
    return thread;
}

void game_thread_destroy(GameContext *context, GameThread *thread)
{
    (void)context;
    free(thread);
}

Result game_thread_start(GameThread *thread)
{
    (void)thread;
    return 0;
}

Result game_thread_join(GameThread *thread)
{
    (void)thread;
    return 0;
}

void game_thread_suspend(GameThread *thread)
{
    (void)thread;
}

void game_thread_resume(GameThread *thread)
{
    (void)thread;
}
