#define _POSIX_C_SOURCE 199309L

#include "system_interface.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

typedef struct {
    pthread_t thread;
    void (*entry)(void *);
    void *argument;
} ThreadData;

static pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t global_condition = PTHREAD_COND_INITIALIZER;

static void use_global_mutex(void)
{
    pthread_mutex_lock(&global_mutex);
    pthread_mutex_unlock(&global_mutex);
}

static void *thread_trampoline(void *data)
{
    ThreadData *thread_data = (ThreadData *)data;
    thread_data->entry(thread_data->argument);
    free(thread_data);
    return NULL;
}

Result svc_exit_thread(void)
{
    pthread_exit(NULL);
    return 0;
}

Result svc_sleep_thread(int64_t nanoseconds)
{
    struct timespec request;
    request.tv_sec = nanoseconds / 1000000000;
    request.tv_nsec = nanoseconds % 1000000000;
    nanosleep(&request, NULL);
    return 0;
}

Result svc_create_mutex(Handle *handle, int initially_locked)
{
    pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mutex, NULL);
    if (initially_locked) {
        pthread_mutex_lock(mutex);
    }
    *handle = (Handle)(uintptr_t)mutex;
    return 0;
}

Result svc_release_mutex(Handle handle)
{
    pthread_mutex_t *mutex = (pthread_mutex_t *)(uintptr_t)handle;
    pthread_mutex_unlock(mutex);
    return 0;
}

Result svc_create_event(Handle *handle, int reset_type)
{
    pthread_cond_t *condition = malloc(sizeof(pthread_cond_t));
    pthread_cond_init(condition, NULL);
    (void)reset_type;
    *handle = (Handle)(uintptr_t)condition;
    return 0;
}

Result svc_signal_event(Handle handle)
{
    pthread_cond_t *condition = (pthread_cond_t *)(uintptr_t)handle;
    pthread_cond_signal(condition);
    return 0;
}

Result svc_clear_event(Handle handle)
{
    pthread_cond_t *condition = (pthread_cond_t *)(uintptr_t)handle;
    pthread_cond_broadcast(condition);
    return 0;
}

Result svc_create_thread(Handle *handle, void (*entry)(void *), void *argument,
    void *stack_top, int priority, int processor)
{
    (void)stack_top;
    (void)priority;
    (void)processor;
    ThreadData *data = malloc(sizeof(ThreadData));
    data->entry = entry;
    data->argument = argument;
    pthread_create(&data->thread, NULL, thread_trampoline, data);
    *handle = (Handle)(uintptr_t)data;
    return 0;
}

Result svc_wait_sync(Handle handle, int64_t timeout)
{
    (void)handle;
    (void)timeout;
    return 0;
}

Result svc_wait_sync2(Handle *handles, uint32_t count, int64_t timeout)
{
    (void)handles;
    (void)count;
    (void)timeout;
    return 0;
}

Result svc_get_thread_id(uint32_t *thread_id)
{
    *thread_id = (uint32_t)(uintptr_t)pthread_self();
    return 0;
}

Result svc_get_process_id(uint32_t *process_id)
{
    *process_id = (uint32_t)getpid();
    return 0;
}

Result svc_get_system_tick(uint64_t *tick)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    *tick = (uint64_t)now.tv_sec * 1000000000 + (uint64_t)now.tv_nsec;
    return 0;
}

Result svc_map_memory(Handle process, void *address, void *source, uint32_t size)
{
    (void)process;
    memcpy(address, source, size);
    return 0;
}

Result svc_unmap_memory(Handle process, void *address, uint32_t size)
{
    (void)process;
    (void)address;
    (void)size;
    return 0;
}

Result svc_create_memory_block(Handle *handle, void *address, uint32_t size,
    uint32_t permissions)
{
    (void)permissions;
    void *block = malloc(size);
    if (address != NULL) {
        memcpy(address, block, size);
    }
    *handle = (Handle)(uintptr_t)block;
    return 0;
}

Result svc_free_memory_block(Handle handle)
{
    free((void *)(uintptr_t)handle);
    return 0;
}

Result svc_query_memory(void *address, uint32_t *info)
{
    (void)address;
    *info = 0;
    return 0;
}

Result svc_exit_process(int32_t status)
{
    exit(status);
    return 0;
}

Result svc_create_address_arbiter(Handle *handle)
{
    use_global_mutex();
    *handle = (Handle)(uintptr_t)&global_condition;
    return 0;
}

Result svc_arbitrate_address(Handle handle, void *address, uint32_t type,
    int32_t value, int64_t timeout)
{
    (void)handle;
    (void)address;
    (void)type;
    (void)value;
    (void)timeout;
    return 0;
}

Result svc_close_handle(Handle handle)
{
    if (handle != 0) {
        free((void *)(uintptr_t)handle);
    }
    return 0;
}

Result svc_output_debug_string(const char *string, uint32_t length)
{
    fwrite(string, 1, length, stderr);
    return 0;
}

Result svc_break(int32_t reason)
{
    (void)reason;
    abort();
    return 0;
}

Result svc_get_resource_limit(Handle *handle)
{
    *handle = 0;
    return 0;
}

Result svc_get_resource_limit_current(Handle handle, uint32_t *values)
{
    (void)handle;
    (void)values;
    return 0;
}

Result svc_get_resource_limit_limit(Handle handle, uint32_t *values)
{
    (void)handle;
    (void)values;
    return 0;
}

Result svc_set_resource_limit(Handle handle, uint32_t *values)
{
    (void)handle;
    (void)values;
    return 0;
}

Result svc_set_resource_limit_current(Handle handle, uint32_t *values)
{
    (void)handle;
    (void)values;
    return 0;
}

Result svc_set_resource_limit_limit(Handle handle, uint32_t *values)
{
    (void)handle;
    (void)values;
    return 0;
}

Result svc_create_session(Handle *handle, const char *name)
{
    (void)name;
    *handle = 0;
    return 0;
}

Result svc_send_sync_request(Handle session)
{
    (void)session;
    return 0;
}

Result svc_get_session(Handle *handle)
{
    *handle = 0;
    return 0;
}

Result svc_close_session(Handle handle)
{
    (void)handle;
    return 0;
}

Result svc_get_process_info(uint32_t *info, uint32_t type)
{
    (void)info;
    (void)type;
    return 0;
}

Result svc_get_thread_info(uint32_t *info, uint32_t type)
{
    (void)info;
    (void)type;
    return 0;
}

Result svc_get_system_info(uint32_t *info, uint32_t type)
{
    (void)info;
    (void)type;
    return 0;
}

Result svc_get_thread_priority(uint32_t *priority, Handle thread)
{
    (void)thread;
    *priority = 0;
    return 0;
}

Result svc_set_thread_priority(Handle thread, uint32_t priority)
{
    (void)thread;
    (void)priority;
    return 0;
}

Result svc_get_thread_core_mask(uint32_t *mask, Handle thread)
{
    (void)thread;
    *mask = 0;
    return 0;
}

Result svc_set_thread_core_mask(Handle thread, uint32_t mask)
{
    (void)thread;
    (void)mask;
    return 0;
}

Result svc_get_thread_context(void *context, Handle thread)
{
    (void)context;
    (void)thread;
    return 0;
}

Result svc_set_thread_context(Handle thread, void *context)
{
    (void)thread;
    (void)context;
    return 0;
}

Result svc_get_thread_argument(uint32_t *argument, Handle thread)
{
    (void)thread;
    *argument = 0;
    return 0;
}

Result svc_set_thread_argument(Handle thread, uint32_t argument)
{
    (void)thread;
    (void)argument;
    return 0;
}

Result svc_get_process_argument(uint32_t *argument, Handle process)
{
    (void)process;
    *argument = 0;
    return 0;
}

Result svc_set_process_argument(Handle process, uint32_t argument)
{
    (void)process;
    (void)argument;
    return 0;
}

Result svc_get_process_affinity(uint32_t *affinity, Handle process)
{
    (void)process;
    *affinity = 0;
    return 0;
}

Result svc_set_process_affinity(Handle process, uint32_t affinity)
{
    (void)process;
    (void)affinity;
    return 0;
}

Result svc_get_process_ideal_processor(uint32_t *processor, Handle process)
{
    (void)process;
    *processor = 0;
    return 0;
}

Result svc_set_process_ideal_processor(Handle process, uint32_t processor)
{
    (void)process;
    (void)processor;
    return 0;
}

Result svc_get_process_list(uint32_t *list, uint32_t count)
{
    (void)list;
    (void)count;
    return 0;
}

Result svc_get_thread_list(uint32_t *list, uint32_t count)
{
    (void)list;
    (void)count;
    return 0;
}

Result svc_get_process_list_of_process(uint32_t *list, uint32_t count, Handle process)
{
    (void)list;
    (void)count;
    (void)process;
    return 0;
}

Result svc_get_thread_list_of_process(uint32_t *list, uint32_t count, Handle process)
{
    (void)list;
    (void)count;
    (void)process;
    return 0;
}

Result svc_get_process_handle(Handle *handle, uint32_t index)
{
    (void)index;
    *handle = 0;
    return 0;
}

Result svc_get_thread_handle(Handle *handle, uint32_t index)
{
    (void)index;
    *handle = 0;
    return 0;
}

Result svc_get_process_handle_count(uint32_t *count)
{
    *count = 0;
    return 0;
}

Result svc_get_thread_handle_count(uint32_t *count)
{
    *count = 0;
    return 0;
}

Result svc_get_process_handle_list(Handle *list, uint32_t count)
{
    (void)list;
    (void)count;
    return 0;
}

Result svc_get_thread_handle_list(Handle *list, uint32_t count)
{
    (void)list;
    (void)count;
    return 0;
}

Result svc_get_process_handle_type(uint32_t *type, Handle handle)
{
    (void)handle;
    *type = 0;
    return 0;
}

Result svc_get_thread_handle_type(uint32_t *type, Handle handle)
{
    (void)handle;
    *type = 0;
    return 0;
}

Result svc_get_process_handle_signal(uint32_t *signal, Handle handle)
{
    (void)handle;
    *signal = 0;
    return 0;
}

Result svc_get_thread_handle_signal(uint32_t *signal, Handle handle)
{
    (void)handle;
    *signal = 0;
    return 0;
}

Result svc_get_process_handle_wait(uint32_t *wait, Handle handle)
{
    (void)handle;
    *wait = 0;
    return 0;
}

Result svc_get_thread_handle_wait(uint32_t *wait, Handle handle)
{
    (void)handle;
    *wait = 0;
    return 0;
}

Result svc_get_process_handle_info(uint32_t *info, Handle handle)
{
    (void)handle;
    *info = 0;
    return 0;
}

Result svc_get_thread_handle_info(uint32_t *info, Handle handle)
{
    (void)handle;
    *info = 0;
    return 0;
}

Result svc_get_process_handle_name(char *name, uint32_t length, Handle handle)
{
    (void)name;
    (void)length;
    (void)handle;
    return 0;
}

Result svc_get_thread_handle_name(char *name, uint32_t length, Handle handle)
{
    (void)name;
    (void)length;
    (void)handle;
    return 0;
}

Result svc_get_process_handle_owner(Handle *owner, Handle handle)
{
    (void)handle;
    *owner = 0;
    return 0;
}

Result svc_get_thread_handle_owner(Handle *owner, Handle handle)
{
    (void)handle;
    *owner = 0;
    return 0;
}

Result svc_get_process_handle_parent(Handle *parent, Handle handle)
{
    (void)handle;
    *parent = 0;
    return 0;
}

Result svc_get_thread_handle_parent(Handle *parent, Handle handle)
{
    (void)handle;
    *parent = 0;
    return 0;
}

Result svc_get_process_handle_children(Handle *children, uint32_t count, Handle handle)
{
    (void)children;
    (void)count;
    (void)handle;
    return 0;
}

Result svc_get_thread_handle_children(Handle *children, uint32_t count, Handle handle)
{
    (void)children;
    (void)count;
    (void)handle;
    return 0;
}

Result svc_get_process_handle_state(uint32_t *state, Handle handle)
{
    (void)handle;
    *state = 0;
    return 0;
}

Result svc_get_thread_handle_state(uint32_t *state, Handle handle)
{
    (void)handle;
    *state = 0;
    return 0;
}

Result svc_get_process_handle_flags(uint32_t *flags, Handle handle)
{
    (void)handle;
    *flags = 0;
    return 0;
}

Result svc_get_thread_handle_flags(uint32_t *flags, Handle handle)
{
    (void)handle;
    *flags = 0;
    return 0;
}

Result svc_get_process_handle_attributes(uint32_t *attributes, Handle handle)
{
    (void)handle;
    *attributes = 0;
    return 0;
}

Result svc_get_thread_handle_attributes(uint32_t *attributes, Handle handle)
{
    (void)handle;
    *attributes = 0;
    return 0;
}

Result svc_get_process_handle_reference(uint32_t *reference, Handle handle)
{
    (void)handle;
    *reference = 0;
    return 0;
}

Result svc_get_thread_handle_reference(uint32_t *reference, Handle handle)
{
    (void)handle;
    *reference = 0;
    return 0;
}

Result svc_get_process_handle_security(uint32_t *security, Handle handle)
{
    (void)handle;
    *security = 0;
    return 0;
}

Result svc_get_thread_handle_security(uint32_t *security, Handle handle)
{
    (void)handle;
    *security = 0;
    return 0;
}

Result svc_get_process_handle_capability(uint32_t *capability, Handle handle)
{
    (void)handle;
    *capability = 0;
    return 0;
}

Result svc_get_thread_handle_capability(uint32_t *capability, Handle handle)
{
    (void)handle;
    *capability = 0;
    return 0;
}

Result svc_get_process_handle_protection(uint32_t *protection, Handle handle)
{
    (void)handle;
    *protection = 0;
    return 0;
}

Result svc_get_thread_handle_protection(uint32_t *protection, Handle handle)
{
    (void)handle;
    *protection = 0;
    return 0;
}

Result svc_get_process_handle_access(uint32_t *access, Handle handle)
{
    (void)handle;
    *access = 0;
    return 0;
}

Result svc_get_thread_handle_access(uint32_t *access, Handle handle)
{
    (void)handle;
    *access = 0;
    return 0;
}

Result svc_get_process_handle_rights(uint32_t *rights, Handle handle)
{
    (void)handle;
    *rights = 0;
    return 0;
}

Result svc_get_thread_handle_rights(uint32_t *rights, Handle handle)
{
    (void)handle;
    *rights = 0;
    return 0;
}

Result svc_get_process_handle_granted(uint32_t *granted, Handle handle)
{
    (void)handle;
    *granted = 0;
    return 0;
}

Result svc_get_thread_handle_granted(uint32_t *granted, Handle handle)
{
    (void)handle;
    *granted = 0;
    return 0;
}

Result svc_get_process_handle_inherited(uint32_t *inherited, Handle handle)
{
    (void)handle;
    *inherited = 0;
    return 0;
}

Result svc_get_thread_handle_inherited(uint32_t *inherited, Handle handle)
{
    (void)handle;
    *inherited = 0;
    return 0;
}

Result svc_get_process_handle_duplicate(Handle *duplicate, Handle handle)
{
    (void)handle;
    *duplicate = 0;
    return 0;
}

Result svc_get_thread_handle_duplicate(Handle *duplicate, Handle handle)
{
    (void)handle;
    *duplicate = 0;
    return 0;
}

Result svc_get_process_handle_open(Handle *open, Handle handle)
{
    (void)handle;
    *open = 0;
    return 0;
}

Result svc_get_thread_handle_open(Handle *open, Handle handle)
{
    (void)handle;
    *open = 0;
    return 0;
}

Result svc_get_process_handle_close(Handle *close, Handle handle)
{
    (void)handle;
    *close = 0;
    return 0;
}

Result svc_get_thread_handle_close(Handle *close, Handle handle)
{
    (void)handle;
    *close = 0;
    return 0;
}

Result svc_get_process_handle_copy(Handle *copy, Handle handle)
{
    (void)handle;
    *copy = 0;
    return 0;
}

Result svc_get_thread_handle_copy(Handle *copy, Handle handle)
{
    (void)handle;
    *copy = 0;
    return 0;
}

Result svc_get_process_handle_move(Handle *move, Handle handle)
{
    (void)handle;
    *move = 0;
    return 0;
}

Result svc_get_thread_handle_move(Handle *move, Handle handle)
{
    (void)handle;
    *move = 0;
    return 0;
}

uint32_t coproc_movefrom_user_r_thread_and_process_id(void)
{
    return 0;
}

void *rt_memset(void *dest, uint32_t size, uint8_t value)
{
    uint8_t *cursor = (uint8_t *)dest;
    uint8_t *end = cursor + size;
    while (cursor != end) {
        *cursor = value;
        cursor = cursor + 1;
    }
    return cursor;
}

void get_system_tick(uint64_t *tick)
{
    (void)svc_get_system_tick(tick);
}

void recursive_mutex_lock(uint32_t *lock)
{
    uint32_t self = (uint32_t)(uintptr_t)pthread_self();
    if (self != lock[1]) {
        while (__sync_lock_test_and_set(&lock[0], 1u) != 0u) {
            sched_yield();
        }
        lock[1] = self;
    }
    lock[2] = lock[2] + 1;
}

void recursive_mutex_unlock(uint32_t *lock)
{
    lock[2] = lock[2] - 1;
    if (lock[2] != 0) {
        return;
    }
    lock[1] = 0;
    __sync_lock_release(&lock[0]);
}

void initialize_linked_list(uint32_t *list)
{
    *(uint8_t *)list = 0;
    list[2] = 0;
    list[3] = 0;
    list[1] = 0;
    *(uint8_t *)((uint8_t *)list + 0x10) = 0;
}

void push_list_front(uint32_t *list, uint32_t **head, uint32_t *node)
{
    uint32_t *old_head = *head;
    node[1] = (uint32_t)(uintptr_t)head;
    node[0] = (uint32_t)(uintptr_t)old_head;
    if (old_head != (uint32_t *)0) {
        old_head[1] = (uint32_t)(uintptr_t)node;
    }
    *head = node;
    list[3] = list[3] + 1;
}

void pop_list_front(uint32_t *list)
{
    uint32_t *node;
    if (list[3] != 0) {
        node = (uint32_t *)(uintptr_t)list[1];
        *(uint32_t *)(uintptr_t)(node[0] + 4) = node[1];
        *(uint32_t *)(uintptr_t)node[1] = node[0];
        node[0] = 0;
        node[1] = 0;
        list[3] = list[3] - 1;
    }
}

void pop_list_back(uint32_t *list)
{
    uint32_t *node;
    if (list[3] != 0) {
        node = (uint32_t *)(uintptr_t)list[2];
        *(uint32_t *)(uintptr_t)(node[0] + 4) = node[1];
        *(uint32_t *)(uintptr_t)node[1] = node[0];
        node[0] = 0;
        node[1] = 0;
        list[3] = list[3] - 1;
    }
}

uint32_t get_block_size(uint32_t *block)
{
    uint32_t header = ((uint32_t *)(uintptr_t)block)[-1];
    if ((header & 1) == 0) {
        block = (uint32_t *)((uint8_t *)block - 0x10);
    } else {
        block = (uint32_t *)(uintptr_t)(header - 1);
    }
    return block[3];
}

int check_object_ready(const uint8_t *object)
{
    int8_t flag = (int8_t)object[0x60];
    int ready = (flag == 0xb);
    if (flag < 0xc) {
        ready = (flag == (int8_t)object[0x5f]);
    }
    return ready;
}

void reset_object_fields(uint32_t *object)
{
    *(uint8_t *)(object + 0x11) = 0;
    object[0x13] = 0;
    object[0x14] = 0;
    object[0x12] = 0;
    *(uint8_t *)(object + 0x15) = 0;
}

uint32_t map_event_type(uint32_t type)
{
    switch (type) {
    case 2: return 0;
    case 3: return 1;
    case 4: return 3;
    case 5: return 5;
    case 6: return 2;
    case 7: return 4;
    case 8: return 6;
    case 9: return 7;
    case 10: return 8;
    case 11: return 9;
    case 12: return 10;
    case 13: return 11;
    case 14: return 12;
    case 15: return 13;
    case 16: return 14;
    case 17: return 15;
    case 18: return 16;
    case 19: return 17;
    default: return 19;
    }
}

int32_t clamp_with_deadzone(int32_t value, int32_t origin, int32_t deadzone, int32_t gain)
{
    int32_t delta = value - origin;
    if (delta < -deadzone) {
        return (int16_t)((int16_t)origin + (int16_t)((delta + deadzone) * gain >> 7));
    }
    if (deadzone < delta) {
        return (int16_t)((int16_t)origin + (int16_t)((delta - deadzone) * gain >> 7));
    }
    return origin;
}

void set_field_value(uint32_t *field, uint32_t value)
{
    *field = value;
}

uint32_t get_constant_value(void)
{
    return 0;
}

uint32_t wide_string_length(const uint16_t *string)
{
    uint32_t length = 0;
    while (string[length] != 0) {
        length = length + 1;
    }
    return length;
}

void copy_short_struct(uint32_t *dest, const uint32_t *src)
{
    dest[0] = src[0];
    *(uint16_t *)(dest + 1) = *(const uint16_t *)(src + 1);
}

int is_field_zero(const uint32_t *object)
{
    return object[7] == 0;
}

void invalidate_field(uint32_t *object)
{
    object[7] = 0xffffffff;
}

void invalidate_handle_field(uint32_t *object)
{
    object[7] = 0xffffffff;
}

void unlink_handle_reference(uint32_t *slot)
{
    uint32_t target = slot[0];
    if (target != 0) {
        if (*(uint32_t *)(uintptr_t)(target + 8) == (uint32_t)(uintptr_t)slot) {
            *(uint32_t *)(uintptr_t)(target + 8) = 0;
        }
        if (*(uint32_t *)(uintptr_t)(target + 0xc) == (uint32_t)(uintptr_t)slot) {
            *(uint32_t *)(uintptr_t)(target + 0xc) = 0;
        }
        slot[0] = 0;
    }
}

void unlink_object_reference(uint32_t *object)
{
    uint32_t *slot = (uint32_t *)(uintptr_t)object[3];
    uint32_t target = slot[0];
    if (target != 0) {
        if (*(uint32_t *)(uintptr_t)(target + 8) == (uint32_t)(uintptr_t)slot) {
            *(uint32_t *)(uintptr_t)(target + 8) = 0;
        }
        if (*(uint32_t *)(uintptr_t)(target + 0xc) == (uint32_t)(uintptr_t)slot) {
            *(uint32_t *)(uintptr_t)(target + 0xc) = 0;
        }
        slot[0] = 0;
    }
}

void clear_short_struct(uint32_t *dest)
{
    dest[0] = 0;
    *(uint16_t *)(dest + 1) = 0;
}

int is_alternate_mode(uint32_t mode)
{
    if ((mode == 0x2600) || (mode != 0x2601)) {
        return 0;
    }
    return 1;
}

void set_byte_pair_high(uint32_t *object, uint8_t first, uint8_t second)
{
    *(uint8_t *)((uint8_t *)object + 8) = first;
    *(uint8_t *)((uint8_t *)object + 9) = second;
}

void set_byte_pair_low(uint32_t *object, uint8_t first, uint8_t second)
{
    *(uint8_t *)((uint8_t *)object + 6) = first;
    *(uint8_t *)((uint8_t *)object + 7) = second;
}

void set_conditional_field(uint32_t *object, uint32_t mode, uint32_t value)
{
    if ((mode != 3 && mode != 0) &&
        ((mode == 1 || mode == 2 || (mode == 4 || mode == 5)))) {
        object[1] = value;
        return;
    }
    object[1] = 0;
}

uint32_t get_slot_index(uint32_t *table_base, uint32_t handle)
{
    if (table_base[0xf0 / 4] != handle) {
        if (table_base[0xf4 / 4] == handle) {
            return 1;
        }
        if (table_base[0xf8 / 4] == handle) {
            return 2;
        }
        if (table_base[0xfc / 4] == handle) {
            return 3;
        }
        if (table_base[0x100 / 4] == handle) {
            return 4;
        }
        if (table_base[0x104 / 4] == handle) {
            return 5;
        }
    }
    return 0;
}

void initialize_flag_block(uint32_t *object)
{
    *(uint8_t *)((uint8_t *)object + 0x16c) = 1;
    *(uint8_t *)((uint8_t *)object + 0x172) = 0;
    set_byte_pair_low((uint32_t *)((uint8_t *)object + 0x168), 6, 1);
    *(uint8_t *)((uint8_t *)object + 0x173) = 0;
    *(uint8_t *)((uint8_t *)object + 0x170) = 6;
    *(uint8_t *)((uint8_t *)object + 0x171) = 1;
}

uint32_t get_indexed_field(const uint32_t *object, uint32_t index)
{
    return object[index + 0x80c / 4];
}

void accumulate_global(uint32_t *total, uint32_t value)
{
    *total = *total + value;
}

void set_global_halfword(uint16_t *target, uint16_t value)
{
    target[1] = value;
}

uint8_t get_indexed_byte(const uint32_t *pair, uint32_t index)
{
    const uint8_t *bytes = (const uint8_t *)pair;
    return bytes[index];
}

void *rt_memzero(void *dest, uint32_t size)
{
    uint8_t *cursor = (uint8_t *)dest;
    uint8_t *end = cursor + size;
    while (cursor != end) {
        *cursor = 0;
        cursor = cursor + 1;
    }
    return cursor;
}

char *copy_string_padded(char *dest, const char *src, uint32_t size)
{
    uint32_t i = 0;
    while (i < size) {
        char c = src[i];
        dest[i] = c;
        i = i + 1;
        if (c == '\0') {
            break;
        }
    }
    if (i < size) {
        rt_memzero(dest + i, size - i);
    }
    return dest;
}

void *rt_memcpy(void *dest, const void *src, uint32_t size)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    uint32_t i = 0;
    while (i < size) {
        d[i] = s[i];
        i = i + 1;
    }
    return dest;
}

int32_t semaphore_post(uint32_t *semaphore, int32_t count)
{
    int32_t previous;
    int32_t limit;
    int32_t next;
    do {
        previous = (int32_t)semaphore[0];
        limit = (int32_t)(int16_t)((uint8_t *)semaphore)[6];
        next = limit - count;
        if (previous <= next) {
            next = previous + count;
        }
    } while (__sync_val_compare_and_swap(&semaphore[0], (uint32_t)previous, (uint32_t)next)
             != (uint32_t)previous);
    return previous;
}

int queue_pop(uint32_t *queue, uint32_t *out_value)
{
    uint32_t *lock = queue + 5;
    recursive_mutex_lock(lock);
    if (0 < (int32_t)queue[10]) {
        uint32_t *buffer = (uint32_t *)(uintptr_t)queue[0];
        *out_value = buffer[queue[9]];
        uint32_t capacity = queue[8];
        queue[9] = capacity != 0 ? (queue[9] + 1) % capacity : queue[9] + 1;
        queue[10] = queue[10] - 1;
        if (0 < (int32_t)queue[0xc]) {
            semaphore_post(queue + 3, 1);
        }
        recursive_mutex_unlock(lock);
        return 1;
    }
    recursive_mutex_unlock(lock);
    return 0;
}

void write_command_record(uint32_t *ring, uint32_t command, const void *payload)
{
    uint32_t *cursor = *(uint32_t **)(uintptr_t)(ring[0] + 8);
    cursor[0] = command << 8;
    cursor[1] = 0x000f01c5;
    rt_memcpy(cursor + 2, payload, 0x408);
    *(uint32_t *)(uintptr_t)(ring[0] + 8) = (uint32_t)(uintptr_t)(cursor + 0x104);
}

void write_command_record_indexed(uint32_t *ring, const uint32_t *table,
                                  const void *payload)
{
    uint32_t command = get_indexed_byte(table, 0);
    uint32_t *cursor = *(uint32_t **)(uintptr_t)(ring[0] + 8);
    cursor[0] = command << 8;
    cursor[1] = 0x000f01c5;
    rt_memcpy(cursor + 2, payload, 0x408);
    *(uint32_t *)(uintptr_t)(ring[0] + 8) = (uint32_t)(uintptr_t)(cursor + 0x104);
}

void remove_list_node(uint32_t *list, uint32_t *node)
{
    uint32_t prev = node[1];
    uint32_t next = node[2];
    *(uint32_t *)(uintptr_t)(prev + 4) = next;
    *(uint32_t *)(uintptr_t)next = prev;
    list[0x1dc / 4] = list[0x1dc / 4] - 1;
    node[1] = 0;
    node[2] = 0;
}

void set_global_byte(uint8_t *target, uint8_t value)
{
    target[0xd] = value;
}

void remove_list_entry(uint32_t *count, uint32_t *node)
{
    uint32_t prev = node[0];
    uint32_t next = node[1];
    *(uint32_t *)(uintptr_t)(prev + 4) = next;
    *(uint32_t *)(uintptr_t)next = prev;
    count[0] = count[0] - 1;
    node[0] = 0;
    node[1] = 0;
}

void transform_point_affine(float *out, const float *matrix, const float *point)
{
    float x = point[0];
    float y = point[1];
    float z = point[2];
    out[0] = matrix[3] + matrix[0] * x + matrix[1] * y + matrix[2] * z;
    out[1] = matrix[7] + matrix[4] * x + matrix[5] * y + matrix[6] * z;
    out[2] = matrix[11] + matrix[8] * x + matrix[9] * y + matrix[10] * z;
}

void fill_word_range(uint32_t *start, uint32_t *end, uint32_t value)
{
    while (start != end) {
        *start = value;
        start = start + 1;
    }
}

void initialize_render_descriptor(uint16_t *descriptor)
{
    descriptor[0] = 0x28;
    descriptor[1] = 0x24;
    descriptor[2] = 0x28;
    descriptor[3] = 0x91;
    descriptor[4] = 0x91;
    descriptor[5] = 0x91;
    *(uint8_t *)(descriptor + 6) = 0;
    descriptor[7] = 0x8d;
    *(float *)(descriptor + 0xc) = 0.0f;
    *(float *)(descriptor + 0xe) = 0.0f;
    *(float *)(descriptor + 0x10) = 0.0f;
    *(float *)(descriptor + 8) = 1.5f;
    *(float *)(descriptor + 10) = 141.0f;
}

void saturating_add_indexed(uint32_t *object, const uint32_t *amount, uint32_t index)
{
    uint32_t *field = (uint32_t *)((uint8_t *)object + index * 4 + 0x1b4);
    uint32_t current = *field;
    uint64_t sum = (uint64_t)current + amount[0] + ((uint64_t)(int32_t)current >> 63) + amount[1];
    if (sum >= 0x7fffffff) {
        *field = 0x7fffffff;
    } else {
        *field = current + amount[0];
    }
}

void clear_global_block(uint32_t *block)
{
    block[2] = 0;
    block[0] = 0;
    block[4] = 0;
    block[5] = 0;
    block[6] = 0;
    block[7] = 0;
    *(uint8_t *)(block + 0x14 / 4) = 0;
}

void saturating_add_total(uint32_t *object, const uint32_t *amount)
{
    uint32_t *field = (uint32_t *)((uint8_t *)object + 0x220);
    uint32_t current = *field;
    uint64_t sum = (uint64_t)current + amount[0] + ((uint64_t)(int32_t)current >> 63) + amount[1];
    if (sum >= 0x7fffffff) {
        *field = 0x7fffffff;
    } else {
        *field = current + amount[0];
    }
}

int test_flag_bit(const uint32_t *object, uint32_t bit)
{
    return ((uint32_t) * (const uint16_t *)(object + 1) & (1u << (bit & 0xff))) != 0;
}

uint32_t *get_indexed_slot(uint32_t *object, uint32_t index)
{
    return (uint32_t *)((uint8_t *)object + index * 0x2c + 0x120);
}

int has_attached_pointer(const uint32_t *object)
{
    return object[1] != 0;
}

uint16_t *append_wide_string_bounded(uint16_t *dest, const uint16_t *src, uint32_t limit)
{
    uint16_t *tail = dest;
    while (*tail != 0) {
        tail = tail + 1;
    }
    while (limit != 0 && *src != 0) {
        *tail = *src;
        tail = tail + 1;
        src = src + 1;
        limit = limit - 1;
    }
    *tail = 0;
    return dest;
}

void store_vector4(uint32_t *dest, const uint32_t *src)
{
    dest[0xf4 / 4] = src[0];
    dest[0xf8 / 4] = src[1];
    dest[0xfc / 4] = src[2];
    dest[0x100 / 4] = src[3];
}

uint32_t *build_wide_string_descriptor(uint32_t *descriptor, uint32_t tag, const uint16_t *string)
{
    descriptor[0] = tag;
    descriptor[1] = (uint32_t)(uintptr_t)string;
    descriptor[2] = wide_string_length(string) << 1;
    return descriptor;
}

int has_backing_store(const uint32_t *object)
{
    return object[0x1a4 / 4] != 0;
}

int has_active_subobject(const uint32_t *object)
{
    uint32_t index = object[0x274 / 4];
    return object[index * (0xd0 / 4) + 1] != 0;
}

void transpose_matrix_rows(uint32_t *dest, const uint32_t *src)
{
    dest[0] = src[0];
    dest[1] = src[4];
    dest[2] = src[8];
    dest[3] = 0;
    dest[4] = src[1];
    dest[5] = src[5];
    dest[6] = src[9];
    dest[7] = 0;
    dest[8] = src[2];
    dest[9] = src[6];
    dest[10] = src[10];
    dest[11] = 0;
}

void set_object_handle_field(uint32_t *object, uint32_t handle, uint32_t value)
{
    object[1] = value;
    object[0x38 / 4] = handle;
}

uint32_t take_and_clear_global(uint32_t *slot)
{
    uint32_t value = slot[0];
    slot[0] = 0;
    return value;
}

uint32_t *insert_list_back(uint32_t *list, uint32_t *node)
{
    uint32_t *link = node + 1;
    uint32_t *old_tail = *(uint32_t **)(uintptr_t)(list[0x1e4 / 4]);
    link[0] = (uint32_t)(uintptr_t)(list + 0x1e0 / 4);
    node[2] = (uint32_t)(uintptr_t)old_tail;
    *(uint32_t *)(uintptr_t)(list[0x1e4 / 4]) = (uint32_t)(uintptr_t)link;
    old_tail[0] = (uint32_t)(uintptr_t)link;
    list[0x1dc / 4] = list[0x1dc / 4] + 1;
    return link;
}

uint32_t *insert_list_after(uint32_t *count, uint32_t *at, uint32_t *node)
{
    uint32_t *next = (uint32_t *)(uintptr_t)(at[1]);
    node[0] = (uint32_t)(uintptr_t)at;
    node[1] = (uint32_t)(uintptr_t)next;
    at[1] = (uint32_t)(uintptr_t)node;
    next[0] = (uint32_t)(uintptr_t)node;
    count[0] = count[0] + 1;
    return node;
}

void copy_pair(uint32_t *dest, const uint32_t *src)
{
    dest[0] = src[0];
    dest[1] = src[1];
}

void clear_list(uint32_t *count, uint32_t *head)
{
    uint32_t *next = (uint32_t *)(uintptr_t)head[0];
    while (head != next) {
        uint32_t *cur = next;
        uint32_t *following = (uint32_t *)(uintptr_t)cur[0];
        uint32_t *prev = (uint32_t *)(uintptr_t)cur[1];
        following[1] = (uint32_t)(uintptr_t)prev;
        prev[0] = (uint32_t)(uintptr_t)following;
        count[0] = count[0] - 1;
        cur[0] = 0;
        cur[1] = 0;
        next = following;
    }
}

void set_byte_at_offset(uint8_t *base, uint8_t value)
{
    base[10] = value;
}

uint32_t get_table_entry(const uint32_t *table, uint32_t index)
{
    if (index == 0) {
        return table[0];
    }
    return *(const uint32_t *)(uintptr_t)((uint32_t) * (const uint16_t *)((const uint8_t *)table + 10) + index + 4);
}

uint32_t resolve_range_entry(uint32_t table, uint32_t key)
{
    uint32_t index = 0;
    uint32_t entry;
    for (;;) {
        entry = get_table_entry((const uint32_t *)(uintptr_t)table, index);
        if (entry == 0) {
            return 0;
        }
        uint32_t low = *(const uint32_t *)(uintptr_t)(entry + 0x18);
        uint32_t high = *(const uint32_t *)(uintptr_t)(entry + 0x1c);
        if (low <= key && key < high) {
            break;
        }
        index = entry;
    }
    uint32_t child = resolve_range_entry(entry + 0xc, key);
    if (child == 0) {
        child = entry;
    }
    return child;
}

void clamp_render_descriptor(int16_t *descriptor)
{
    if (descriptor[0] < 0x28) {
        descriptor[0] = 0x28;
    }
    if (descriptor[1] < 0x24) {
        descriptor[1] = 0x24;
    }
    if (0x91 < descriptor[3]) {
        descriptor[3] = 0x91;
    }
    if (0x91 < descriptor[4]) {
        descriptor[4] = 0x91;
    }
    if (0x91 < descriptor[5]) {
        descriptor[5] = 0x91;
    }
}

void build_range_descriptor(uint32_t *descriptor, uint32_t tag, uint32_t base, uint32_t size)
{
    descriptor[1] = 0;
    descriptor[0] = tag;
    descriptor[5] = size;
    descriptor[6] = 0;
    descriptor[2] = base;
    descriptor[7] = 0;
    descriptor[3] = base;
    descriptor[4] = base;
}

uint32_t get_region_tag(void)
{
    return 0;
}

int get_service_state_byte(void)
{
    return 0;
}

void set_bitset_bit(uint32_t *bitset, uint32_t bit)
{
    uint32_t *word = (uint32_t *)((uint8_t *)bitset + (bit >> 5) * 4);
    *word = *word | (1u << (bit & 0x1f));
}

void clear_byte_flag(uint8_t *object)
{
    object[0x1b] = 0;
}

void initialize_command_descriptor(uint8_t *descriptor)
{
    descriptor[0] = 4;
    descriptor[1] = 2;
    descriptor[2] = 0;
    descriptor[3] = 0;
    *(uint32_t *)(descriptor + 4) = 0;
    *(uint32_t *)(descriptor + 8) = 0;
}

uint32_t *copy_quad_pair(uint32_t *dest, const uint32_t *src)
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    dest[3] = src[3];
    dest[4] = src[4];
    dest[5] = src[5];
    dest[6] = src[6];
    dest[7] = src[7];
    return dest;
}

void clear_pair(uint32_t *dest)
{
    dest[0] = 0;
    dest[1] = 0;
}

void noop_operation(void)
{
}

void build_region_record(uint8_t *record, int32_t x, int32_t y, int32_t x2, int32_t y2,
                         uint32_t extra_a, uint32_t extra_b)
{
    record[0] = 1;
    *(int32_t *)(record + 4) = x;
    *(int32_t *)(record + 8) = y;
    *(int32_t *)(record + 0xc) = x2 - x;
    *(int32_t *)(record + 0x10) = y2 - y;
    *(uint32_t *)(record + 0x14) = extra_a;
    *(uint32_t *)(record + 0x18) = extra_b;
}

void reset_write_buffer(uint32_t *buffer)
{
    uint8_t *cursor;
    buffer[0xdc / 4] = 0;
    buffer[0xe0 / 4] = 0;
    cursor = (uint8_t *)(uintptr_t)buffer[0xe4 / 4];
    buffer[0xe8 / 4] = (uint32_t)(uintptr_t)cursor;
    buffer[0xe8 / 4] = (uint32_t)(uintptr_t)(cursor + 1);
    if (cursor != (uint8_t *)0) {
        cursor[0] = 0x1c;
    }
    buffer[0xe0 / 4] = buffer[0xe0 / 4] + 1;
    buffer[0xdc / 4] = buffer[0xdc / 4] | 0x10000000;
}

void lookup_command_value(int16_t *out_tag, int16_t *out_value, uint32_t command)
{
    if (command == 0x8058) {
        *out_tag = (int16_t)0x6752;
        *out_value = (int16_t)0x1401;
        return;
    }
    if (command != 0x8057) {
        if (command != 0x8d62) {
            if (command == 0x8056) {
                *out_tag = (int16_t)0x6752;
                *out_value = (int16_t)0x8033;
            }
            return;
        }
        *out_tag = (int16_t)0x6754;
        *out_value = (int16_t)0x8363;
        return;
    }
    *out_tag = (int16_t)0x6752;
    *out_value = (int16_t)0x8034;
}

void initialize_region_block(uint8_t *block)
{
    block[0] = 1;
    *(uint32_t *)(block + 4) = 0;
    *(uint32_t *)(block + 0x10) = 0x140;
    *(uint32_t *)(block + 0x14) = 0x100;
    *(uint32_t *)(block + 0x18) = 0x140;
    *(uint32_t *)(block + 8) = 0;
    *(uint32_t *)(block + 0xc) = 0xf0;
}

void initialize_list_head_pair(uint32_t *list)
{
    list[0] = 0;
    list[2] = (uint32_t)(uintptr_t)(list + 4);
    list[1] = 0;
    list[3] = (uint32_t)(uintptr_t)(list + 4);
}

void initialize_record(uint32_t *record, uint32_t tag)
{
    record[0] = 0;
    record[3] = 0;
    record[5] = 0;
    *(uint8_t *)(record + 6) = 1;
    record[7] = tag;
    record[2] = 0;
    record[1] = 0;
}

void clear_quad(uint32_t *dest)
{
    dest[0] = 0;
    dest[1] = 0;
    dest[2] = 0;
    dest[3] = 0;
}

void clear_state_fields(uint8_t *object)
{
    object[0] = 0;
    object[1] = 0;
    *(uint32_t *)(object + 0x24) = 0;
    *(uint32_t *)(object + 8) = 0;
    *(uint32_t *)(object + 4) = 0;
    *(uint32_t *)(object + 0xc) = 0;
}

void set_status_byte_b(uint8_t *block, uint8_t value)
{
    block[0xb] = value;
}

int get_status_byte_9(const uint8_t *block)
{
    return (int)(int8_t)block[9];
}

void set_status_byte_c(uint8_t *block, uint8_t value)
{
    block[0xc] = value;
}

uint8_t get_status_byte_c(const uint8_t *block)
{
    return block[0xc];
}

int get_status_byte_1(const uint8_t *block)
{
    return (int)(int8_t)block[1];
}

uint8_t get_status_byte_6(const uint8_t *block)
{
    return block[6];
}

uint8_t get_status_byte_2(const uint8_t *block)
{
    return block[2];
}

int get_object_field_120(const uint8_t *object)
{
    return (int)(int8_t)object[0x120];
}

uint32_t map_service_mode(uint32_t mode)
{
    switch (mode) {
    case 3:
    case 4:
        return 1;
    case 5:
        return 2;
    default:
        return 0;
    }
}

uint8_t get_indexed_status_byte(const uint8_t *block, uint32_t offset)
{
    return block[offset + 0xd];
}

void svc_store_word(uint32_t *target, uint32_t value)
{
    *target = value;
}

void add_map_entry(uint32_t *map, uint32_t key, uint32_t value)
{
    uint32_t count = map[0];
    map[count * 2 + 1] = key;
    map[count * 2 + 2] = value;
    map[0] = count + 1;
}

uint32_t get_word_field_1c(const uint32_t *object)
{
    return object[0x1c / 4];
}

uint32_t get_word_field_18(const uint32_t *object)
{
    return object[0x18 / 4];
}

uint32_t compare_wide_strings(const uint16_t *a, const uint16_t *b)
{
    uint32_t ca;
    for (;;) {
        ca = *a;
        if (ca == 0 || ca != *b) {
            break;
        }
        a = a + 1;
        b = b + 1;
    }
    return ca - *b;
}

uint32_t test_flag_80(const uint32_t *object)
{
    return object[3] & 0x80;
}

void increment_reference_count(uint32_t *slot, uint32_t *target)
{
    uint32_t value = *target;
    *slot = value;
    *(uint32_t *)(uintptr_t)(value + 0x1c) = *(uint32_t *)(uintptr_t)(value + 0x1c) + 1;
}

uint32_t *get_indexed_pointer(uint32_t *base, uint32_t index)
{
    return (uint32_t *)(uintptr_t)(base[0] + index * 4);
}

uint32_t *select_larger(uint32_t *a, uint32_t *b)
{
    if (a[0] < b[0]) {
        a = b;
    }
    return a;
}

void clear_byte_at_202(uint8_t *object)
{
    object[0x202] = 0;
}

void set_quad_fields(uint32_t *object, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    object[0x150 / 4] = a;
    object[0x154 / 4] = b;
    object[0x158 / 4] = c;
    object[0x15c / 4] = d;
}

uint32_t get_region_base(void)
{
    return 0x3000000;
}

void set_flag_854(uint8_t *object)
{
    object[0x854] = 1;
}

void set_flag_855(uint8_t *object)
{
    object[0x855] = 1;
}

uint32_t identity_word(uint32_t value)
{
    return value;
}

void clear_record_fields(uint32_t *record)
{
    record[0] = 0;
    record[2] = 0xffffffff;
    record[1] = 0;
    record[3] = 0;
    record[4] = 0;
    record[5] = 0;
    record[6] = 0;
}

void clear_six_fields(uint32_t *record)
{
    record[0] = 0;
    record[3] = 0;
    record[4] = 0;
    record[5] = 0;
    record[1] = 0;
    record[2] = 0;
}

void set_four_offsets(uint32_t *object, uint32_t value)
{
    object[0x24 / 4] = value;
    object[0x54 / 4] = value;
    object[0x78 / 4] = value;
    object[0x8c / 4] = value;
}

void clear_first_word(uint32_t *object)
{
    object[0] = 0;
}

void clear_byte_84(uint8_t *object)
{
    object[0x84] = 0;
}

void clear_byte_18(uint8_t *object)
{
    object[0x18] = 0;
}

void clear_three_halfwords(uint32_t *object)
{
    object[0] = 0;
    *(uint16_t *)(object + 1) = 0;
    *(uint16_t *)((uint8_t *)object + 6) = 0;
    *(uint16_t *)(object + 2) = 0;
}

void clear_four_words(uint32_t *object)
{
    object[2] = 0;
    object[3] = 0;
    object[4] = 0;
    object[1] = 0;
}

void store_indexed_value(uint32_t *object, uint32_t index, const uint32_t *value)
{
    *(uint32_t *)(uintptr_t)(*(uint32_t *)(uintptr_t)((uint8_t *)object + 0x2fc) + index * 4) = value[0];
}

int has_valid_attachment(uint32_t *object)
{
    uint32_t result = 0;
    if (object[1] != 0 && has_attached_pointer(object) != 0) {
        result = 1;
    }
    return result;
}

uint32_t get_locked_field_5c(uint32_t *object)
{
    recursive_mutex_lock(object + 0x28 / 4);
    uint32_t value = object[0x5c / 4];
    recursive_mutex_unlock(object + 0x28 / 4);
    return value;
}

uint32_t set_field_and_confirm(uint32_t *object, uint32_t value)
{
    object[1] = value;
    return 1;
}

void clear_indexed_slot_138(uint32_t *object, uint32_t index)
{
    object[index + 0x138 / 4] = 0;
}

void copy_field_180_to_184(uint32_t *object)
{
    object[0x184 / 4] = object[0x180 / 4];
}

void clear_indexed_slot_128(uint32_t *object, uint32_t index)
{
    object[index + 0x128 / 4] = 0;
}

void build_state_record(uint32_t *object, uint32_t field_20, uint32_t field_28, const uint32_t *values)
{
    object[0x20 / 4] = field_20;
    object[0x28 / 4] = field_28;
    object[1] = values[0];
    object[2] = values[1];
    object[3] = values[2];
    object[4] = values[3];
    object[5] = values[4];
    object[6] = values[5];
    object[7] = values[6];
}

void clear_byte_49(uint8_t *object)
{
    object[0x49] = 0;
}

void noop_return(void)
{
}

void clear_byte_16c(uint8_t *object)
{
    object[0x16c] = 0;
}

void clear_four_words_and_byte(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = 0;
    object[3] = 0;
    *(uint8_t *)(object + 4) = 0;
}

uint32_t *detach_handle_references(uint32_t *object)
{
    unlink_handle_reference(object + 2);
    unlink_handle_reference(object + 1);
    return object;
}

void set_flag_1fd(uint8_t *object)
{
    if (object[0x1fd] == 0) {
        object[0x1fd] = 1;
    }
}

uint32_t get_indexed_record_address(uint32_t base, uint32_t index)
{
    return base + index * 0x80 + 0xff8;
}

int is_field_20ac_zero(const uint32_t *object)
{
    return object[0x20ac / 4] == 0;
}

void set_first_word_one(uint32_t *object)
{
    object[0] = 1;
}

uint32_t get_thread_field_5c(void)
{
    return 0x5c;
}

uint32_t get_indexed_word_18(const uint32_t *object, uint32_t index)
{
    return object[index + 0x18 / 4];
}

uint32_t compute_record_offset(uint32_t base, uint32_t row, uint32_t column)
{
    return column * row + base * 0xba0 + 0x36c0;
}

void set_bit_in_field(uint8_t *object, uint32_t bit)
{
    if ((int32_t)bit < 0x3c) {
        object = object + ((int32_t)bit >> 3);
        object[0xf] = object[0xf] | (uint8_t)(1 << (bit & 7));
    }
}

void clear_word_28(uint32_t *object)
{
    if (object[0x28 / 4] != 0) {
        object[0x28 / 4] = 0;
    }
}

void clear_pair_38(uint32_t *object)
{
    object[0x38 / 4] = 0;
    object[0x3c / 4] = 0;
}

void initialize_status_record(uint32_t *record)
{
    record[1] = 0;
    ((uint8_t *)record)[0xc] = 0x2f;
    ((uint8_t *)record)[0xd] = 0;
}

void clear_triple_38(uint32_t *object)
{
    object[0x38 / 4] = 0;
    object[0x3c / 4] = 0;
    object[0x40 / 4] = 0;
}

void set_pair_8_5c(uint32_t *object, uint32_t a, uint32_t b)
{
    object[8 / 4] = a;
    object[0x5c / 4] = b;
}

void clear_status_block(uint32_t *block)
{
    block[1] = 0;
    block[0] = 0;
    ((uint8_t *)block)[10] = 0;
    ((uint8_t *)block)[9] = 0;
    ((uint8_t *)block)[8] = 0;
}

uint32_t get_nested_field_18(uint32_t *object)
{
    uint32_t result = 0;
    if (object[0x134 / 4] != 0 && object[0x12c / 4] != 0) {
        result = *(uint32_t *)(uintptr_t)(object[0x12c / 4] + 0x18);
    }
    return result;
}

uint32_t get_field_14_offset_658(const uint32_t *object)
{
    return object[0x14 / 4] + 0x658;
}

void clear_word_20_and_pointed(uint32_t *object)
{
    object[0x20 / 4] = 0;
    *(uint32_t *)(uintptr_t)object[2] = 0;
}

uint32_t get_indexed_pointed_field(uint32_t *object, uint32_t offset)
{
    uint32_t index = object[0x14 / 4];
    uint32_t base = object[index + 1];
    return (uint32_t)(uintptr_t)(base + offset);
}

uint32_t get_pointed_field_48(const uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(object[0x14 / 4] + 0x48);
}

void clear_byte_4c(uint8_t *object)
{
    object[0x4c] = 0;
}

void clear_record_10(uint8_t *object)
{
    object[0x10] = 0;
    *(uint32_t *)(object + 8) = 0;
    *(uint32_t *)(object + 0xc) = 0;
}

void clear_word_14(uint32_t *object)
{
    object[0x14 / 4] = 0;
}

void clear_byte_190(uint8_t *object)
{
    if (object[400] != 0) {
        object[400] = 0;
    }
}

void clear_pointed_word_20(uint32_t *object)
{
    if (object[0] != 0) {
        *(uint32_t *)(uintptr_t)object[0] = 0;
    }
}

void set_byte_98(uint8_t *object)
{
    object[0x98] = 1;
}

void set_byte_and_mark_dirty(uint8_t *object, uint8_t value)
{
    object[0] = value;
    *(uint32_t *)(object + 0x5008) = *(uint32_t *)(object + 0x5008) | 0x21;
}

int is_double_match(const uint32_t *object, uint32_t field_c, uint32_t field_64)
{
    return object[0x64 / 4] == field_64 && object[0xc / 4] == field_c;
}

void invalidate_range_fields(uint32_t *object)
{
    object[0xc / 4] = 0xffffffff;
    object[0x10 / 4] = 0xffffffff;
    object[0x14 / 4] = 0;
    object[0x1c / 4] = 0xffffffff;
    object[0x24 / 4] = 0;
    object[0x20 / 4] = 0xffffffff;
}

void clear_pair_c_8(uint32_t *object)
{
    object[0xc / 4] = 0;
    object[8 / 4] = 0;
}

void clear_record_4c(uint32_t *object)
{
    object[0x4c / 4] = 0;
    ((uint8_t *)object)[0x5c] = 0;
    object[0x40 / 4] = 0;
    object[0x44 / 4] = 0;
}

void clear_sub_record(uint32_t *parent, uint16_t *sub)
{
    sub[2] = 0;
    sub[3] = 0;
    sub[4] = 0;
    sub[5] = 0;
    sub[6] = 0;
    ((uint8_t *)sub)[0xe] = 0;
    *(uint32_t *)(sub + 8) = 0;
    *(uint32_t *)(sub + 10) = 0;
    parent[0] = 0;
}

uint32_t get_conditional_field_21c(const uint32_t *object)
{
    if (((int8_t *)object)[0x9c] == 0) {
        return 0;
    }
    return object[0x21c / 4];
}

int has_pointed_field_44(const uint32_t *object)
{
    return *(const int *)(uintptr_t)(object[1] + 0x44) != 0;
}

uint32_t get_double_pointed_field_8(const uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)object[6] + 8);
}

uint32_t passthrough_word(uint32_t value)
{
    return value;
}

uint32_t mark_if_type_102(uint32_t *object)
{
    if (*(int16_t *)((uint8_t *)object + 0x1c) == 0x102) {
        *(uint16_t *)((uint8_t *)object + 0xc) = 6;
    }
    return 1;
}

void set_bytes_ff(uint8_t *dest)
{
    dest[0] = 0xff;
    dest[1] = 0xff;
    dest[2] = 0xff;
    dest[3] = 0xff;
}

uint32_t clear_word_21c_and_confirm(uint32_t *object)
{
    object[0x21c / 4] = 0;
    return 1;
}

void clear_byte_2c_and_word_20(uint8_t *object)
{
    object[0x2c] = 0;
    *(uint32_t *)(object + 0x20) = 0;
}

void noop_b(void)
{
}

void noop_c(void)
{
}

void noop_d(void)
{
}

uint64_t multiply_accumulate_64(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    uint64_t product = (uint64_t)a * (uint64_t)c;
    uint64_t high = (uint64_t)(uint32_t)(d * a + c * b + (uint32_t)(product >> 0x20));
    return (high << 0x20) | (uint32_t)product;
}

void clear_byte_f7_and_mask(uint32_t *object)
{
    uint32_t *mid = (uint32_t *)(uintptr_t)object[1];
    uint32_t *target = *(uint32_t **)(uintptr_t)((uint8_t *)mid + 0xb08);
    *(uint8_t *)(uintptr_t)((uint8_t *)target + 0xf7) = 0xff;
    target[0x48 / 4] = target[0x48 / 4] & 0xffff3fff;
}

void clear_byte_f7(uint32_t *object)
{
    uint32_t *mid = (uint32_t *)(uintptr_t)object[1];
    uint32_t *target = *(uint32_t **)(uintptr_t)((uint8_t *)mid + 0xb08);
    *(uint8_t *)(uintptr_t)((uint8_t *)target + 0xf7) = 0;
}

uint32_t set_field_if_mask_60000(uint32_t *object)
{
    uint32_t *mid = (uint32_t *)(uintptr_t)object[1];
    uint32_t *target = *(uint32_t **)(uintptr_t)((uint8_t *)mid + 0xb08);
    if ((target[0x48 / 4] & 0x60000) != 0) {
        *(uint16_t *)((uint8_t *)object + 0xc) = 1;
    }
    return 1;
}

uint32_t initialize_channel_record(uint32_t *record, uint32_t handle, uint32_t value, uint32_t extra)
{
    uint32_t result;
    *(uint8_t *)(record + 1) = 0;
    *(uint16_t *)((uint8_t *)record + 0x10) = 0;
    if (handle == 0) {
        result = 0;
    } else {
        if (value != 0) {
            record[2] = value;
            record[3] = extra;
        }
        result = 1;
    }
    return result;
}

void set_field_4(uint32_t *object, uint32_t value)
{
    object[1] = value;
}

void set_halfword_c_100(uint8_t *object)
{
    *(uint16_t *)(object + 0xc) = 0x100;
}

void clear_quad_words(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = 0;
    object[3] = 0;
}

void set_fields_18_14_with_null_flag(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0x18 / 4] = a;
    object[0x14 / 4] = b;
    *(uint8_t *)((uint8_t *)object + 0x121) = (a == 0 || b == 0);
}

void set_field_138_if_nonzero(uint32_t *object, uint32_t value)
{
    if (value != 0) {
        object[0x138 / 4] = value;
    }
}

uint32_t pop_field_244(uint32_t *object, uint32_t *out)
{
    out[0] = object[0x244 / 4];
    object[0x244 / 4] = (uint32_t)(uintptr_t)out;
    object[0x24c / 4] = object[0x24c / 4] - 1;
    return object[0x244 / 4];
}

uint32_t pop_field_278(uint32_t *object, uint32_t *out)
{
    out[0] = object[0x278 / 4];
    object[0x278 / 4] = (uint32_t)(uintptr_t)out;
    object[0x280 / 4] = object[0x280 / 4] - 1;
    return object[0x278 / 4];
}

void set_field_110_and_clear(uint32_t *object, uint32_t value)
{
    object[0x110 / 4] = value;
    ((uint8_t *)object)[0x116] = 0;
}

void store_pointed_100(uint32_t *object, const uint32_t *value)
{
    object[0x100 / 4] = value[0];
}

void store_pointed_104(uint32_t *object, const uint32_t *value)
{
    object[0x104 / 4] = value[0];
}

void noop_e(void)
{
}

void scale_pair_by_field_c(float *object, float *target)
{
    target[0x40 / 4] = target[0x24 / 4] * object[0xc / 4];
    target[0x44 / 4] = target[0x28 / 4] * object[0xc / 4];
}

uint32_t get_field_1c_or_pointed(const uint32_t *object)
{
    uint32_t value = object[0x1c / 4];
    if (value == 0) {
        value = **(uint32_t *const *)(uintptr_t)object[1];
    }
    return value;
}

void initialize_state_block(uint8_t *object)
{
    object[0x14] = 6;
    *(uint32_t *)(object + 0x20) = 0;
    *(uint32_t *)(object + 0x1c) = 0;
    *(uint32_t *)(object + 4) = 0x29;
}

void store_pointed_68_24(uint32_t *object, const uint32_t *value)
{
    *(uint32_t *)(uintptr_t)(object[0x68 / 4] + 0x24) = value[0];
}

uint32_t advance_state_byte_19(uint8_t *object)
{
    int8_t state = (int8_t)object[0x19];
    if (state != 0) {
        if (state == 1 || state == 2) {
            return (uint8_t)state;
        }
    }
    return 1;
}

int8_t advance_state_byte_4d(uint8_t *object)
{
    int8_t state = (int8_t)object[0x4d];
    if (state == 0) {
        state = 2;
    }
    if (state != 2) {
        if (state == 3) {
            state = 4;
        } else {
            state = 0;
        }
    }
    return state;
}

uint16_t swap_halfword_34(uint8_t *object, uint16_t value)
{
    uint16_t old = *(uint16_t *)(object + 0x34);
    *(uint16_t *)(object + 0x34) = value;
    return old;
}

uint16_t swap_halfword_36_bit0(uint8_t *object, uint16_t value)
{
    uint16_t old = *(uint16_t *)(object + 0x36);
    *(uint16_t *)(object + 0x36) = (value & 1) | (old & 0xfffe);
    return old & 1;
}

int32_t swap_byte_38(uint8_t *object, uint8_t value)
{
    int8_t old = (int8_t)object[0x38];
    object[0x38] = value;
    return old;
}

void clear_byte_4(uint8_t *object)
{
    object[4] = 0;
}

void clear_word_0_and_set_c(uint32_t *object, uint16_t *target, uint16_t value)
{
    target[0xc / 2] = value;
    object[0] = 0;
}

void clear_record_with_byte_3(uint32_t *record)
{
    record[0] = 0;
    record[1] = 0;
    record[2] = 0;
    ((uint8_t *)record)[0xc] = 0;
}

void clear_word_field_4(uint32_t *object)
{
    object[1] = 0;
}

void clear_byte_pair_4_5(uint8_t *object)
{
    object[4] = 0;
    object[5] = 0;
}

void set_byte_field_1438(uint8_t *object, uint8_t value)
{
    object[0x1438] = value;
}

void set_word_fields_26c_270(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0x26c / 4] = a;
    object[0x270 / 4] = b;
}

void clear_word_b0(uint32_t *object)
{
    object[0xb0 / 4] = 0;
}

void clear_flag_bits(uint32_t *object, uint32_t bit)
{
    object[0x44 / 4] = object[0x44 / 4] & ~(1u << (bit & 0xff));
}

void clear_fields_40_44(uint32_t *object)
{
    object[0x40 / 4] = 0;
    object[0x44 / 4] = 0;
}

void set_word_and_halfword(uint32_t *object, uint32_t word, uint16_t half)
{
    object[0] = word;
    *(uint16_t *)((uint8_t *)object + 1) = half;
}

void set_halfword_8_and_byte_10(uint8_t *object, uint16_t half)
{
    *(uint16_t *)(object + 8) = half;
    object[10] = 1;
}

void clear_word_60_64(uint32_t *object)
{
    object[0x60 / 4] = 0;
    object[0x64 / 4] = 0;
}

void clear_fields_6c_70(uint32_t *object)
{
    object[0x6c / 4] = 0;
    object[0x70 / 4] = 0;
}

void clear_word_a8(uint32_t *object)
{
    object[0xa8 / 4] = 0;
}

void clear_word_3c(uint32_t *object)
{
    object[0x3c / 4] = 0;
}

void clear_word_40(uint32_t *object)
{
    object[0x40 / 4] = 0;
}

void set_indexed_byte_d4(uint8_t *object, uint8_t value)
{
    object[(uint32_t)object[0xb8] + 0xd4] = value;
}

void copy_fields_8_c(uint32_t *object)
{
    object[1] = object[2];
    object[2] = object[3];
}

void set_word_1000_and_byte_1(uint32_t *object)
{
    object[0] = 1000;
    ((uint8_t *)object)[1] = 1;
}

void set_first_word_1(uint32_t *object)
{
    object[0] = 1;
}

void store_bytes_split(uint8_t *dest, uint32_t value)
{
    dest[0] = (uint8_t)(value >> 8);
    dest[1] = (uint8_t)value;
}

void store_indexed_184(uint32_t *object, uint32_t index, uint32_t value)
{
    object[index + 0x184 / 4] = value;
}

void clear_word_field_4_b(uint32_t *object)
{
    object[1] = 0;
}

void clear_pair_words(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
}

void set_first_word_1_b(uint32_t *object)
{
    object[0] = 1;
}

uint32_t test_bit_2(const uint8_t *object)
{
    uint8_t bit = object[0] & 2;
    if ((object[0] & 2) != 0) {
        bit = 1;
    }
    return bit;
}

void clear_byte_179(uint8_t *object)
{
    object[0x179] = 0;
}

void toggle_byte_1(uint8_t *object)
{
    object[1] = (uint8_t)(1 - object[1]);
}

void clear_bytes_78_80(uint8_t *object)
{
    object[0x80] = 0;
    object[0x78] = 0;
}

void set_pair_1c_20(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0x1c / 4] = a;
    object[0x20 / 4] = b;
}

void advance_list_node(uint32_t *node)
{
    if (node[0] != 0) {
        node[0] = *(uint32_t *)(uintptr_t)node[0];
    }
}

void swap_head_pointer(uint32_t *object, uint32_t *node)
{
    node[0] = object[0];
    object[0] = (uint32_t)(uintptr_t)node;
}

void set_byte_17_if_different(uint8_t *object, uint8_t value)
{
    if (object[0x17] != value) {
        object[0x17] = value;
    }
}

void clear_fields_1a0(uint32_t *object)
{
    if (object != (uint32_t *)0) {
        object[0x1a0 / 4] = 0;
        object[0x1a4 / 4] = 0;
    }
}

void clear_six_words_and_byte(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = 0;
    object[3] = 0;
    object[4] = 0;
    object[5] = 0;
    ((uint8_t *)object)[0x11] = 0;
}

uint32_t compute_stride_1b8(uint32_t index)
{
    return (index + 1) * 0x1b8;
}

uint32_t compute_stride_60(uint32_t index)
{
    return index * 0x60;
}

uint8_t get_pointed_byte_14(const uint32_t *object, uint32_t offset)
{
    return *(const uint8_t *)(uintptr_t)(object[1] + offset + 0x14);
}

uint32_t get_constant_23(void)
{
    return 0x23;
}

uint32_t get_halfword_38_masked(const uint32_t *object)
{
    return object[0x38 / 4] & 0xffff;
}

uint16_t byte_swap_halfword(uint16_t value)
{
    return (uint16_t)(value << 8 | value >> 8);
}

void copy_field_8_to_4(uint32_t *object)
{
    object[1] = object[2];
    object[3] = 0;
}

void store_pair_10_14(uint32_t *object, const uint32_t *value)
{
    object[0x10 / 4] = value[0];
    object[0x14 / 4] = value[1];
}

uint32_t get_indexed_halfword_address(uint32_t object, uint32_t index)
{
    if (index < 0x10) {
        return object + index * 2 + 0x10c;
    }
    return 0;
}

int has_flag_and_subobject(const uint32_t *object)
{
    int has_flag = ((const int8_t *)object)[0x316] != 0;
    if (has_flag) {
        object = (const uint32_t *)(uintptr_t)object[0x310 / 4];
    }
    return has_flag && object != (const uint32_t *)0;
}

void noop_l(void)
{
}

void noop_m(void)
{
}

void clear_byte_358(uint8_t *object)
{
    if (object[0x358] != 0) {
        object[0x358] = 0;
    }
}

void clear_record_4_8(uint8_t *object)
{
    *(uint16_t *)(object + 4) = 0;
    *(uint32_t *)(object + 8) = 0;
}

void clear_word_18(uint32_t *object)
{
    object[0x18 / 4] = 0;
}

void clear_word_8(uint32_t *object)
{
    object[8 / 4] = 0;
}

void clear_word_4(uint32_t *object)
{
    object[4 / 4] = 0;
}

void clear_word_250(uint32_t *object)
{
    object[0x250 / 4] = 0;
}

uint32_t set_byte_14_if_nonzero(uint32_t *record, uint32_t *sub)
{
    (void)record;
    if (sub != (uint32_t *)0) {
        ((uint8_t *)sub)[0x14] = 3;
    }
    return sub != (uint32_t *)0;
}

void set_byte_f7_to_1(uint32_t *object)
{
    uint32_t *mid = (uint32_t *)(uintptr_t)object[1];
    uint32_t *target = *(uint32_t **)(uintptr_t)((uint8_t *)mid + 0xb08);
    *(uint8_t *)(uintptr_t)((uint8_t *)target + 0xf7) = 1;
}

void set_byte_f7_to_fa(uint32_t *object)
{
    uint32_t *mid = (uint32_t *)(uintptr_t)object[1];
    uint32_t *target = *(uint32_t **)(uintptr_t)((uint8_t *)mid + 0xb08);
    *(uint8_t *)(uintptr_t)((uint8_t *)target + 0xf7) = 0xfa;
}

void set_byte_90_and_91(uint8_t *object, uint8_t a, uint8_t b)
{
    object[0x90] = a;
    object[0x91] = b;
}

void advance_byte_by_two(uint8_t *object)
{
    object[1] = (uint8_t)(object[0] + 2);
}

void set_byte_4_and_word_8(uint8_t *object, uint8_t a, uint32_t b)
{
    object[4] = a;
    *(uint32_t *)(object + 8) = b;
}

void clear_byte_and_four_words(uint8_t *object)
{
    object[0] = 0;
    *(uint32_t *)(object + 1) = 0;
    *(uint32_t *)(object + 5) = 0;
    *(uint32_t *)(object + 9) = 0;
    *(uint32_t *)(object + 0xd) = 0;
}

uint32_t initialize_pair_record(uint8_t *record, uint32_t value)
{
    *(uint32_t *)(record + 8) = value;
    record[0] = 0;
    record[1] = 0;
    record[2] = 0;
    record[3] = 0;
    *(uint32_t *)(record + 4) = 0;
    return 1;
}

void noop_o(void)
{
}

void noop_p(void)
{
}

uint32_t get_word_b08_offset_4c(const uint32_t *object)
{
    return object[0xb08 / 4] + 0x4c;
}

void clear_word_20(uint32_t *object)
{
    object[0x20 / 4] = 0;
}

void set_word_1d0_and_link(uint32_t *object, uint32_t *node)
{
    object[0x1d0 / 4] = (uint32_t)(uintptr_t)node;
    if (node != (uint32_t *)0) {
        node[0] = (uint32_t)(uintptr_t)object;
    }
}

void set_byte_pair_481_482(uint8_t *object, uint8_t a, uint8_t b)
{
    object[0x481] = a;
    object[0x482] = b;
}

void or_halfword_e8_10(uint8_t *object)
{
    *(uint16_t *)(object + 0xe8) = *(uint16_t *)(object + 0xe8) | 0x10;
}

void or_word_48_8(uint32_t *object)
{
    object[0x48 / 4] = object[0x48 / 4] | 8;
}

uint32_t or_word_48_2_if_nonzero(uint32_t *object, uint32_t value)
{
    if (value != 0) {
        object[0x48 / 4] = object[0x48 / 4] | 2;
    }
    return value;
}

uint32_t or_word_48_1_if_nonzero(uint32_t *object, uint32_t value)
{
    if (value != 0) {
        object[0x48 / 4] = object[0x48 / 4] | 1;
    }
    return value;
}

void clear_halfword_c(uint8_t *object)
{
    *(uint16_t *)(object + 0xc) = 0;
}

void store_pointed_244_248(uint32_t *object, const uint32_t *value)
{
    object[0x244 / 4] = value[0];
    object[0x248 / 4] = value[1];
}

void store_pointed_250_254(uint32_t *object, const uint32_t *value)
{
    object[0x250 / 4] = value[0];
    object[0x254 / 4] = value[1];
}

void store_pointed_25c_260(uint32_t *object, const uint32_t *value)
{
    object[0x25c / 4] = value[0];
    object[0x260 / 4] = value[1];
}

void store_indexed_d0_80(uint32_t *object, uint32_t index, uint32_t value)
{
    *(uint32_t *)(uintptr_t)(object[0x10 / 4] + index * 0xd0 + 0x80) = value;
}

void clear_halfword_bit(uint8_t *object, uint32_t bit)
{
    *(uint16_t *)(object + 8) = *(uint16_t *)(object + 8) & ~(uint16_t)(1 << (bit & 0xff));
}

void set_halfword_bit(uint8_t *object, uint32_t bit)
{
    *(uint16_t *)(object + 8) = *(uint16_t *)(object + 8) | (uint16_t)(1 << (bit & 0xff));
}

void set_byte_6_and_mark(uint8_t *object, uint8_t value)
{
    if (object[6] != value) {
        object[0x4fa] = object[0x4fa] | 1;
    }
    object[6] = value;
}

void set_sub_record_pointer(uint32_t *object, uint32_t index)
{
    object[0x178 / 4] = (uint32_t)(uintptr_t)((uint8_t *)object + index * 0x2c + 0x120);
}

void append_counted_value(uint32_t *object, uint32_t value)
{
    uint32_t count = object[0x134 / 4];
    object[0x134 / 4] = count + 1;
    object[count + 1] = value;
}

void noop_q(void)
{
}

void noop_r(void)
{
}

uint16_t get_pointed_halfword_22(const uint32_t *object)
{
    uint16_t result = 0;
    if (object[1] != 0) {
        result = *(const uint16_t *)(uintptr_t)(object[1] + 0x22);
    }
    return result;
}

int32_t get_float_as_int_8c(const uint32_t *object)
{
    return (int32_t)object[0x8c / 4];
}

void store_triple_5c(uint32_t *object, const uint32_t *value)
{
    object[0x5c / 4] = value[0];
    object[0x60 / 4] = value[1];
    object[0x64 / 4] = value[2];
}

void store_triple_50(uint32_t *object, const uint32_t *value)
{
    object[0x50 / 4] = value[0];
    object[0x54 / 4] = value[1];
    object[0x58 / 4] = value[2];
}

void store_triple_44(uint32_t *object, const uint32_t *value)
{
    object[0x44 / 4] = value[0];
    object[0x48 / 4] = value[1];
    object[0x4c / 4] = value[2];
}

uint32_t test_low_bit(const uint8_t *object)
{
    uint8_t bit = object[0] & 1;
    if ((object[0] & 1) != 0) {
        bit = 1;
    }
    return bit;
}

uint32_t get_indexed_entry_by_byte(uint32_t *object, uint32_t index)
{
    if ((index & 0xff) == 0xff) {
        return 0;
    }
    uint32_t *table = (uint32_t *)(uintptr_t)object[0x110 / 4];
    return *(uint32_t *)(uintptr_t)(table[2] + (index & 0xff) * 4);
}

void set_high_bitset_bit(uint32_t *bitset, uint32_t bit)
{
    bitset[(bit >> 5)] = bitset[(bit >> 5)] | (0x80000000u >> (bit & 0x1f));
}

void clear_high_bitset_bit(uint32_t *bitset, uint32_t bit)
{
    bitset[(bit >> 5)] = bitset[(bit >> 5)] & ~(0x80000000u >> (bit & 0x1f));
}

void set_quad_2e0(uint32_t *object, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    object[0x2e0 / 4] = a;
    object[0x2e4 / 4] = b;
    object[0x2e8 / 4] = c;
    object[0x2ec / 4] = d;
}

int32_t get_signed_byte_148(const uint8_t *object)
{
    return (int32_t)(int8_t)object[0x148];
}

uint32_t get_indexed_record_a0(const uint32_t *object, uint32_t index)
{
    return object[0x28 / 4] + index * 0xa0;
}

uint32_t get_nested_table_entry(const uint32_t *object)
{
    const uint32_t *table = (const uint32_t *)(uintptr_t)object[1];
    return *(const uint32_t *)(uintptr_t)(table[0] + table[0xc / 4 * 4] + 8);
}

void noop_s(void)
{
}

uint32_t get_indexed_field_10c(uint32_t *object, uint32_t index)
{
    return object[0x10c / 4] + index * 0x1c;
}

uint32_t get_low_bit_3c(const uint8_t *object)
{
    return object[0x3c] & 1;
}

uint32_t get_nested_table_word(const uint32_t *object)
{
    const uint32_t *table = (const uint32_t *)(uintptr_t)object[1];
    return *(const uint32_t *)(uintptr_t)(table[0] + table[0x30 / 4] + 8);
}

uint32_t allocate_from_arena(uint32_t *object, uint32_t size)
{
    uint32_t used = object[0x5d0 / 4];
    uint32_t next = size + used;
    uint32_t result;
    if (next < 0x5c1) {
        result = (uint32_t)(uintptr_t)((uint8_t *)object + 0x10 + used);
        object[0x5d0 / 4] = next;
    } else {
        result = 0;
    }
    return result;
}

void set_pair_bc8(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0xbc8 / 4] = a;
    object[0xbcc / 4] = b;
}

void copy_pair_with_halfword(uint32_t *dest, const uint32_t *src)
{
    dest[0] = src[0];
    *(uint16_t *)(dest + 1) = *(const uint16_t *)(src + 1);
}

void copy_pair_with_byte(uint32_t *dest, const uint32_t *src)
{
    dest[0] = src[0];
    *(uint8_t *)(dest + 1) = *(const uint8_t *)(src + 1);
}

void clear_word_18_b(uint32_t *object)
{
    object[0x18 / 4] = 0;
}

void clear_eight_words(uint32_t *object)
{
    object[4 / 4] = 0;
    object[8 / 4] = 0;
    object[0xc / 4] = 0;
    object[0x10 / 4] = 0;
    object[0x14 / 4] = 0;
    object[0x18 / 4] = 0;
    object[0x1c / 4] = 0;
    object[0x20 / 4] = 0;
}

void clear_word_4_and_halfword_8(uint32_t *object)
{
    object[4 / 4] = 0;
    *(uint16_t *)(object + 8 / 4) = 0;
}

void clear_word_and_halfword_1(uint32_t *object)
{
    object[0] = 0;
    *(uint16_t *)(object + 1) = 0;
}

void set_byte_10_1(uint8_t *object)
{
    object[0x10] = 1;
}

void clear_byte_pair_1_2(uint8_t *object)
{
    object[1] = 0;
    object[2] = 0;
}

void clear_first_word_c(uint32_t *object)
{
    object[0] = 0;
}

void set_word_1b8_if_different(uint32_t *object, uint32_t value)
{
    if (object[0x1b8 / 4] != value) {
        object[0x1b8 / 4] = value;
    }
}

void set_pointed_word_10_and_clear(uint32_t *object, uint32_t *sub, uint32_t value)
{
    sub[0x10 / 4] = value;
    object[0] = 0;
}

void clear_word_and_byte_1(uint32_t *object)
{
    object[0] = 0;
    ((uint8_t *)object)[1] = 0;
}

void set_self_link_4(uint32_t *object)
{
    object[4 / 4] = (uint32_t)(uintptr_t)(object + 4 / 4);
    object[8 / 4] = (uint32_t)(uintptr_t)(object + 4 / 4);
    object[0xc / 4] = 0;
}

void set_byte_1_2_clear(uint8_t *object)
{
    object[1] = 0;
    object[2] = 0;
}

void clear_byte_4_b(uint8_t *object)
{
    object[4] = 0;
}

void add_to_word_184(uint32_t *object, uint32_t value)
{
    object[0x184 / 4] = value + object[0x184 / 4];
}

void set_byte_1ac6_ff(uint8_t *object)
{
    object[0x1ac6] = 0xff;
}

void store_quad_58(uint32_t *object, const uint32_t *value)
{
    object[0x58 / 4] = value[0];
    object[0x5c / 4] = value[1];
    object[0x60 / 4] = value[2];
    object[0x64 / 4] = value[3];
}

uint32_t check_pair_480_481(const uint8_t *object)
{
    int match = ((const int8_t *)object)[0x481] == ((const int8_t *)object)[0x480];
    uint32_t value = match ? (uint32_t)object[0x482] : 0;
    if (!match || value != 0) {
        value = 1;
    }
    return value;
}

uint32_t check_idle_1fd_201(const uint8_t *object)
{
    int idle = ((const int8_t *)object)[0x1fd] == 0;
    uint32_t value = idle ? (uint32_t)object[0x201] : 0;
    return idle && value == 0;
}

void clear_record_with_list_head(uint32_t *record)
{
    record[1] = 0;
    record[2] = 0;
    record[0] = 0;
    *(uint16_t *)(record + 3) = 0;
    ((uint8_t *)record)[0xe] = 0;
    record[5] = 0;
    record[6] = 0;
}

uint32_t get_indexed_pointed_word(uint32_t *object, uint32_t index)
{
    uint32_t **table = *(uint32_t ***)(uintptr_t)object[2];
    return *(uint32_t *)(uintptr_t)((uint8_t *)table + index * 4);
}

void noop_w(void)
{
}

void noop_x(void)
{
}

void noop_y(void)
{
}

void noop_z(void)
{
}

uint32_t is_decimal_digit(uint32_t value)
{
    if (value - 0x30 < 10) {
        return 1;
    }
    return 0;
}

void copy_field_c_to_14(uint32_t *object)
{
    object[0x14 / 4] = object[0xc / 4];
}

void clear_pair_0_1(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
}

void set_word_3c_offset_8(uint32_t *object, uint32_t value)
{
    object[0x3c / 4] = value + 8;
}

void set_word_38_offset_8(uint32_t *object, uint32_t value)
{
    object[0x38 / 4] = value + 8;
}

void clear_triple_0(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = 0;
}

void set_byte_2c_if_different(uint8_t *object, uint8_t value)
{
    if (object[0x2c] != value) {
        object[0x2c] = value;
        *(uint16_t *)(object + 0x20) = *(uint16_t *)(object + 0x20) | 8;
    }
}

void set_byte_2d_if_different(uint8_t *object, uint8_t value)
{
    if (object[0x2d] != value) {
        object[0x2d] = value;
        *(uint16_t *)(object + 0x20) = *(uint16_t *)(object + 0x20) | 8;
    }
}

void set_byte_15_1_and_clear_17(uint8_t *object)
{
    object[0x15] = 1;
    object[0x17] = 0;
}

void set_byte_83(uint8_t *object, uint8_t value)
{
    object[0x83] = value;
}

void set_byte_f4(uint8_t *object, uint8_t value)
{
    object[0xf4] = value;
}

void set_indexed_halfword_10c(uint8_t *object, uint32_t index, uint16_t value)
{
    *(uint16_t *)(object + index * 2 + 0x10c) = value;
}

void set_byte_f0(uint8_t *object, uint8_t value)
{
    object[0xf0] = value;
}

void set_pair_8c_90(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0x8c / 4] = a;
    object[0x90 / 4] = b;
}

void add_to_word_16c(uint32_t *object, uint32_t value)
{
    object[0x16c / 4] = value + object[0x16c / 4];
}

void or_word_48_c400(uint32_t *object)
{
    object[0x48 / 4] = object[0x48 / 4] | 0xc400;
}

void set_word_4(uint32_t *object, uint32_t value)
{
    object[4 / 4] = value;
}

void increment_word_1c(uint32_t *object)
{
    object[0x1c / 4] = object[0x1c / 4] + 1;
}

void set_pair_14_6c(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0x14 / 4] = a;
    object[0x6c / 4] = b;
}

void clear_halfwords_a0_a2(uint8_t *object)
{
    *(uint16_t *)(object + 0xa0) = 0;
    *(uint16_t *)(object + 0xa2) = 0;
}

void clear_first_word_d(uint32_t *object)
{
    object[0] = 0;
}

void noop_aa(void)
{
}

void noop_ab(void)
{
}

void noop_ac(void)
{
}

void noop_ad(void)
{
}

void clear_word_0_e(uint32_t *object)
{
    object[0] = 0;
}

void clear_word_0_f(uint32_t *object)
{
    object[0] = 0;
}

void set_byte_1621_1(uint8_t *object)
{
    object[0x1621] = 1;
}

void set_triple_halfword_pairs(uint8_t *object, uint16_t a, uint16_t b, uint16_t c)
{
    *(uint16_t *)(object + 0x94) = a;
    *(uint16_t *)(object + 0x92) = a;
    *(uint16_t *)(object + 0x98) = b;
    *(uint16_t *)(object + 0x96) = b;
    *(uint16_t *)(object + 0x9c) = c;
    *(uint16_t *)(object + 0x9a) = c;
}

void clear_byte_1d08(uint8_t *object)
{
    object[0x1d08] = 0;
}

void clear_byte_2e05(uint8_t *object)
{
    object[0x2e05] = 0;
}

void clear_pair_4_8(uint32_t *object)
{
    object[4 / 4] = 0;
    object[8 / 4] = 0;
}

void and_word_4_fffd(uint32_t *object)
{
    object[4 / 4] = object[4 / 4] & 0xfffffffd;
}

void set_byte_14_10(uint8_t *object)
{
    object[0x14] = 10;
}

void set_byte_970_1(uint8_t *object)
{
    object[0x970] = 1;
}

void clear_byte_f88(uint8_t *object)
{
    object[0xf88] = 0;
}

void set_byte_f88_1(uint8_t *object)
{
    object[0xf88] = 1;
}

void set_byte_150e(uint8_t *object, uint8_t value)
{
    object[0x150e] = value;
}

void set_byte_150d(uint8_t *object, uint8_t value)
{
    object[0x150d] = value;
}

void clear_byte_428(uint8_t *object)
{
    object[0x428] = 0;
}

void clear_word_3e4(uint32_t *object)
{
    object[0x3e4 / 4] = 0;
}

void set_byte_200_1(uint8_t *object)
{
    object[0x200] = 1;
}

void set_word_4_b(uint32_t *object, uint32_t value)
{
    object[1] = value;
}

void clear_halfword_58(uint8_t *object)
{
    *(uint16_t *)(object + 0x58) = 0;
}

void clear_pair_368_36c(uint32_t *object)
{
    object[0x368 / 4] = 0;
    object[0x36c / 4] = 0;
}

void set_halfword_c_108(uint8_t *object)
{
    *(uint16_t *)(object + 0xc) = 0x108;
}

void clear_byte_589(uint8_t *object)
{
    object[0x589] = 0;
}

void copy_byte_1b31_to_1b30(uint8_t *object)
{
    object[0x1b30] = object[0x1b31];
}

void set_byte_15c5_if_set(uint8_t *object)
{
    if (object[0x15c4] != 0) {
        object[0x15c5] = 1;
    }
}

void set_byte_24cd_if_set(uint8_t *object)
{
    if (object[0x24cc] != 0) {
        object[0x24cd] = 1;
    }
}

void clear_byte_4_and_mask_e4(uint8_t *object)
{
    object[4] = 0;
    object[0xe4] = object[0xe4] & 0xfb;
}

void clear_record_3b303c(uint32_t *record)
{
    record[0] = 0;
    ((uint8_t *)record)[4] = 0;
    ((uint8_t *)record)[5] = 0;
}

uint32_t get_byte_5_if_state_1(const uint8_t *object)
{
    if (((const int8_t *)object)[4] == 1) {
        return (uint32_t)(uint8_t)object[5];
    }
    return 0;
}

void noop_af(void)
{
}

void noop_ba(void)
{
}

void noop_bb(void)
{
}

uint32_t get_constant_10(void)
{
    return 0x10;
}

uint32_t get_constant_4(void)
{
    return 4;
}

uint32_t get_constant_8(void)
{
    return 8;
}

void noop_bd(void)
{
}

void noop_be(void)
{
}

void noop_bf(void)
{
}

void noop_c0(void)
{
}

void noop_c1(void)
{
}

void noop_c2(void)
{
}

uint32_t add_field_3c(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[0x3c / 4];
}

uint32_t add_field_2c(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[0x2c / 4];
}

uint32_t add_field_c(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[0xc / 4];
}

uint32_t add_field_1c(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[0x1c / 4];
}

uint32_t add_field_14(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[0x14 / 4];
}

uint32_t add_field_10(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[0x10 / 4];
}

uint32_t add_field_4(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[4 / 4];
}

uint32_t add_field_8(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[8 / 4];
}

void noop_c3(void)
{
}

void noop_c4(void)
{
}

void noop_c5(void)
{
}

void noop_c6(void)
{
}

uint32_t clear_byte_24d_and_confirm(uint8_t *object)
{
    object[0x24d] = 0;
    return 1;
}

void clear_pair_54_58(uint32_t *object)
{
    object[0x54 / 4] = 0;
    object[0x58 / 4] = 0;
}

void set_byte_2a_1(uint8_t *object)
{
    object[0x2a] = 1;
}

void copy_fields_4_8_to_138(uint32_t *object)
{
    object[0x138 / 4] = object[4 / 4];
    object[0x13c / 4] = object[8 / 4];
    *(uint16_t *)((uint8_t *)object + 0x140) = 0;
    object[0x19c / 4] = 0;
}

void initialize_link_record(uint8_t *record)
{
    record[0] = 1;
    *(uint32_t *)(record + 4) = 0xffffffff;
    *(uint32_t *)(record + 0x14) = 0;
    *(uint32_t *)(record + 0x1c) = 0;
    *(uint32_t *)(record + 8) = 0xffffffff;
    *(uint32_t *)(record + 0x20) = 0;
    *(uint32_t *)(record + 0xc) = 0xffffffff;
    *(uint32_t *)(record + 0x10) = 0;
}

void clear_byte_5_to_2(uint8_t *object)
{
    object[5] = 2;
}

uint32_t copy_record_if_different(uint32_t *dest, const uint32_t *src)
{
    if (dest != src) {
        copy_pair_with_halfword(dest + 4 / 4, src + 4 / 4);
        *(uint16_t *)((uint8_t *)dest + 0xc) = *(const uint16_t *)((const uint8_t *)src + 0xc);
    }
    return (uint32_t)(uintptr_t)dest;
}

int is_not_type_8579(uint32_t value)
{
    return value != 0x8579;
}

void initialize_state_record(uint32_t *record)
{
    record[0] = 0;
    record[1] = 0;
    record[2] = 0;
    ((uint8_t *)record)[0xc] = 0;
    ((uint8_t *)record)[0xd] = 0xff;
    ((uint8_t *)record)[0xe] = 0;
    ((uint8_t *)record)[0xf] = 0;
}

void set_self_link_2(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = (uint32_t)(uintptr_t)(object + 2);
    object[3] = (uint32_t)(uintptr_t)(object + 2);
}

void initialize_link_record_full(uint32_t *record)
{
    record[0] = 0;
    record[1] = 0xffffffff;
    ((uint8_t *)record)[0xc] = 0;
    record[0x25] = 0;
    record[0x27] = 0;
    ((uint8_t *)record)[0xa0] = 3;
    record[0x29] = 0;
    record[0x2a] = 0;
    record[0x2f] = 0;
}

void initialize_tagged_record(uint32_t *record, uint32_t tag)
{
    record[1] = 0;
    record[0] = 0x10000;
    record[2] = 0;
    ((uint8_t *)record)[0xc] = 0;
    ((uint8_t *)record)[0xd] = 0;
    record[6] = tag;
    record[5] = 0;
    record[4] = 0;
}

void initialize_tagged_record_b(uint32_t *record, uint32_t tag)
{
    record[1] = 0;
    record[0] = 0x10000;
    record[2] = 0;
    record[3] = 0;
    ((uint8_t *)record)[0x10] = 0;
    ((uint8_t *)record)[0x11] = 0;
    record[7] = tag;
    record[6] = 0;
    record[5] = 0;
}

void set_pair_1cc_1cd_if_different(uint8_t *object, uint8_t a, uint8_t b)
{
    if (object[0x1cc] != a || object[0x1cd] != b) {
        object[0x1cc] = a;
        object[0x1cd] = b;
    }
}

uint32_t get_state_1a_mapped(const uint8_t *object)
{
    int8_t state = (int8_t)object[0x1a];
    if (state != 0) {
        if (state == 3) {
            return 0;
        }
        if (state == 4) {
            return 2;
        }
    }
    return 1;
}

uint32_t get_state_4e_mapped(const uint8_t *object)
{
    int8_t state = (int8_t)object[0x4e];
    if (state == 0) {
        return 2;
    }
    if (state == 3) {
        return 1;
    }
    return 0;
}

void clear_byte_5c(uint8_t *object)
{
    object[0x5c] = 0;
}

void clear_word_0_and_byte_10_11(uint32_t *object)
{
    object[1] = 0;
    object[0] = 0x10000;
    object[2] = 0;
    object[3] = 0;
    ((uint8_t *)object)[0x10] = 0;
    ((uint8_t *)object)[0x11] = 0;
}

void clear_word_0_1_and_halfword_2(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    *(uint16_t *)(object + 2) = 0;
}

void clear_byte_5c_and_call_clear(uint8_t *object)
{
    object[0x5c] = 0;
}

void clear_byte_5c_b(uint8_t *object)
{
    object[0x5c] = 0;
}

void noop_cb(void)
{
}

void push_tagged_818(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[0x818 / 4];
    object[0x818 / 4] = (uint32_t)(uintptr_t)(cursor + 2);
    if (cursor != (uint32_t *)0) {
        cursor[0] = value;
        cursor[1] = 3;
    }
    object[0x810 / 4] = object[0x810 / 4] + 1;
}

void push_tagged_c(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[0xc / 4];
    object[0xc / 4] = (uint32_t)(uintptr_t)(cursor + 2);
    if (cursor != (uint32_t *)0) {
        cursor[0] = value;
        cursor[1] = 3;
    }
    object[4 / 4] = object[4 / 4] + 1;
}

void clear_byte_5c_c(uint8_t *object)
{
    object[0x5c] = 0;
}

void set_byte_290_if_0x102(uint8_t *object)
{
    if (*(int16_t *)(object + 0x1c) == 0x102) {
        object[0x290] = 1;
    }
}

void clear_state_record_970c(uint32_t *record)
{
    record[3] = 0;
    ((uint8_t *)record)[0x14] = 0;
    ((uint8_t *)record)[0x15] = 0;
    ((uint8_t *)record)[0x16] = 0;
    ((uint8_t *)record)[0x17] = 0;
    *(uint16_t *)((uint8_t *)record + 0x20) = 0;
    record[0x16] = 0;
    record[0x17] = 0;
    record[0] = 0;
    record[1] = 0;
}

void initialize_state_record_788c(uint32_t *record)
{
    record[0] = 0;
    record[1] = 0;
    record[2] = 2;
    record[3] = 0;
    record[4] = 0;
    record[5] = 2;
    record[6] = 0;
    ((uint8_t *)record)[0x1c] = 0;
}

void set_byte_4_or_bit(uint8_t *object, uint32_t bit)
{
    object[4] = object[4] | (uint8_t)(1 << (bit & 0xff));
}

void set_pointed_word_3c(uint32_t *object, uint32_t value)
{
    *(uint32_t *)(uintptr_t)(object[0x90 / 4] + 0x3c) = value;
}

void set_byte_2_and_flag(uint8_t *object, uint32_t bit)
{
    if (object[2] == 0) {
        clear_byte_pair_1_2(object + 0x54);
    }
    object[2] = object[2] | (uint8_t)(1 << (bit & 0xff));
}

void clear_byte_49a_and_set_234(uint8_t *object)
{
    if (object[0x49a] != 0) {
        *(uint16_t *)(object + 0x234) = *(uint16_t *)(object + 0x234) | 1;
    }
}

void copy_state_and_clear(uint8_t *dest, const uint8_t *src)
{
    dest[0] = src[0];
    *(uint32_t *)(dest + 4) = 0;
    *(uint32_t *)(dest + 8) = 0;
    *(uint32_t *)(dest + 0xc) = 0;
    *(uint32_t *)(dest + 0x10) = 0;
    dest[0x14] = 0;
    *(uint32_t *)(dest + 0x18) = 0;
    dest[0x20] = 0;
}

void clear_word_14_and_set_word_c(uint32_t *object, uint32_t value)
{
    object[0x14 / 4] = 0;
    object[0xc / 4] = value;
}

uint32_t find_offset_for_type_6800(const uint8_t *object)
{
    uint32_t offset;
    if (*(const uint16_t *)(object + 0x14) == 0x6800) {
        offset = 0x14;
    } else if (*(const uint16_t *)(object + 0x20) == 0x6800) {
        offset = 0x20;
    } else {
        offset = 0;
    }
    return (uint32_t)(uintptr_t)object + *(const uint32_t *)(object + offset + 4);
}

uint32_t get_field_after_type_6800(const uint8_t *object)
{
    if (*(const uint16_t *)(object + 0x14) == 0x6800) {
        object = object + 0x14;
    } else if (*(const uint16_t *)(object + 0x20) == 0x6800) {
        object = object + 0x20;
    } else {
        object = NULL;
    }
    return *(const uint32_t *)(object + 4);
}

uint32_t get_record_entry_field(uint32_t *record, uint32_t index)
{
    if (*(const uint8_t *)(record + 3) == 0) {
        return 0;
    }
    return *(const uint32_t *)(uintptr_t)((uintptr_t)record[1] + index * 0xc + 0xc);
}

void store_indexed_entry_pointer(uint32_t *out, uint32_t *object, uint32_t index)
{
    uint32_t value;
    uint32_t base = *(const uint32_t *)((uint8_t *)object + 4);
    if (index < *(const uint32_t *)(uintptr_t)(base + 4)) {
        value = base + *(const uint32_t *)(uintptr_t)(base + 8 + index * 4);
    } else {
        value = 0;
    }
    *out = value;
}

uint32_t map_mode_to_state(uint32_t object)
{
    switch (*(const uint8_t *)(uintptr_t)(object + 0x14)) {
    case 2:
    case 6:
    case 10:
    case 14:
    case 18:
    case 22:
        return 3;
    case 3:
    case 7:
    case 11:
    case 15:
    case 19:
    case 23:
        return 1;
    case 4:
    case 8:
    case 9:
    case 16:
    case 20:
    case 21:
        return 2;
    default:
        return 0;
    }
}

uint32_t check_mode_flag(uint32_t object)
{
    uint8_t mode = *(const uint8_t *)(uintptr_t)(object + 0x31e);
    if (mode == 1) {
        return 1;
    }
    if (mode == 2 && *(const uint8_t *)(uintptr_t)(object + 799) == 0x1e) {
        return 1;
    }
    return 0;
}

void reset_counter_and_copy(uint32_t *record)
{
    uint32_t i;
    for (i = 0; i < record[0x2a8 / 4]; i++) {
    }
    record[0x2a8 / 4] = 0;
    record[0x2b0 / 4] = record[0x2ac / 4];
}

void init_record_738(uint32_t *object)
{
    object[0x8ec / 4] = (uint32_t)(uintptr_t)object + 0x738;
    object[0x73c / 4] = object[1];
    object[0x740 / 4] = object[2];
    *(uint16_t *)((uint8_t *)object + 0x744) = 0;
}

uint32_t check_nested_chain_10_90_8(const uint32_t *object)
{
    uint32_t mid = *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)((const uint8_t *)object + 4) + 0x10);
    uint32_t next = 0;
    if (mid != 0) {
        next = *(const uint32_t *)(uintptr_t)(mid + 0x90);
    }
    if (mid != 0 && next != 0 && *(const uint32_t *)(uintptr_t)(next + 8) != 0) {
        return 1;
    }
    return 0;
}

void set_byte_c4d_if_valid(uint8_t *object)
{
    if (*(const int16_t *)(uintptr_t)(*(const uint32_t *)(object + 0xb08) + 0x150) > 0 && *(const uint32_t *)(object + 0xc48) != 0) {
        object[0xc4d] = 1;
    }
}

uint32_t check_nested_chain_10_90_8_b(const uint32_t *object)
{
    uint32_t mid = *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)((const uint8_t *)object + 4) + 0x10);
    uint32_t next = 0;
    if (mid != 0) {
        next = *(const uint32_t *)(uintptr_t)(mid + 0x90);
    }
    if (mid != 0 && next != 0 && *(const uint32_t *)(uintptr_t)(next + 8) != 0) {
        return 1;
    }
    return 0;
}

void unlink_list_node(uint32_t *node)
{
    if (node[0] != 0) {
        *(uint32_t *)(uintptr_t)(node[0] + 4) = node[1];
    }
    if (node[1] != 0) {
        *(uint32_t *)(uintptr_t)node[1] = node[0];
    }
    node[1] = 0;
    node[0] = 0;
}

uint32_t append_if_room(uint32_t *object, uint32_t value)
{
    int index = object[0x34 / 4];
    if (index < 0xc) {
        object[0x34 / 4] = index + 1;
        object[1 + index] = value;
    }
    return index < 0xc;
}

void move_list_entry(uint32_t *list, uint32_t *entry)
{
    remove_list_entry((uint32_t *)((uint8_t *)list + 4), (uint32_t *)(uintptr_t)((uint8_t *)entry + 0x58));
    insert_list_after((uint32_t *)((uint8_t *)list + 0x10), (uint32_t *)((uint8_t *)list + 0x14), (uint32_t *)(uintptr_t)((uint8_t *)entry + 0x58));
}

void write_be32(uint8_t *object, uint32_t value, uint32_t offset)
{
    uint8_t *dest = (uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 0x1c) + offset + 0x14);
    dest[0] = (uint8_t)(value >> 0x18);
    dest[1] = (uint8_t)(value >> 0x10);
    dest[2] = (uint8_t)(value >> 8);
    dest[3] = (uint8_t)value;
}

uint64_t shift_right_64(uint32_t low, uint32_t high, uint32_t shift)
{
    if ((int)(shift - 0x20) < 0) {
        return ((uint64_t)(high >> (shift & 0xff)) << 32) |
               (low >> (shift & 0xff) | high << ((0x20 - shift) & 0xff));
    }
    return (uint64_t)(high >> ((shift - 0x20) & 0xff));
}

void allocate_and_clear(uint32_t object, uint32_t size)
{
    uint32_t ptr = allocate_from_arena((uint32_t *)(uintptr_t)object, size);
    *(uint32_t *)(uintptr_t)((size & 0xfffffffc) + ptr - 4) = 0;
}

void init_record_fields(uint32_t *record, const uint32_t *src, uint32_t value, uint8_t flag_a, uint8_t flag_b)
{
    record[0] = value;
    record[3] = src[0];
    *(uint8_t *)((uint8_t *)record + 0x14) = flag_a;
    *(uint8_t *)((uint8_t *)record + 0x15) = flag_b;
    record[4] = 0;
    *(uint8_t *)((uint8_t *)record + 0xcc) = 0;
    record[0x32] = 0;
}

uint32_t count_list_entries(uint32_t *object)
{
    uint32_t node = object[3];
    uint32_t count = 0;
    if (node != (uint32_t)(uintptr_t)object + 8) {
        do {
            node = *(const uint32_t *)(uintptr_t)(node + 4);
            count = count + 1;
        } while (node != (uint32_t)(uintptr_t)object + 8);
    }
    return count;
}

int32_t wrap_index(int32_t *object, int32_t value)
{
    int32_t range = *(const int32_t *)(uintptr_t)((uint8_t *)object + 0x668);
    int32_t index = *(const int32_t *)(uintptr_t)((uint8_t *)object + 0x684) + (value - *(const int32_t *)(uintptr_t)((uint8_t *)object + 0x674));
    if (index < 0) {
        index = index + range;
    } else if (range <= index) {
        index = index - range;
    }
    return index;
}

uint32_t set_halfword_6c_if_valid(uint8_t *object)
{
    if (*(const int16_t *)(object + 0x6e) != 0 && *(const int16_t *)(object + 0x6e) != 2) {
        *(uint16_t *)(object + 0x6c) = 2;
        return 1;
    }
    return 0;
}

void unlink_circular_entry(uint32_t *object)
{
    uint32_t head = object[0x228 / 4];
    uint32_t entry = *(const uint32_t *)(uintptr_t)(head + 0x154);
    if (entry != head) {
        *(uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(entry + 0x154) + 0x150) = head;
        *(uint32_t *)(uintptr_t)(object[0x228 / 4] + 0x154) = *(const uint32_t *)(uintptr_t)(entry + 0x154);
    }
}

uint32_t check_nested_chain_10_90_8_c(const uint32_t *object)
{
    uint32_t mid = *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)((const uint8_t *)object + 4) + 0x10);
    uint32_t next = 0;
    if (mid != 0) {
        next = *(const uint32_t *)(uintptr_t)(mid + 0x90);
    }
    if (mid != 0 && next != 0 && *(const uint32_t *)(uintptr_t)(next + 8) != 0) {
        return 1;
    }
    return 0;
}

int32_t clamp_toward_target(int32_t value, int32_t target, int32_t step)
{
    if (target < value) {
        value = value - step;
        if (value <= target) {
            return target;
        }
    } else {
        value = value + step;
        if (target <= value) {
            return target;
        }
    }
    return value;
}

void copy_two_halfwords(uint8_t *dest, const uint8_t *src)
{
    *(uint16_t *)(dest + 0x2c) = *(const uint16_t *)(src + 0x78);
    *(uint16_t *)(dest + 0x2e) = *(const uint16_t *)(src + 0x7a);
}

uint32_t classify_value_bits(uint32_t value)
{
    uint32_t result = 0;
    if ((value & 0x7fffff) != 0) {
        result = 4;
    }
    if ((value & 0x7fffffff) >> 0x17 != 0) {
        result = result | 1;
    }
    if ((~(value << 1) & 0xff000000) == 0) {
        result = result | 2;
    }
    if (result == 1) {
        result = 5;
    }
    return result;
}

uint32_t get_indexed_nested_table_entry(uint32_t *object, uint32_t index)
{
    uint32_t mid = object[1];
    uint32_t next = 0;
    if (mid != 0) {
        next = *(const uint32_t *)(uintptr_t)(mid + 0x10);
    }
    if (mid != 0 && next != 0) {
        next = *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(next + 0x90) + 0x1c) + index * 0x30;
    }
    return next;
}

int claim_once(uint32_t *flag);
static uint32_t global_accumulator;
static uint32_t singleton_flag;
static uint32_t singleton_storage[2];

uint32_t check_mode_31d_10(uint32_t object)
{
    if (*(const uint8_t *)(uintptr_t)(object + 0x31d) != 0) {
        uint32_t is_mode2 = *(const uint8_t *)(uintptr_t)(object + 0x31e) == 2;
        uint32_t value = object;
        if (is_mode2) {
            value = *(const uint8_t *)(uintptr_t)(object + 799);
        }
        if (!is_mode2 || value != 10) {
            return 1;
        }
    }
    return 0;
}

void copy_and_scale_vector(float *dest, const float *src, const uint8_t *object)
{
    float y;
    dest[0] = src[0];
    y = src[1];
    dest[1] = y;
    dest[2] = src[2];
    dest[1] = y + *(const float *)(object + 0x24) * *(const float *)(object + 0xcc);
}

void remove_counted_list_entry(uint32_t *owner, uint32_t *node)
{
    *(uint32_t *)(uintptr_t)(node[0] + 4) = node[1];
    *(uint32_t *)(uintptr_t)node[1] = node[0];
    node[0] = 0;
    node[1] = 0;
    *(uint32_t *)((uint8_t *)owner + 0xc) = *(const uint32_t *)((uint8_t *)owner + 0xc) - 1;
}

void insert_counted_list_entry(uint32_t *owner, uint32_t *at, uint32_t *node)
{
    node[0] = (uint32_t)(uintptr_t)at;
    node[1] = *(const uint32_t *)((uint8_t *)at + 4);
    *(uint32_t *)(uintptr_t)*(const uint32_t *)((uint8_t *)at + 4) = (uint32_t)(uintptr_t)node;
    *(uint32_t *)((uint8_t *)at + 4) = (uint32_t)(uintptr_t)node;
    *(uint32_t *)((uint8_t *)owner + 0xc) = *(const uint32_t *)((uint8_t *)owner + 0xc) + 1;
}

static const uint32_t default_record_value = 0;
void init_record_by_mode(uint8_t *record)
{
    if (record[3] == 0) {
        record[1] = 1;
        record[2] = 0;
        *(uint32_t *)(record + 4) = default_record_value;
    } else {
        record[2] = 1;
    }
}

uint32_t test_flag_bit_array(const uint8_t *object, uint32_t bit)
{
    if ((int)bit < 0x3c) {
        if ((object[(bit >> 3) + 0xf] & (1u << (bit & 7))) != 0) {
            return 1;
        }
    }
    return 0;
}

uint32_t get_field_by_code(const uint8_t *object, uint32_t code)
{
    if (code == 0x8ce0) {
        return *(const uint32_t *)(object + 0x10);
    }
    if (code == 0x100 || code == 0x821a) {
        return *(const uint32_t *)(object + 0x14);
    }
    return 0;
}

char *find_substring(char *haystack, const char *needle)
{
    char a, b;
    char *n;
    char *h;
    n = (char *)needle;
    h = haystack;
    for (;;) {
        a = *haystack;
        b = *n;
        haystack = haystack + 1;
        if (a == '\0') {
            break;
        }
        n = n + 1;
        if (a != b) {
            if (b == '\0') {
                return h;
            }
            if (a == '\0') {
                return NULL;
            }
            haystack = h + 1;
            n = (char *)needle;
            h = haystack;
        }
    }
    if (b == '\0') {
        return h;
    }
    return NULL;
}

int32_t finalize_counter_and_flag(uint8_t *object)
{
    int32_t diff = *(const int32_t *)(object + 0x10) - *(const int32_t *)(object + 0xc);
    if (diff != 0) {
        global_accumulator += diff;
    }
    object[0x11d] = 1;
    return diff;
}

uint32_t *get_or_init_singleton(void)
{
    if ((singleton_flag & 1) == 0 && claim_once(&singleton_flag)) {
        singleton_storage[0] = 0;
        singleton_storage[1] = 0;
    }
    return singleton_storage;
}

uint64_t shift_left_64(uint32_t low, uint32_t high, uint32_t shift)
{
    if ((int)(shift - 0x20) < 0) {
        return ((uint64_t)(high << (shift & 0xff) | low >> ((0x20 - shift) & 0xff)) << 32) |
               (uint64_t)(low << (shift & 0xff));
    }
    return (uint64_t)(low << ((shift - 0x20) & 0xff)) << 32;
}

int32_t clear_list_and_get_base(uint32_t *object)
{
    if (object[6] != 0) {
        int32_t base = object[7];
        clear_list(object + 6, object + 7);
        return base - 0x1c;
    }
    return 0;
}

uint32_t init_range_aligned(uint32_t *object, uint32_t start, uint32_t size)
{
    uint32_t end = size + start;
    uint32_t aligned = (start + 0x1f) & 0xffffffe0;
    if (aligned <= end) {
        object[3] = aligned;
        object[4] = end;
        object[5] = aligned;
    }
    return aligned <= end;
}

void init_record_offsets(uint32_t *record, uint32_t a, uint32_t b, uint32_t c, uint32_t base, uint32_t d)
{
    record[0] = a;
    record[1] = b;
    record[2] = c;
    record[7] = d;
    record[4] = base + 8;
    record[3] = base;
    record[5] = base + 0x10;
    record[6] = base + 0x18;
}

uint32_t map_type_code(uint32_t code)
{
    if (code == 5) {
        return 1;
    }
    if (code == 6) {
        return 2;
    }
    if (code == 0x6010 || code == 4) {
        return 3;
    }
    return 0;
}

void call_flag_if_nested_nonzero(uint32_t *object)
{
    uint32_t mid;
    if (object[6] == 0) {
        return;
    }
    mid = *(const uint32_t *)(uintptr_t)(object[6] + 0x5c);
    if (mid != 0) {
        or_word_48_1_if_nonzero(object, mid);
    }
}

void propagate_flag_change(uint8_t *object)
{
    uint32_t old = *(const uint32_t *)(object + 0x15c4);
    uint32_t now = *(const uint32_t *)(object + 0xc4) >> 0x18;
    uint8_t changed;
    *(uint32_t *)(object + 0x15c4) = now;
    changed = old != now;
    object[0x15c8] = changed;
    object[0x10f4] = changed;
}

void clear_indexed_word_54(uint32_t *object, uint32_t index)
{
    uint32_t table = *(const uint32_t *)(uintptr_t)(object[1] + 0x14);
    if (table != 0) {
        *(uint32_t *)(uintptr_t)(table + index * 0x54 + 0xc) = 0;
    }
}

uint32_t reset_state_fields(uint8_t *object)
{
    *(uint16_t *)(object + 0x98) = 0;
    object[0x108] = 0;
    object[0x109] = 0;
    advance_byte_by_two(object + 0x110);
    return 1;
}

uint32_t set_halfword_c_for_range(uint8_t *object)
{
    uint32_t value = *(const uint16_t *)(object + 0x1c);
    uint8_t match = value == 0x100;
    if (!match) {
        value = value - 0x101;
        match = value == 0;
    }
    if (!match && value == 1) {
        *(uint16_t *)(object + 0xc) = 0xb;
    }
    return 1;
}

int32_t compare_wide_string_bounded(const uint16_t *a, const uint16_t *b, int32_t count)
{
    uint32_t ca;
    for (;;) {
        if (count == 0) {
            return 0;
        }
        ca = *a;
        if (ca == 0 || ca != *b) {
            break;
        }
        a = a + 1;
        b = b + 1;
        count = count - 1;
    }
    return ca - *b;
}

uint32_t get_indexed_word_base(const uint32_t *object, uint32_t index)
{
    return object[0] + index * 4;
}

void svc_38_store(uint32_t *object, uint32_t value)
{
    *object = value;
}

void svc_21_store(uint32_t *object, uint32_t value)
{
    *object = value;
}

void clear_four_words_b(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = 0;
    object[3] = 0;
}

void clear_record_13(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = 0;
    *(uint8_t *)(object + 3) = 0;
}

void clear_two_bytes(uint8_t *object)
{
    object[0] = 0;
    object[1] = 0;
}

void init_pointer_pairs_500(uint32_t *object)
{
    object[0x500 / 4] = (uint32_t)(uintptr_t)object + 0x184;
    object[0x504 / 4] = (uint32_t)(uintptr_t)object + 0x14c;
    object[0x508 / 4] = 0;
    object[0x50c / 4] = 0;
}

void svc_2d_store(uint32_t *object, uint32_t value)
{
    *object = value;
}

uint32_t svc_25_store(uint32_t *object, uint32_t value, uint32_t unused_a, uint32_t unused_b, uint32_t result)
{
    (void)unused_a;
    (void)unused_b;
    *object = value;
    return result;
}

uint32_t return_minus_one(void)
{
    return 0xffffffff;
}

uint32_t return_minus_one_b(void)
{
    return 0xffffffff;
}

void svc_29_store_pair(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0] = a;
    object[1] = b;
}

uint32_t check_word_c_nonzero(const uint32_t *object)
{
    return object[3] != 0;
}

uint32_t check_words_not_fd(const uint32_t *object)
{
    uint32_t first_ok = object[0x94 / 4] != 0xfd;
    uint32_t second = object[0x98 / 4];
    if (first_ok) {
        second = object[0x98 / 4];
    }
    return first_ok && second != 0xfd;
}

uint32_t get_pointed_word_8(const uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(object[2] + 8);
}

uint32_t get_masked_entry_5c(const uint32_t *object, uint32_t index)
{
    return object[7] + (index & 0xffffff) * 0x5c;
}

void clear_word_14_only(uint32_t *object)
{
    object[5] = 0;
}

uint32_t get_self_offset_10d(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + 0x10d;
}

int32_t get_indexed_halfword_d4(const uint8_t *object, uint32_t index)
{
    return *(const int16_t *)(object + index * 2 + 0xd4);
}

void noop_g(void)
{
}

void copy_nine_words(uint32_t *dest, const uint32_t *src)
{
    uint32_t i;
    for (i = 0; i < 9; i++) {
        dest[i] = src[i];
    }
}

void copy_and_offset_vector(float *dest, const float *offset, const float *src)
{
    uint32_t i;
    for (i = 0; i < 12; i++) {
        dest[i] = src[i];
    }
    dest[3] = src[3] + offset[0];
    dest[7] = src[7] + offset[1];
    dest[0xb] = src[0xb] + offset[2];
}

void svc_b_store(uint32_t *object, uint32_t value)
{
    *object = value;
}

uint32_t check_word_b04_zero(const uint32_t *object)
{
    return object[0xb04 / 4] == 0;
}

uint32_t get_nested_word_8e8_14(const uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(object[0x8e8 / 4] + 0x14);
}

void mask_nested_word_48(uint32_t *object)
{
    uint32_t *mid = (uint32_t *)(uintptr_t)object[1];
    uint32_t *table = (uint32_t *)(uintptr_t)mid[0xb08 / 4];
    table[0x48 / 4] = table[0x48 / 4] & 0xffff7eff;
}

void init_record_1b34(uint8_t *object)
{
    *(uint32_t *)(object + 0x1b34) = 0;
    object[0x1b3a] = 0;
    object[0x1b3c] = 0;
    object[0x1b3d] = 0;
}

uint32_t check_word_8_nonzero(const uint32_t *object)
{
    return object[2] != 0;
}

void store_joy_and_flag_db(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xdb] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_da(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xda] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_d9(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd9] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_d8(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd8] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_e3(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xe3] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_e2(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xe2] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_e1(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xe1] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_e0(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xe0] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_df(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xdf] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_de(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xde] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_dd(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xdd] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_dc(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xdc] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x280;
}

void store_joy_and_flag_d3(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd3] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x80;
}

void store_joy_and_flag_d2(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd2] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x80;
}

void store_joy_and_flag_d1(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd1] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x80;
}

void store_joy_and_flag_d0(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd0] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x80;
}

void store_joy_and_flag_d6(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd6] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x80;
}

void store_joy_and_flag_d5(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd5] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x80;
}

void store_joy_and_flag_d4(uint32_t *object, uint8_t value)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[5];
    sub[0xd4] = value;
    *(uint16_t *)(sub + 0xe8) = *(uint16_t *)(sub + 0xe8) | 0x80;
}

uint32_t map_code_to_value(uint32_t code)
{
    if (code == 1) {
        return 0x12;
    }
    if (code == 2) {
        return 0x2b;
    }
    return 0xff;
}

void mask_cc_fields(uint32_t *object)
{
    uint16_t *a = (uint16_t *)(uintptr_t)(object[0x2c / 4] + 0xcc);
    uint16_t *b = (uint16_t *)(uintptr_t)(object[0x30 / 4] + 0xcc);
    *a = *a & 0xfffd;
    *b = *b & 0xfffd;
}

void or_cc_fields(uint32_t *object)
{
    uint16_t *a = (uint16_t *)(uintptr_t)(object[0x2c / 4] + 0xcc);
    uint16_t *b = (uint16_t *)(uintptr_t)(object[0x30 / 4] + 0xcc);
    *a = *a | 2;
    *b = *b | 2;
}

void copy_vector_200(uint32_t *object, const uint32_t *src, uint32_t extra)
{
    object[0x200 / 4] = src[0];
    object[0x204 / 4] = src[1];
    object[0x208 / 4] = src[2];
    object[0x230 / 4] = extra;
}

void clear_word_c_and_38(uint32_t *object)
{
    if (object[3] != 0) {
        object[3] = 0;
    }
    object[0x38 / 4] = 0;
}

void init_record_e_14(uint8_t *object)
{
    *(uint32_t *)(object + 4) = 0xe;
    object[0x14] = 6;
    *(uint32_t *)(object + 0x1c) = 0;
    *(uint32_t *)(object + 0x20) = 0;
}

void init_record_22_24(uint8_t *object)
{
    object[0x14] = 6;
    *(uint32_t *)(object + 0x1c) = 0;
    *(uint32_t *)(object + 4) = 0x22;
    *(uint32_t *)(object + 0x20) = 0;
    *(uint32_t *)(object + 0x24) = 0;
}

void store_two_words_108(uint8_t *object, const uint32_t *src)
{
    *(uint32_t *)(object + 0x108) = src[0];
    *(uint32_t *)(object + 0x10c) = src[1];
    object[0x116] = 0;
}

void increment_word_18(uint32_t *object)
{
    object[6] = object[6] + 1;
}

void set_byte_a28(uint32_t *object, int32_t value)
{
    *(uint8_t *)((uint8_t *)object + 0xa28) = (uint8_t)value;
    if (value == 1) {
        object[0x8c / 4] = (uint32_t)(uintptr_t)object + 0x90;
    }
}

uint32_t get_if_byte_4_is_5(const uint32_t *object)
{
    uint32_t sub = object[2];
    if (*(const uint8_t *)(uintptr_t)(sub + 4) != 5) {
        sub = 0;
    }
    return sub;
}

void set_word_a18(uint32_t *object)
{
    object[0xa18 / 4] = 0;
}

uint32_t svc_23_release_0(uint32_t *object)
{
    if (object[1] != 0) {
        object[1] = 0;
    }
    return (uint32_t)(uintptr_t)object;
}

uint32_t svc_23_release_1(uint32_t *object)
{
    if (object[0] != 0) {
        object[0] = 0;
    }
    return (uint32_t)(uintptr_t)object;
}

uint32_t svc_23_release_2(uint32_t *object)
{
    if (object[0] != 0) {
        object[0] = 0;
    }
    return (uint32_t)(uintptr_t)object;
}

uint32_t svc_23_release_3(uint32_t *object)
{
    if (object[0] != 0) {
        object[0] = 0;
    }
    return (uint32_t)(uintptr_t)object;
}

int32_t normalize_index(int32_t index)
{
    if (index < 0x20) {
        if (0x17 < index) {
            index = index - 0x18;
        }
    } else {
        index = index - 0x20;
    }
    return index;
}

void mask_byte_1ea(uint8_t *object, uint8_t value)
{
    object[0x1e9] = value;
    object[0x1ea] = object[0x1ea] & value;
}

void push_word_1c(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[7];
    object[7] = (uint32_t)(uintptr_t)(cursor + 1);
    if (cursor != NULL) {
        *cursor = value;
    }
    object[5] = object[5] + 1;
}

void set_byte_1b5_if_different(uint8_t *object, uint8_t value)
{
    if (object[0x1b5] != value) {
        object[0x1b5] = value;
        object[0x1cf] = object[0x1cf] | 2;
    }
}

float get_word_114_as_float(const uint8_t *object)
{
    return *(const float *)(object + 0x114);
}

int32_t get_byte_at_8_bounded(const uint8_t *object, uint32_t index)
{
    if (index < 0xc) {
        return *(const int8_t *)(object + index + 8);
    }
    return 0;
}

uint32_t check_byte_1508_is_2(const uint8_t *object)
{
    return object[0x1508] == 2;
}

uint32_t check_byte_1508_is_2_b(const uint8_t *object)
{
    return object[0x1508] == 2;
}

void clear_byte_2367(uint8_t *object)
{
    object[0x2367] = 0;
}

uint32_t check_byte_45b0_is_5(const uint8_t *object)
{
    return object[0x45b0] == 5;
}

uint32_t identity_word_b(uint32_t value)
{
    return value;
}

void reset_counters_30(uint32_t *object)
{
    object[0x38 / 4] = object[0x34 / 4];
    object[0x30 / 4] = 0;
    object[1] = 0;
    object[3] = object[2];
}

void push_by_mode(uint32_t *object)
{
    uint32_t *cursor;
    if (*(const uint8_t *)(uintptr_t)((uint8_t *)object + 0x5e0) != 0) {
        cursor = (uint32_t *)(uintptr_t)object[0x38 / 4];
        object[0x38 / 4] = (uint32_t)(uintptr_t)(cursor + 1);
        if (cursor != NULL) {
            *cursor = (uint32_t)(uintptr_t)object + 0x60;
        }
        object[0x30 / 4] = object[0x30 / 4] + 1;
    } else {
        cursor = (uint32_t *)(uintptr_t)object[3];
        object[3] = (uint32_t)(uintptr_t)(cursor + 1);
        if (cursor != NULL) {
            *cursor = (uint32_t)(uintptr_t)object + 0x60;
        }
        object[1] = object[1] + 1;
    }
}

void copy_vector_200_b(uint32_t *object, const uint32_t *src, uint32_t extra, uint32_t tag)
{
    object[0x200 / 4] = src[0];
    object[0x204 / 4] = src[1];
    object[0x208 / 4] = src[2];
    object[0x230 / 4] = extra;
    object[0x2d4 / 4] = tag;
}

uint32_t identity_word_c(uint32_t value)
{
    return value;
}

void push_front_node(uint32_t *head, uint32_t *node)
{
    uint32_t old = *head;
    *head = (uint32_t)(uintptr_t)node;
    node[1] = (uint32_t)(uintptr_t)head;
    node[0] = old;
    if (old != 0) {
        *(uint32_t *)(uintptr_t)(old + 4) = (uint32_t)(uintptr_t)node;
    }
}

uint32_t check_byte_1aa2_under_2(const uint8_t *object)
{
    return object[0x1aa2] < 2;
}

void increment_word_258(uint8_t *object)
{
    if (*(int32_t *)(object + 600) != 0x7fffffff) {
        *(int32_t *)(object + 600) = *(int32_t *)(object + 600) + 1;
    }
}

void init_record_0_10(uint8_t *object)
{
    object[0] = 0;
    *(uint32_t *)(object + 0x10) = 0;
    object[1] = 0;
    object[2] = 0;
    *(uint32_t *)(object + 4) = 0;
}

int32_t get_byte_11d1(const uint8_t *object)
{
    return *(const int8_t *)(object + 0x11d1);
}

uint32_t add_d4_entry(const uint32_t *object, uint32_t index)
{
    return *(const uint32_t *)(uintptr_t)(object[2] + 0xd4) + index * 0x30 + 0x90;
}

uint32_t add_word_c_indexed(const uint32_t *object, uint32_t index)
{
    return object[4] + (uint32_t)*(const uint16_t *)(uintptr_t)(object[3] + index * 2);
}

uint32_t add_word_4_by_halfword(const uint32_t *object, uint32_t index)
{
    return object[1] + (uint32_t)*(const uint16_t *)(uintptr_t)(object[3] + index * 8 + 4) * 4;
}

uint16_t get_chained_halfword_2(const uint32_t *object, uint32_t index, uint32_t sub)
{
    return *(const uint16_t *)(uintptr_t)(object[1] + (uint32_t)*(const uint16_t *)(uintptr_t)(object[4] + index * 4 + 2) * 4 + sub * 2);
}

uint32_t add_word_8_indexed(const uint32_t *object, uint32_t index)
{
    return object[2] + index * 8;
}

uint32_t get_pointed_word_0(const uint32_t *object)
{
    uint32_t result = 0;
    if (object[1] != 0) {
        result = *(const uint32_t *)(uintptr_t)(object[1] + 8);
    }
    return result;
}

uint8_t get_pointed_byte_5(const uint32_t *object)
{
    uint8_t result = 0;
    if (object[1] != 0) {
        result = *(const uint8_t *)(uintptr_t)(object[1] + 5);
    }
    return result;
}

int32_t get_pointed_halfword_6(const uint32_t *object)
{
    int32_t result = 0;
    if (object[1] != 0) {
        result = *(const int16_t *)(uintptr_t)(object[1] + 6);
    }
    return result;
}

uint32_t check_pair_18_19(const uint8_t *object)
{
    if (object[0x18] == 0xfd || object[0x19] != 3) {
        return 0;
    }
    return 1;
}

uint32_t map_to_012(uint32_t value)
{
    if (value == 0) {
        return 0;
    }
    if (value == 1) {
        return 1;
    }
    return 2;
}

uint32_t check_byte_254_is_1(const uint8_t *object)
{
    return object[0x254] == 1;
}

uint32_t check_nested_word_44(const uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(object[0x1f8 / 4] + 0x44) != 0;
}

uint32_t add_offset_1c(uint32_t object, uint32_t offset)
{
    return object + offset + 0x1c;
}

uint32_t return_ten(void)
{
    return 10;
}

uint8_t get_byte_6f_flag(const uint32_t *object)
{
    uint32_t sub = object[8];
    uint8_t value = 0;
    if (sub != 0) {
        value = *(const uint8_t *)(uintptr_t)(sub + 0x6f);
    }
    if (sub != 0 && value != 0) {
        value = 1;
    }
    return value;
}

uint32_t get_word_e4_low(const uint32_t *object)
{
    return object[0xe4 / 4] & 0xffff;
}

void noop_h(void)
{
}

void store_word_60_if_mode_1_3(uint32_t *out, const uint8_t *object)
{
    uint32_t value;
    if (object[0x58] == 1 || object[0x58] == 3) {
        value = *(const uint32_t *)(object + 0x60);
    } else {
        value = 0;
    }
    *out = value;
}

uint32_t check_mode_20_byte_55_1(const uint8_t *object)
{
    uint8_t is_mode5 = object[0x20] == 5;
    uint32_t value = (uint32_t)(uintptr_t)object;
    if (is_mode5) {
        value = object[0x55];
    }
    if (!is_mode5 || value != 1) {
        return 0;
    }
    return 1;
}

uint32_t add_word_4(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[1];
}

uint32_t add_word_4_b(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[1];
}

uint32_t get_pointed_word_0_b(const uint32_t *object)
{
    uint32_t result = 0;
    if (object[2] != 0) {
        result = **(const uint32_t **)(uintptr_t)(object[2]);
    }
    return result;
}

uint32_t get_if_halfword_4_is_300(uint16_t *object)
{
    if (object[0] == 0x300) {
        return (uint32_t)(uintptr_t)object + *(const uint32_t *)(object + 2);
    }
    return 0;
}

uint32_t add_word_34(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[0x34 / 4];
}

uint32_t get_if_halfword_4_is_101(uint32_t *object)
{
    if (*(const int16_t *)((uint8_t *)object + 4) == 0x101) {
        return (uint32_t)(uintptr_t)object + object[2];
    }
    return 0;
}

uint32_t get_if_halfword_4_is_101_b(uint32_t *object)
{
    if (*(const int16_t *)((uint8_t *)object + 4) == 0x101) {
        return (uint32_t)(uintptr_t)object + object[2];
    }
    return 0;
}

uint32_t get_if_pair_18_1c(uint32_t *object)
{
    if ((int32_t)object[7] == -1 || *(const int16_t *)((uint8_t *)object + 0x18) != 0x2210) {
        return 0;
    }
    return (uint32_t)(uintptr_t)object + object[7];
}

uint32_t get_if_halfword_0_is_220c(uint16_t *object)
{
    if (object[0] == 0 || object[0] != 0x220c) {
        return 0;
    }
    return (uint32_t)(uintptr_t)object + *(const uint32_t *)(object + 2);
}

uint32_t map_halfword_220c(uint16_t *object)
{
    uint32_t value;
    if (object[0] == 0 || (value = object[0] - 0x220c, 1 < value)) {
        value = 2;
    }
    return value;
}

uint32_t get_pointed_word_0_c(const uint8_t *object)
{
    if (object[0xc] == 0) {
        return 0;
    }
    return **(const uint32_t **)(uintptr_t)(object + 4);
}

uint32_t get_nested_68_8(const uint32_t *object)
{
    if (object[0] != 0) {
        return *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[0] + 0x68) + 8);
    }
    return 0;
}

uint32_t check_pointed_byte_4_zero(const uint32_t *object)
{
    uint32_t result = 0;
    if (object[0] != 0) {
        if (*(const uint8_t *)(uintptr_t)(object[0] + 4) == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

uint8_t get_byte_50_or_1(const uint32_t *object)
{
    if (object[0] == 0) {
        return 1;
    }
    return (uint8_t)object[0x14];
}

uint32_t check_byte_51_word_84(const uint8_t *object)
{
    if (object[0x51] != 0) {
        return 0;
    }
    if (*(const uint32_t *)(object + 0x84) != 0) {
        return 1;
    }
    return 0;
}

uint32_t get_if_word_4_is_21f(uint32_t *object)
{
    if (object[1] == 0x21f) {
        return (uint32_t)(uintptr_t)object + 8;
    }
    return 0;
}

uint32_t add_word_c(uint32_t *object)
{
    return (uint32_t)(uintptr_t)object + object[3];
}

uint32_t add_word_4_offset(const uint32_t *object, uint32_t offset)
{
    return object[1] + offset;
}

uint32_t get_indexed_entry_14(uint32_t *object, uint32_t index)
{
    uint32_t *table = object + 5;
    if (index < table[0]) {
        return (uint32_t)(uintptr_t)table + table[index * 2 + 2];
    }
    return 0;
}

uint32_t add_nested_8_16c(uint32_t *object)
{
    return object[1] + *(const uint32_t *)(uintptr_t)(object[0] + 8) * 0x16c;
}

void store_deref_offset_10(uint32_t *out, uint32_t *object, uint32_t index)
{
    *out = object[0] + *(const uint32_t *)(uintptr_t)(object[0] + 0x10 + index * 4);
    out[1] = 0;
}

uint32_t add_8_180_10(uint32_t *object, uint32_t a, uint32_t b)
{
    return object[2] + a * 0x180 + b * 0x10 + 0x54;
}

void store_8_180_18_130(uint32_t *out, uint32_t *object, uint32_t a, uint32_t b)
{
    *out = object[2] + a * 0x180 + b * 0x18 + 0x130;
}

uint32_t get_nested_8_180_17c(uint32_t *object, uint32_t a, uint32_t b)
{
    return *(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[2] + a * 0x180 + 0x17c) + b * 4);
}

uint32_t copy_4c_from_pointed(uint8_t *dest, const uint32_t *object)
{
    const uint8_t *src = (const uint8_t *)(uintptr_t)object[1];
    uint32_t i;
    for (i = 0; i < 0x4c; i++) {
        dest[i] = src[i];
    }
    return 1;
}

uint32_t check_pointed_word_68(const uint32_t *object)
{
    if (object[0] != 0) {
        return *(const uint32_t *)(uintptr_t)(object[0] + 0x68);
    }
    return 0;
}

void clear_byte_end(uint32_t *object)
{
    *(uint8_t *)(uintptr_t)(object[2] + object[1] - 1) = 0;
}

int32_t get_byte_15bc(const uint8_t *object)
{
    return *(const int8_t *)(object + 0x15bc);
}

int32_t get_byte_15b8_indexed(const uint8_t *object, uint32_t index)
{
    return *(const int8_t *)(object + (*(const int32_t *)(object + 0x15b8) - index) + 0x1597);
}

uint32_t check_31e_328(const uint8_t *object)
{
    if (object[0x31e] == 1 && object[0x328] != 6) {
        return 1;
    }
    return 0;
}

uint32_t check_315_314(const uint8_t *object)
{
    if (object[0x315] == 0 && object[0x314] != 0) {
        return 1;
    }
    return 0;
}

uint32_t map_flags_18(const uint32_t *object)
{
    uint32_t flags = *(const uint32_t *)(uintptr_t)(object[6] + 4);
    if ((flags & 1) != 0) {
        return 2;
    }
    if ((flags & 2) != 0) {
        return 1;
    }
    return 0;
}

uint8_t get_byte_6_low(const uint8_t *object)
{
    return object[6] & 0x7f;
}

uint8_t get_byte_6_high(const uint8_t *object)
{
    return object[6] & 0x80;
}

uint8_t get_byte_49f0(const uint8_t *object, uint32_t index)
{
    return object[index + 0x49f0];
}

uint32_t get_word_18_if_byte_1(const uint8_t *object)
{
    if (object[1] == 0) {
        return 0;
    }
    return *(const uint32_t *)(object + 0x18);
}

int32_t get_byte_118(const uint8_t *object)
{
    return *(const int8_t *)(object + 0x118);
}

uint32_t get_word_4(const uint32_t *object)
{
    return object[1];
}

uint16_t get_halfword_2_chained(const uint32_t *object)
{
    return *(const uint16_t *)(uintptr_t)(object[1] + 2);
}

uint16_t get_halfword_28_chained(const uint32_t *object)
{
    uint16_t result = 0;
    if (object[1] != 0) {
        result = *(const uint16_t *)(uintptr_t)(object[1] + 0x28);
    }
    return result;
}

uint32_t get_word_8_chained(const uint32_t *object)
{
    int32_t offset = *(const int32_t *)(uintptr_t)(object[1] + 8);
    if (offset < 1) {
        return 0;
    }
    return offset + object[1];
}

uint32_t get_word_c_chained(const uint32_t *object)
{
    int32_t offset = *(const int32_t *)(uintptr_t)(object[1] + 0xc);
    if (offset < 1) {
        return 0;
    }
    return offset + object[1];
}

uint32_t get_word_14_chained(const uint32_t *object)
{
    int32_t offset = *(const int32_t *)(uintptr_t)(object[1] + 0x14);
    if (offset < 1) {
        return 0;
    }
    return offset + object[1];
}

uint32_t add_38_110(const uint32_t *object, uint32_t index)
{
    return object[0x38 / 4] + index * 0x110 + 0x90;
}

int32_t get_byte_1b3c(const uint8_t *object)
{
    return *(const int8_t *)(object + 0x1b3c);
}

void clear_two_words(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
}

void fill_pair_ff(uint32_t *object, uint32_t value)
{
    uint32_t pair = (value & 0xff) | (value & 0xff) << 8;
    pair = pair | pair << 0x10;
    object[0] = pair;
    object[1] = pair;
}

void increment_word_1c_b(uint32_t *object)
{
    object[7] = object[7] + 1;
}

void push_word_1c_b(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[7];
    object[7] = (uint32_t)(uintptr_t)(cursor + 1);
    if (cursor != NULL) {
        *cursor = value;
    }
    object[5] = object[5] + 1;
}

uint32_t return_16(void)
{
    return 0x10;
}

uint32_t check_mask_18400(uint32_t value)
{
    uint32_t match = (value & 0x3fc00) == 0x18400;
    if (match) {
        value = value & 0x3ff;
    }
    return match && value == 600;
}

int32_t locked_get_byte_10(uint8_t *object)
{
    int8_t value;
    recursive_mutex_lock((uint32_t *)(object + 0x18));
    value = *(int8_t *)(object + 0x10);
    recursive_mutex_unlock((uint32_t *)(object + 0x18));
    return value;
}

int32_t locked_get_byte_11(uint8_t *object)
{
    int8_t value;
    recursive_mutex_lock((uint32_t *)(object + 0x18));
    value = *(int8_t *)(object + 0x11);
    recursive_mutex_unlock((uint32_t *)(object + 0x18));
    return value;
}

int32_t locked_get_byte_1c(uint8_t *object)
{
    int8_t value;
    recursive_mutex_lock((uint32_t *)(object + 0x28));
    value = *(int8_t *)(object + 0x1c);
    recursive_mutex_unlock((uint32_t *)(object + 0x28));
    return value;
}

int32_t locked_get_byte_14(uint8_t *object)
{
    int8_t value;
    recursive_mutex_lock((uint32_t *)(object + 0x1c));
    value = *(int8_t *)(object + 0x14);
    recursive_mutex_unlock((uint32_t *)(object + 0x1c));
    return value;
}

void reset_counters_4(uint32_t *object)
{
    object[1] = 0;
    object[3] = object[2];
}

void init_record_4_1c(uint8_t *object)
{
    *(uint32_t *)(object + 8) = 0;
    *(uint32_t *)(object + 4) = 0;
    *(uint32_t *)(object + 0xc) = 0;
    *(uint16_t *)(object + 0x1c) = 0;
}

void set_bytes_94_98(uint32_t *object, uint8_t value)
{
    if (object[0x94 / 4] != 0) {
        *(uint8_t *)(uintptr_t)(object[0x94 / 4] + 0x1b) = value;
    }
    if (object[0x98 / 4] != 0) {
        *(uint8_t *)(uintptr_t)(object[0x98 / 4] + 0x17) = value;
    }
}

void add_pointed_byte_d(uint8_t *object, uint8_t value)
{
    object[0xd] = object[0xd] + value;
}

void set_pointed_byte_17(uint8_t *object, uint8_t value)
{
    object[0x17] = value;
}

void scale_word_8c(uint8_t *object)
{
    *(float *)(object + 0x8c) = *(float *)(object + 0x8c) * 2.0f;
}

uint32_t check_word_40_is_1(const uint32_t *object)
{
    return object[0x40 / 4] == 1;
}

uint32_t get_word_40(const uint32_t *object)
{
    return object[0x40 / 4];
}

uint32_t test_byte_6c_bit(const uint8_t *object, uint32_t bit)
{
    return (object[0x6c] & (1u << (bit & 0xff))) != 0;
}

void set_word_pair(uint32_t *object, uint32_t value)
{
    object[0] = value;
    object[1] = value + *(const uint32_t *)(uintptr_t)(value + 0xc);
}

void copy_eleven_words(uint32_t *dest, const uint32_t *src)
{
    uint32_t i;
    for (i = 0; i < 9; i++) {
        dest[i] = src[i];
    }
    dest[3] = src[4];
    dest[4] = src[5];
    dest[5] = src[6];
    dest[6] = src[8];
    dest[7] = src[9];
    dest[8] = src[10];
}

uint32_t add_8_180_4(const uint32_t *object, uint32_t a, uint32_t b)
{
    return object[2] + a * 0x180 + b * 0x10 + 4;
}

void set_word_30_if_diff(uint8_t *object, float value)
{
    if (*(float *)(object + 0x30) != value) {
        *(float *)(object + 0x30) = value;
        *(uint16_t *)(object + 0x20) = *(uint16_t *)(object + 0x20) | 8;
    }
}

uint32_t get_if_halfword_10_is_101(uint32_t *object)
{
    if (*(const int16_t *)((uint8_t *)object + 0x10) == 0x101) {
        return (uint32_t)(uintptr_t)object + object[5];
    }
    return 0;
}

uint32_t clamp_to_3(uint32_t value)
{
    if (1 < value) {
        value = 3;
    }
    return value;
}

void call_add_field_4_if_set(uint32_t *object)
{
    if (*(const uint8_t *)(uintptr_t)((uint8_t *)object + 8) != 0) {
        add_field_4((uint32_t *)(uintptr_t)object[1]);
    }
}

void remove_list_entry_b(uint32_t *count, uint32_t *node)
{
    remove_list_entry(count, (uint32_t *)(uintptr_t)((uint8_t *)node + 4));
}

void insert_list_after_b(uint32_t *count, uint32_t *node)
{
    insert_list_after(count, count + 1, (uint32_t *)(uintptr_t)((uint8_t *)node + 4));
}

void set_word_50_byte_9d(uint8_t *object, uint8_t value, uint32_t word)
{
    *(uint32_t *)(object + 0x50) = word;
    object[0x9d] = value;
}

void set_byte_60_ff_if_lower(uint8_t *object, uint32_t index)
{
    if (index < 0xc && object[index + 0x60] < *(const uint16_t *)(object + 0x6c)) {
        object[index + 0x60] = 0xff;
    }
}

void set_byte_77_if_match(uint8_t *object, uint8_t value)
{
    if (object[0x74] == value) {
        object[0x77] = 1;
    }
}

void store_pair_4_8(uint32_t *object, uint32_t a, uint32_t b)
{
    object[1] = a;
    object[2] = b;
    object[0] = 0;
}

void copy_record_c(uint8_t *dest, const uint8_t *src)
{
    dest[0xc] = src[0xc];
    *(uint32_t *)(dest + 4) = *(const uint32_t *)(src + 4);
    *(uint32_t *)(dest + 8) = *(const uint32_t *)(src + 8);
}

void store_pair_80_84(uint32_t *object, const uint32_t *src)
{
    uint32_t first = src[0];
    object[0x84 / 4] = src[1];
    object[0x80 / 4] = first;
    *(uint8_t *)((uint8_t *)object + 0x88) = 1;
}

void store_pair_54_58(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0x54 / 4] = a;
    object[0x58 / 4] = b;
}

void store_pair_8_c(uint32_t *object, const uint32_t *src)
{
    uint32_t first = src[0];
    object[3] = src[1];
    object[2] = first;
    *(uint8_t *)((uint8_t *)object + 0x10) = 1;
}

void clear_record_8_10(uint8_t *object)
{
    *(uint32_t *)(object + 8) = 0;
    *(uint32_t *)(object + 0xc) = 0;
    object[0x10] = 0;
}

void store_word_4_byte_1c(uint32_t *object, uint32_t value)
{
    object[1] = value;
    *(uint8_t *)((uint8_t *)object + 0x1c) = 0;
}

void store_word_14_if_valid(uint32_t *object, uint32_t value)
{
    if (value - 0x100000 < 0x100000) {
        object[5] = value;
    }
}

void set_halfword_1e_mask(uint8_t *object, uint16_t value)
{
    *(uint16_t *)(object + 0x1e) = value & 0xfffe;
}

void set_halfword_1c(uint8_t *object, uint16_t value)
{
    *(uint16_t *)(object + 0x1c) = value;
}

void set_byte_1b7_if_diff(uint8_t *object, uint8_t value)
{
    if (object[0x1b7] != value) {
        object[0x1b7] = value;
        object[0x1cf] = object[0x1cf] | 2;
    }
}

void init_record_1c_28(uint8_t *object)
{
    object[0x14] = 6;
    *(uint32_t *)(object + 0x1c) = 0;
    *(uint32_t *)(object + 0x28) = 0;
    *(uint32_t *)(object + 0x24) = 0;
    *(uint32_t *)(object + 4) = 10;
}

void init_record_90(uint8_t *object)
{
    *(uint32_t *)(object + 0x90) = 0;
}

uint32_t check_word_4_nonzero(const uint32_t *object)
{
    return object[1] != 0;
}

uint32_t check_byte_8_is_0_or_7(const uint8_t *object)
{
    return object[8] == 0 || object[8] == 7;
}

uint32_t check_byte_28_is_0_or_8(const uint8_t *object)
{
    return object[0x28] == 0 || object[0x28] == 8;
}

void copy_or_clear_80(uint8_t *object, const uint8_t *src)
{
    if (src != NULL) {
        *(uint32_t *)(object + 0x80) = *(const uint32_t *)(src + 0x80);
        *(uint16_t *)(object + 0x84) = *(const uint16_t *)(src + 0x84);
    } else {
        *(uint32_t *)(object + 0x80) = 0;
        *(uint16_t *)(object + 0x84) = 0;
    }
}

void push_word_fa8(uint32_t *object, uint32_t value)
{
    uint32_t *count = (uint32_t *)((uint8_t *)object + 0xfa8);
    count[count[0] + 1] = value;
    count[0] = count[0] + 1;
}

void set_byte_d6_bit(uint8_t *object, uint32_t bit)
{
    object[0xd6] = (1u << (bit & 0xff)) | object[0xd6];
}

int32_t get_byte_cff_if_cfe(const uint8_t *object)
{
    if (object[0xcfe] == 0) {
        return 0;
    }
    return *(const int8_t *)(object + 0xcff);
}

uint32_t check_1ff_1a4(const uint8_t *object)
{
    uint8_t is_mode2 = object[0x1ff] == 2;
    uint32_t value = (uint32_t)(uintptr_t)object;
    if (is_mode2) {
        value = object[0x1a4];
    }
    return is_mode2 && value == 2;
}

uint32_t check_1ff_178(const uint8_t *object)
{
    uint8_t is_mode1 = object[0x1ff] == 1;
    uint32_t value = (uint32_t)(uintptr_t)object;
    if (is_mode1) {
        value = object[0x178];
    }
    return is_mode1 && value == 2;
}

void clear_byte_202(uint8_t *object)
{
    object[0x202] = 0;
}

void add_158_15c(uint32_t *object)
{
    object[0x158 / 4] = object[0x158 / 4] + object[0x15c / 4];
}

void or_byte_9894(uint8_t *object)
{
    object[0x9894] = object[0x9894] | 2;
}

void store_four_halfwords_114(uint8_t *object, uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
    *(uint16_t *)(object + 0x114) = a;
    *(uint16_t *)(object + 0x116) = b;
    *(uint16_t *)(object + 0x118) = c;
    *(uint16_t *)(object + 0x11a) = d;
}

void toggle_byte_5e8(uint8_t *object)
{
    object[0x5e8] = object[0x5e8] == 0;
}

void store_pair_594_1720(uint32_t *object, uint32_t a, uint32_t b)
{
    object[0x594 / 4] = a;
    object[0x1720 / 4] = b;
}

uint32_t set_state_2_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 2;
    }
    return 1;
}

uint32_t set_state_10_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 10;
    }
    return 1;
}

uint32_t set_state_2_if_flag_b(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 2;
    }
    return 1;
}

void or_byte_3eff_set_3f05_4(uint8_t *object)
{
    object[0x3eff] = object[0x3eff] | 1;
    object[0x3f05] = 4;
}

void and_byte_3eff_set_3f05_2(uint8_t *object)
{
    object[0x3eff] = object[0x3eff] & 0xfe;
    object[0x3f05] = 2;
}

void or_byte_3eff_2_set_3f05_4(uint8_t *object)
{
    object[0x3eff] = object[0x3eff] | 2;
    object[0x3f05] = 4;
}

void and_byte_3eff_fd_set_3f05_2(uint8_t *object)
{
    object[0x3eff] = object[0x3eff] & 0xfd;
    object[0x3f05] = 2;
}

void store_word_4(uint32_t *object, uint32_t value)
{
    object[1] = value;
}

void store_word_4_b(uint32_t *object, uint32_t value)
{
    object[1] = value;
}

void store_word_4_c(uint32_t *object, uint32_t value)
{
    object[1] = value;
}

void reset_record_10(uint8_t *object)
{
    *(uint32_t *)(object + 0xc) = 0;
    object[0x16] = 0;
    *(uint16_t *)(object + 0x12) = 0;
    *(uint16_t *)(object + 0x10) = 0;
    *(uint32_t *)(object + 8) = *(const uint32_t *)(object + 4);
}

void store_word_1_word_2_len(uint32_t *object, const uint16_t *string)
{
    object[0] = 0;
    object[1] = (uint32_t)(uintptr_t)string;
    object[2] = wide_string_length(string) << 1;
}

uint32_t count_bits_and_index(const uint32_t *table, uint32_t *out, uint32_t slot)
{
    uint8_t found = 0;
    int32_t count = 0;
    int32_t i;
    if (slot != 0xffffffff) {
        uint32_t bit = 0;
        i = slot + 1;
        do {
            if ((*table & (1u << bit)) != 0) {
                count = count + 1;
                if (bit == slot) {
                    found = 1;
                }
            }
            i = i - 1;
            bit = bit + 1;
        } while (i != 0);
        if (!found) {
            return 0;
        }
    }
    if (count == 0) {
        return 0;
    }
    *out = table[count];
    return 1;
}

uint32_t set_state_5_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 5;
    }
    return 1;
}

uint32_t set_state_15_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 0xf;
    }
    return 1;
}

void split_four_words(const uint32_t *object, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
    *a = object[0];
    *b = object[1];
    *c = object[2];
    *d = object[3];
}

uint32_t get_config_byte_14_1(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 1) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_byte_14_2(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 2) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_byte_14_0(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 0) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_word_14_2(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 2) == 0) {
        return 0;
    }
    return (local[0] & 0xffffff) >> 0x10;
}

uint32_t get_config_word_14_2_high(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 2) == 0) {
        return 0;
    }
    return (local[0] & 0xffff) >> 8;
}

int32_t get_config_signed_byte_14_0(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 0) == 0) {
        return 0;
    }
    return (int32_t)(int8_t)(local[0] >> 8);
}

uint32_t get_config_byte_4_0(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 0) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_byte_4_2(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 2) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_byte_4_1_60(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 1) == 0) {
        return 0x60;
    }
    return local[0] & 0xff;
}

uint32_t get_config_word_4_1(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 1) == 0) {
        return 0;
    }
    return local[0];
}

uint32_t get_config_byte_8_0(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 8), local, 0) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_word_8_1(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 8), local, 1) == 0) {
        return 0;
    }
    return local[0];
}

uint32_t get_config_word_c_0(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0xc), local, 0) == 0) {
        return 0;
    }
    return local[0];
}

uint32_t get_config_byte_c_1(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0xc), local, 1) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_word_18_2(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x18), local, 2) == 0) {
        return 0;
    }
    return local[0];
}

uint32_t get_config_word_18_1(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x18), local, 1) == 0) {
        return 0;
    }
    return local[0];
}

uint32_t get_config_byte_18_0(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x18), local, 0) == 0) {
        return 1;
    }
    return local[0] & 0xff;
}

uint32_t get_config_offset_14_8(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 8) == 0) {
        return 0;
    }
    return local[0] + (uint32_t)(uintptr_t)object;
}

uint32_t get_config_byte_4_0_3c(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 0) == 0) {
        return 0x3c;
    }
    return local[0] & 0xff;
}

uint32_t get_config_byte_4_2_b(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 2) == 0) {
        return 0x40;
    }
    return local[0] & 0xff;
}

uint32_t get_config_byte_4_1_7f(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 1) == 0) {
        return 0x7f;
    }
    return local[0] & 0xff;
}

uint32_t get_config_byte_14_1_or_0(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 1) == 0) {
        return 0;
    }
    return local[0] & 0xff;
}

uint32_t get_config_word_14_1_high(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 1) == 0) {
        return 0;
    }
    return (local[0] & 0xffff) >> 8;
}

uint32_t get_config_bit_14_17(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 0x11) == 0) {
        return 0;
    }
    return local[0] & 1;
}

uint32_t get_config_word_14_2_high_b(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 0x14), local, 2) == 0) {
        return 0;
    }
    return (local[0] & 0xffff) >> 8;
}

uint32_t get_config_word_4_2_high(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 2) == 0) {
        return 0;
    }
    return (local[0] & 0xffff) >> 8;
}

uint32_t get_config_word_8_0_high(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 8), local, 0) == 0) {
        return 0;
    }
    return (local[0] & 0xffff) >> 8;
}

uint32_t get_config_word_4_4_high(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 4) == 0) {
        return 0;
    }
    return (local[0] & 0xffff) >> 8;
}

uint32_t get_config_flag_4_4(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 4) == 0) {
        return 0;
    }
    return (local[0] & 0xff) != 0;
}

uint32_t get_config_top_byte_4_4(uint32_t *object, uint32_t value)
{
    uint32_t local[1];
    local[0] = value;
    if (count_bits_and_index((uint32_t *)(uintptr_t)((uint8_t *)object + 4), local, 4) == 0) {
        return 0;
    }
    return (local[0] & 0xffffff) >> 0x10;
}

void clear_if_byte_8(uint32_t *object)
{
    if (*(const uint8_t *)(uintptr_t)((uint8_t *)object + 8) != 0) {
        object[0] = 0;
        object[1] = 0;
        *(uint8_t *)(uintptr_t)((uint8_t *)object + 8) = 0;
    }
}

void clear_if_byte_c(uint32_t *object)
{
    if (*(const uint8_t *)(uintptr_t)((uint8_t *)object + 0xc) != 0) {
        object[0] = 0;
        object[1] = 0;
        object[2] = 0;
        *(uint8_t *)(uintptr_t)((uint8_t *)object + 0xc) = 0;
    }
}

void clear_two_words_b(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
}

void init_record_4_14(uint32_t *object, uint32_t a, uint32_t b)
{
    *(uint8_t *)(uintptr_t)((uint8_t *)object + 4) = 0;
    object[3] = 0;
    object[5] = a;
    object[4] = 0;
    object[0] = 0;
    object[6] = b;
    object[7] = 0;
}

void set_word_38_if_diff(uint8_t *object, float value)
{
    if (*(float *)(object + 0x38) != value) {
        *(float *)(object + 0x38) = value;
        *(uint16_t *)(object + 0x20) = *(uint16_t *)(object + 0x20) | 0x10;
    }
}

void set_word_34_if_diff(uint8_t *object, float value)
{
    if (*(float *)(object + 0x34) != value) {
        *(float *)(object + 0x34) = value;
        *(uint16_t *)(object + 0x20) = *(uint16_t *)(object + 0x20) | 8;
    }
}

void set_word_28_if_diff(uint8_t *object, float value)
{
    if (*(float *)(object + 0x28) != value) {
        *(float *)(object + 0x28) = value;
        *(uint16_t *)(object + 0x20) = *(uint16_t *)(object + 0x20) | 4;
    }
}

void store_word_108_byte_fe(uint8_t *object, uint32_t word, uint8_t value)
{
    *(uint32_t *)(object + 0x108) = word;
    object[0xfe] = value;
}

void store_word_28_byte_2c(uint8_t *object, uint32_t word, uint8_t value)
{
    *(uint32_t *)(object + 0x28) = word;
    object[0x2c] = value;
}

void store_word_indexed_38(uint32_t *object, uint32_t index, uint32_t value)
{
    object[index + 0x38 / 4] = value;
}

uint32_t get_indexed_word_94(const uint32_t *object, uint32_t index)
{
    if (index < 0x10) {
        return object[index + 0x94 / 4];
    }
    return 0;
}

void set_halfword_d4(uint8_t *object, uint32_t index, uint16_t value)
{
    *(uint16_t *)(object + index * 2 + 0xd4) = value;
}

uint32_t set_state_7_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 7;
    }
    return 1;
}

uint32_t set_state_1_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 1;
    }
    return 1;
}

uint32_t set_state_0_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 0;
    }
    return 1;
}

uint32_t set_state_3_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 3;
    }
    return 1;
}

uint32_t set_state_4_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 4;
    }
    return 1;
}

uint32_t set_state_6_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 6;
    }
    return 1;
}

uint32_t set_state_8_if_flag(uint8_t *object)
{
    if ((*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xbd8) & 1) != 0) {
        *(uint16_t *)(object + 0xc) = 8;
    }
    return 1;
}


uint32_t get_nested_b08_word(const uint32_t *object)
{
    if (object[0] != 0) {
        return *(const uint32_t *)(uintptr_t)(object[0] + 0xb08);
    }
    return 0;
}

void set_nested_f7_f8(uint8_t *object, uint8_t value, int32_t mode)
{
    if (mode == 0) {
        mode = 4;
    }
    *(uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 0xb08) + 0xf7) = value;
    *(uint8_t *)(uintptr_t)(*(const uint32_t *)(object + 0xb08) + 0xf8) = (uint8_t)mode;
}

void and_nested_b08_word_48(uint32_t *object)
{
    uint32_t *tab = (uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[1] + 0xb08));
    tab[0x48 / 4] = tab[0x48 / 4] & 0xffff5fff;
}

uint32_t check_nested_b08_halfword_96(const uint32_t *object)
{
    return *(const int16_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[1] + 0xb08) + 0x96) == 0;
}

uint32_t set_state_1_if_nested_f3_zero(uint8_t *object)
{
    if (*(const uint8_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(*(const uint32_t *)(object + 4) + 0xb08) + 0xf3) == 0) {
        *(uint16_t *)(object + 0xc) = 1;
    }
    return 1;
}



uint32_t find_tagged_entry(uint8_t *object, uint32_t tag)
{
    uint32_t count = *(const uint16_t *)(object + 0x10);
    uint32_t i;
    if (count == 0) {
        return 0;
    }
    i = count & 1;
    if (i != 0) {
        if (*(const uint16_t *)(object + 0x14) == tag) {
            return (uint32_t)(uintptr_t)(object + 0x14);
        }
    }
    while (i < count) {
        if (*(const uint16_t *)(object + i * 0xc + 0x14) == tag) {
            return (uint32_t)(uintptr_t)(object + i * 0xc + 0x14);
        }
        if (*(const uint16_t *)(object + i * 0xc + 0x20) == tag) {
            return (uint32_t)(uintptr_t)(object + i * 0xc + 0x20);
        }
        i = i + 2;
    }
    return 0;
}

void store_8_180_18_e4(uint32_t *out, uint32_t *object, uint32_t a, uint32_t b)
{
    *out = object[2] + a * 0x180 + b * 0x18 + 0xe4;
}

void store_nested_8_180_18_f8(uint32_t *object, uint32_t a, uint32_t b, uint32_t *out)
{
    *out = *(const uint32_t *)(uintptr_t)(object[2] + a * 0x180 + b * 0x18 + 0xf8);
}

int32_t get_nested_90_8_4(uint32_t object)
{
    return *(const int8_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object + 0x90) + 8) + 4);
}

uint32_t get_if_halfword_8_is_101(uint32_t *object)
{
    if (*(const int16_t *)((uint8_t *)object + 8) == 0x101) {
        return (uint32_t)(uintptr_t)object + object[3];
    }
    return 0;
}

uint32_t check_tag_4001_exists(uint32_t *object)
{
    return find_tagged_entry((uint8_t *)(uintptr_t)object, 0x4001) != 0;
}

uint32_t check_tag_4003_exists(uint32_t *object)
{
    return find_tagged_entry((uint8_t *)(uintptr_t)object, 0x4003) != 0;
}

uint32_t get_tag_4000_word_8(uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(find_tagged_entry((uint8_t *)(uintptr_t)object, 0x4000) + 8);
}

uint32_t get_tag_4002_word_4(uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(find_tagged_entry((uint8_t *)(uintptr_t)object, 0x4002) + 4);
}

uint32_t get_tag_4000_word_4(uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(find_tagged_entry((uint8_t *)(uintptr_t)object, 0x4000) + 4);
}

uint32_t get_tag_4001_word_4(uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(find_tagged_entry((uint8_t *)(uintptr_t)object, 0x4001) + 4);
}

uint32_t get_tag_4003_word_4(uint32_t *object)
{
    return *(const uint32_t *)(uintptr_t)(find_tagged_entry((uint8_t *)(uintptr_t)object, 0x4003) + 4);
}

uint32_t abs_diff_within_wrap(int32_t a, int32_t b, int32_t limit)
{
    int32_t diff = a - b;
    if (diff < 0) {
        diff = -diff;
    }
    if (0x8000 < diff) {
        diff = 0x10000 - diff;
    }
    return diff <= limit;
}

uint32_t set_state_3_if_halfword_e_is_2(uint8_t *object)
{
    if (*(const int16_t *)(object + 0xe) == 2) {
        *(uint16_t *)(object + 0xc) = 3;
        return 1;
    }
    return 0;
}

void set_halfword_41e_4(uint8_t *object)
{
    *(uint16_t *)(object + 0x41e) = 4;
}

uint32_t set_state_2_if_halfword_e_not_2(uint8_t *object)
{
    if (*(const int16_t *)(object + 0xe) != 2) {
        *(uint16_t *)(object + 0xc) = 2;
        return 1;
    }
    return 0;
}

void set_word_24_flag_2b(uint32_t *object, uint32_t value)
{
    object[0x24 / 4] = value;
    *(uint8_t *)((uint8_t *)object + 0x2b) = value != 0;
}

uint32_t check_halfword_e_is_2(const uint8_t *object)
{
    return *(const int16_t *)(object + 0xe) == 2;
}

void init_record_70(uint8_t *object)
{
    object[0x71] = 0;
    object[0x72] = 0;
    object[0x70] = 0;
    object[0x73] = 0;
    *(uint32_t *)(object + 0x78) = 0;
    object[0x75] = 0;
}

void copy_pair_b08(uint32_t *dest, const uint8_t *src)
{
    dest[0] = *(const uint32_t *)(src + 0xb08);
    dest[1] = *(const uint32_t *)(src + 0xb0c);
}

uint32_t get_nested_c48_14(const uint32_t *object)
{
    return **(const uint32_t **)(uintptr_t)(object[0xc48 / 4] + 0x14);
}

void store_word_254_pair(uint32_t *object, const uint32_t *value)
{
    *(uint32_t *)(uintptr_t)(object[4] + 0x254) = value[0];
    *(uint32_t *)(uintptr_t)(object[6] + 0x254) = value[0];
}

void advance_and_mark_179(uint8_t *object)
{
    object[0x179] = 1;
    advance_byte_by_two(object + 0x17c);
    object[0x1c5] = object[0x1c4] + 2;
}

uint32_t get_nested_3c_34_deref(uint32_t *object)
{
    uint32_t addr = add_word_34((uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[1] + 0x3c)));
    return *(const uint32_t *)(uintptr_t)addr;
}

uint32_t get_nested_word_4_plus_4(uint32_t *object)
{
    uint32_t value = get_nested_3c_34_deref(object);
    return value * 4 + 4;
}

uint32_t get_word_14c_as_float(const uint8_t *object)
{
    return *(const uint32_t *)(object + 0x14c);
}

uint32_t check_149_150(const uint8_t *object)
{
    uint8_t has_flag = object[0x149] != 0;
    uint32_t value = (uint32_t)(uintptr_t)object + 0x100;
    if (has_flag) {
        value = object[0x150];
    }
    return has_flag && value != 0;
}

int32_t get_byte_121(const uint8_t *object)
{
    return *(const int8_t *)(object + 0x121);
}

uint32_t add_word_c_indexed_b(const uint32_t *object, uint32_t index)
{
    return object[3] + index * 8;
}

uint32_t get_indexed_byte_5e8_word_5a8(const uint8_t *object)
{
    return *(const uint32_t *)(object + object[0x5e8] * 4 + 0x5a8);
}

uint32_t check_pointed_byte_8c_bit0(const uint32_t *object)
{
    if (object[0] != 0) {
        return *(const uint8_t *)(uintptr_t)(object[0] + 0x8c) & 1;
    }
    return 0;
}

uint32_t get_nested_3c_2c_deref(uint32_t *object)
{
    uint32_t addr = add_field_2c((uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[1] + 0x3c)));
    return *(const uint32_t *)(uintptr_t)addr;
}

uint32_t get_nested_3c_1c_deref(uint32_t *object)
{
    uint32_t addr = add_field_1c((uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[1] + 0x3c)));
    return *(const uint32_t *)(uintptr_t)addr;
}

void raise_float_to_min(float *value, float input)
{
    if (input < *value) {
        input = *value;
    }
    *value = input;
}

void lower_float_to_max(float *value, float input)
{
    if (*value <= input) {
        input = *value;
    }
    *value = input;
}

uint32_t test_high_bit(const uint32_t *object, uint32_t bit)
{
    return object[bit >> 5] & (0x80000000u >> (bit & 0x1f));
}

void noop_i(void)
{
}

void noop_j(void)
{
}

void store_word_138_indexed(uint32_t *object, uint32_t index, uint32_t value)
{
    object[index + 0x138 / 4] = value;
}

void store_word_130_indexed(uint32_t *object, uint32_t index, uint32_t value)
{
    object[index + 0x130 / 4] = value;
}

int32_t find_char_from(const char *string, char target)
{
    const char *cursor;
    string = string - 1;
    do {
        cursor = string + 1;
        string = string + 1;
        if (target == *cursor) {
            return (int32_t)(intptr_t)string;
        }
    } while (*cursor != '\0');
    return 0;
}

uint16_t get_pointed_halfword_word(const uint32_t *object)
{
    return *(const uint16_t *)(uintptr_t)object[1];
}

void store_triple_a4_mark_b0(uint8_t *object, uint32_t a, uint32_t b, uint32_t c)
{
    *(uint32_t *)(object + 0xa4) = a;
    *(uint32_t *)(object + 0xa8) = b;
    *(uint32_t *)(object + 0xac) = c;
    object[0xb0] = 1;
}

uint32_t append_list_tail_170(uint32_t *object, uint32_t *node)
{
    uint32_t *tail = (uint32_t *)(uintptr_t)object[0x170 / 4];
    if (tail == NULL) {
        object[0x16c / 4] = (uint32_t)(uintptr_t)node;
    } else {
        *tail = (uint32_t)(uintptr_t)node;
    }
    object[0x170 / 4] = (uint32_t)(uintptr_t)node;
    *node = 0;
    return object[0x174 / 4];
}

uint32_t check_entry_20_empty(uint32_t *object, uint32_t index)
{
    uint8_t *entry = (uint8_t *)(uintptr_t)((uint32_t)(uintptr_t)object + index * 0x20);
    uint8_t occupied = *(const uint32_t *)(entry + 4) != 0;
    uint32_t value = (uint32_t)(uintptr_t)entry;
    if (occupied) {
        value = entry[0x20];
    }
    return !occupied || value == 0;
}

uint32_t check_byte_14_in_set(const uint8_t *object)
{
    uint8_t value = object[0x14];
    if (value == 0 || value == 8 || value == 9 || value == 0x13) {
        return 1;
    }
    return 0;
}

uint32_t check_byte_14_is_b(const uint8_t *object)
{
    return object[0x14] == 0xb;
}

void set_byte_150b_if_1508_is_2(uint8_t *object)
{
    if (object[0x1508] == 2) {
        object[0x150b] = 1;
    }
}

void set_byte_150a_if_1508_is_2(uint8_t *object)
{
    if (object[0x1508] == 2) {
        object[0x150a] = 1;
    }
}

void set_halfword_4_bit(uint8_t *object, uint32_t bit, uint32_t value)
{
    uint16_t mask = (uint16_t)(1u << (bit & 0xff));
    uint16_t current;
    if (value == 0) {
        current = *(uint16_t *)(object + 4) & (uint16_t)~mask;
    } else {
        current = mask | *(uint16_t *)(object + 4);
    }
    *(uint16_t *)(object + 4) = current;
}

uint32_t get_nested_byte_e8_high(const uint32_t *object)
{
    uint32_t result = 0;
    if (object[2] != 0) {
        result = (*(const uint8_t *)(uintptr_t)(object[2] + 0xe8) & 0x1f) >> 4;
    }
    return result;
}

uint32_t set_state_2_if_word_10_high(uint8_t *object)
{
    if (0x43160000 <= *(const int32_t *)(object + 0x10)) {
        *(uint16_t *)(object + 0xc) = 2;
    }
    return 1;
}

void move_word_8_to_c(uint32_t *object)
{
    uint32_t value = object[2];
    object[2] = 0;
    object[3] = value;
}

uint32_t copy_byte_1_halfword_2(uint8_t *object)
{
    const uint8_t *src = (const uint8_t *)(uintptr_t)*(const uint32_t *)(object + 4);
    object[10] = src[1];
    *(uint16_t *)(object + 0xe) = *(const uint16_t *)(src + 2);
    return 1;
}

uint32_t copy_triple_from_pointed(uint8_t *object)
{
    const uint8_t *src = (const uint8_t *)(uintptr_t)*(const uint32_t *)(object + 4);
    object[10] = src[1];
    *(uint16_t *)(object + 0xe) = *(const uint16_t *)(src + 2);
    *(uint32_t *)(object + 0x14) = *(const uint32_t *)(src + 0xc);
    return 1;
}

void clear_pointed_pair_26c(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[3];
    sub[0x26c / 4] = 0;
    sub[0x270 / 4] = 0;
}

void clear_word_4_only(uint32_t *object)
{
    object[1] = 0;
}

void set_byte_ea_recursive(uint32_t *object, uint8_t value, uint32_t recurse)
{
    *(uint8_t *)(uintptr_t)((uint8_t *)object + 0xea) = value;
    if (recurse == 0) {
        return;
    }
    uint32_t i = 0;
    if (object[6] != 0) {
        do {
            set_byte_ea_recursive((uint32_t *)(uintptr_t)(*(const uint32_t *)(uintptr_t)(object[8] + i * 4)), value, recurse);
            i = i + 1;
        } while (i < object[6]);
    }
}

void copy_sixteen_words(uint32_t *dest, const uint32_t *src)
{
    uint32_t i;
    for (i = 0; i < 16; i++) {
        dest[i] = src[i];
    }
}

void copy_sixteen_words_b(uint32_t *dest, const uint32_t *src)
{
    uint32_t i;
    for (i = 0; i < 16; i++) {
        dest[i] = src[i];
    }
}

void call_each(uint32_t base, uint32_t size, void (*fn)(uint32_t), uint32_t count)
{
    uint32_t current = base;
    if (fn != NULL) {
        while (count != 0) {
            fn(current);
            current = current + size;
            count = count - 1;
        }
    }
}

void svc_17_store(uint32_t *object, uint32_t value)
{
    *object = value;
}

uint32_t swap_byte(uint8_t value)
{
    static uint8_t dat_byte;
    uint8_t old = dat_byte;
    dat_byte = value;
    return old;
}

uint32_t check_word_18_mask_7_zero(void)
{
    static uint32_t dat_storage[7];
    return (dat_storage[6] & 7) == 0;
}

uint32_t get_word_18_mask_7(void)
{
    static uint32_t dat_storage[7];
    return dat_storage[6] & 7;
}

uint32_t return_word_10(void)
{
    static uint32_t dat_storage[5];
    return dat_storage[4];
}

uint32_t return_word_14(void)
{
    static uint32_t dat_storage[6];
    return dat_storage[5];
}

uint32_t return_word_18(void)
{
    static uint32_t dat_storage[7];
    return dat_storage[6];
}

uint32_t return_word_c(void)
{
    static uint32_t dat_storage[4];
    return dat_storage[3];
}

void set_byte_6(uint8_t value)
{
    static uint8_t dat_storage[7];
    dat_storage[6] = value;
    (void)dat_storage;
}

void set_byte_5(uint8_t value)
{
    static uint8_t dat_storage[6];
    dat_storage[5] = value;
    (void)dat_storage;
}

void set_1e_low2(uint32_t *object, uint16_t value)
{
    uint16_t *target = (uint16_t *)(uintptr_t)(object[0x68 / 4] + 0x1e);
    *target = (value & 3) | (*target & 0xfffc);
}

void set_1e_mid2(uint32_t *object, uint16_t value)
{
    uint16_t *target = (uint16_t *)(uintptr_t)(object[0x68 / 4] + 0x1e);
    *target = ((value & 3) << 2) | (*target & 0xfff3);
}

void set_1e_high4(uint32_t *object, int16_t value)
{
    uint16_t *target = (uint16_t *)(uintptr_t)(object[0x68 / 4] + 0x1e);
    *target = (*target & 0xffef) | (uint16_t)value << 4;
}

void set_byte_5_and_nested(uint32_t *object, uint8_t value)
{
    *(uint8_t *)((uint8_t *)object + 5) = value;
    uint8_t *sub = (uint8_t *)(uintptr_t)object[0x68 / 4];
    sub[0xe] = value;
    *(uint16_t *)(sub + 0x6c) = *(uint16_t *)(sub + 0x6c) | 0x20;
}

void set_1e_bit6(uint32_t *object, int16_t value)
{
    uint16_t *target = (uint16_t *)(uintptr_t)(object[0x68 / 4] + 0x1e);
    *target = (*target & 0xffbf) | (uint16_t)value << 6;
}

void init_state_18(uint32_t *object)
{
    object[0x18 / 4] = 0;
    object[0x1c / 4] = 0;
    object[0x20 / 4] = 0;
    object[0x24 / 4] = 0x3f800000;
    *(uint8_t *)((uint8_t *)object + 0x28) = 1;
    *(uint8_t *)((uint8_t *)object + 0x29) = 0;
}

void clamp_float_min_c8(uint32_t *object, float value)
{
    float min = 0.0f;
    if (value < min) value = min;
    *(float *)(object + 200 / 4) = value;
}

void set_float_scaled(uint8_t *object, float value)
{
    float scale = 0.0f;
    *object = 0;
    *(float *)(object + 4) = value * scale;
}

void init_state_10_1c(uint32_t *object)
{
    object[0x14 / 4] = 0;
    object[0x18 / 4] = 0;
    object[0x10 / 4] = 0;
    *(uint8_t *)((uint8_t *)object + 0x1c) = 0;
    *(uint8_t *)((uint8_t *)object + 0x1d) = 0;
}

void clear_bit_6c(uint32_t *object, uint32_t bit)
{
    if (bit < 4) {
        *(uint8_t *)((uint8_t *)object + 0x6c) &= (uint8_t)~(1u << (bit & 0xff));
    }
}

void set_indexed_halfword_130(uint32_t *object, int32_t idx1, int32_t idx2, uint16_t value)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[8 / 4];
    *(uint16_t *)((uint8_t *)sub + idx1 * 0x180 + idx2 * 0x18 + 0x130) = value;
}

void set_indexed_word_f8(uint32_t *object, int32_t idx1, int32_t idx2, const uint32_t *value)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[8 / 4];
    *(uint32_t *)((uint8_t *)sub + idx1 * 0x180 + idx2 * 0x18 + 0xf8) = *value;
}

void set_state_168(uint32_t *object, uint32_t a, uint8_t b)
{
    object[0x168 / 4] = a;
    object[0x170 / 4] = 0;
    object[0x16c / 4] = 0;
    *(uint8_t *)((uint8_t *)object + 0x13b) = b;
}

void set_state_154(uint32_t *object, uint32_t a, uint8_t b)
{
    object[0x154 / 4] = a;
    *(uint8_t *)((uint8_t *)object + 0x13e) = b;
}

void set_state_118(uint32_t *object, uint32_t a, uint8_t b)
{
    object[0x118 / 4] = a;
    *(uint8_t *)((uint8_t *)object + 0x11c) = b;
}

void copy_quad_58(uint32_t *object, uint32_t *dest)
{
    dest[0] = object[0x58 / 4];
    dest[1] = object[0x5c / 4];
    dest[2] = object[0x60 / 4];
    dest[3] = object[0x64 / 4];
}

void set_word_14_6c(uint32_t *object, uint32_t value)
{
    object[0x14 / 4] = value;
    object[0x6c / 4] = value;
}

uint32_t *get_nested_90_1c_indexed(uint32_t *object, int32_t index)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0x90 / 4];
    return (uint32_t *)((uint8_t *)sub + 0x1c + index * 0x30);
}

uint32_t get_nested_table_word_8(uint32_t *object, int32_t index)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0];
    return *(uint32_t *)((uint8_t *)sub + index * 0x18 + 8);
}

uint32_t get_table_word_4(int32_t index)
{
    static const uint32_t table[8] = {0};
    return table[index * 4 + 1];
}

uint32_t get_table_word_4_b(int32_t index)
{
    static const uint32_t table[4] = {0};
    return table[index * 2 + 1];
}

uint32_t get_word_1f18_indexed(uint32_t *object, int32_t index)
{
    return object[(index * 0x1c + 0x1f18) / 4];
}

uint32_t *add_804(uint32_t *object)
{
    return (uint32_t *)((uint8_t *)object + 0x804);
}

void init_pair_4_8(uint32_t *object)
{
    object[4 / 4] = 0;
    *(uint8_t *)((uint8_t *)object + 8) = 0;
}

uint32_t clear_nested_c0_halfword_c(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0xc0 / 4];
    *(uint16_t *)((uint8_t *)sub + 0xc) = 0;
    return 1;
}

uint32_t clear_nested_c4_halfword_c(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0xc4 / 4];
    *(uint16_t *)((uint8_t *)sub + 0xc) = 0;
    return 1;
}

void insert_list_head(uint32_t *object, uint32_t *node)
{
    uint32_t *next = (uint32_t *)(uintptr_t)object[4 / 4];
    object[4 / 4] = (uint32_t)(uintptr_t)node;
    node[0] = (uint32_t)(uintptr_t)object;
    node[1] = (uint32_t)(uintptr_t)next;
    if (next) next[0] = (uint32_t)(uintptr_t)node;
}

void set_halfword_c_to_7(uint32_t *object)
{
    if (*(int16_t *)((uint8_t *)object + 0xe) != 7) {
        *(uint16_t *)((uint8_t *)object + 0xc) = 7;
    }
}

uint32_t set_halfword_c_to_4_if_greater(uint32_t *object, uint32_t threshold)
{
    if ((int32_t)threshold < (int32_t)object[0x10 / 4]) {
        *(uint16_t *)((uint8_t *)object + 0xc) = 4;
    }
    return 1;
}

void set_word_10_to_dat(uint32_t value)
{
    static uint32_t dat_storage[5];
    dat_storage[0x10 / 4] = value;
    (void)dat_storage;
}

void clear_byte_5c_if_9c4(uint8_t *object)
{
    if (*(char *)(object + 0x9c4) == '\0') {
        *(uint8_t *)(object + 0x5c) = 0;
    }
}

void init_triple_0_1_2(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
    object[2] = 0;
}

void set_byte_1d08_if_zero(uint8_t *object)
{
    if (*(char *)(object + 0x1d08) == '\0') {
        *(uint8_t *)(object + 0x1d08) = 1;
    }
}

void push_tagged_818_1(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[0x818 / 4];
    object[0x818 / 4] = (uint32_t)(uintptr_t)(cursor + 2);
    if (cursor) {
        cursor[0] = value;
        cursor[1] = 1;
    }
    object[0x810 / 4] = object[0x810 / 4] + 1;
}

void push_tagged_818_0(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[0x818 / 4];
    object[0x818 / 4] = (uint32_t)(uintptr_t)(cursor + 2);
    if (cursor) {
        cursor[0] = value;
        cursor[1] = 0;
    }
    object[0x810 / 4] = object[0x810 / 4] + 1;
}

void push_tagged_c_1(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[0xc / 4];
    object[0xc / 4] = (uint32_t)(uintptr_t)(cursor + 2);
    if (cursor) {
        cursor[0] = value;
        cursor[1] = 1;
    }
    object[4 / 4] = object[4 / 4] + 1;
}

void push_tagged_c_2(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[0xc / 4];
    object[0xc / 4] = (uint32_t)(uintptr_t)(cursor + 2);
    if (cursor) {
        cursor[0] = value;
        cursor[1] = 2;
    }
    object[4 / 4] = object[4 / 4] + 1;
}

void push_tagged_c_0(uint32_t *object, uint32_t value)
{
    uint32_t *cursor = (uint32_t *)(uintptr_t)object[0xc / 4];
    object[0xc / 4] = (uint32_t)(uintptr_t)(cursor + 2);
    if (cursor) {
        cursor[0] = value;
        cursor[1] = 0;
    }
    object[4 / 4] = object[4 / 4] + 1;
}

uint32_t check_byte_1088_and_clear_dat(uint8_t *object)
{
    static uint32_t dat_storage;
    uint32_t result = (object[0x1088] == 0);
    if (result) dat_storage = 0;
    (void)dat_storage;
    return result;
}

void set_dat_to_1(void)
{
    static uint32_t dat_storage;
    dat_storage = 1;
    (void)dat_storage;
}

void set_dat_to_1_b(void)
{
    static uint32_t dat_storage;
    dat_storage = 1;
    (void)dat_storage;
}

void clear_byte_428_and_9_if_8(uint8_t *object)
{
    if (object[8] != 0) {
        object[0x428] = 0;
        object[9] = 5;
    }
}

void clear_state_8_10_14(uint32_t *object)
{
    object[0x14 / 4] = 0;
    object[0x10 / 4] = 0;
    object[0xc / 4] = 0;
    object[8 / 4] = 0;
    clear_word_field_4_b(object);
}

uint32_t get_byte_880_shift_7(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0];
    return *(uint8_t *)((uint8_t *)sub + 0x880) >> 7;
}

uint32_t get_byte_880_mask_7fff_shift_e(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0];
    return (*(uint32_t *)((uint8_t *)sub + 0x880) & 0x7fff) >> 0xe;
}

uint32_t check_byte_ff1_is_2(uint8_t *object)
{
    return object[0xff1] == 2;
}

void set_byte_ff1_to_2(uint8_t *object)
{
    object[0xff1] = 2;
}

void clear_byte_ff1(uint8_t *object)
{
    object[0xff1] = 0;
}

uint32_t return_dat(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

void init_byte_4_5(uint32_t *object)
{
    *(uint8_t *)((uint8_t *)object + 4) = 0;
    *(uint8_t *)((uint8_t *)object + 5) = 0;
}

void call_nested_3dc(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0x3dc / 4];
    if (sub) {
        (void)sub[0];
        (void)object[0x3e0 / 4];
    }
}

void call_nested_3e4(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0x3e4 / 4];
    if (sub) {
        (void)sub[0];
        (void)object[1000 / 4];
    }
}

void call_nested_3d0(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0x3d0 / 4];
    if (sub) {
        (void)sub[0];
        (void)object[0x3d4 / 4];
    }
}

void set_pair_dat(uint32_t a, uint32_t b)
{
    static uint32_t dat_storage[2];
    dat_storage[0] = a;
    dat_storage[1] = b;
    (void)dat_storage;
}

void clear_dat(void)
{
    static uint32_t dat_storage;
    dat_storage = 0;
    (void)dat_storage;
}

void increment_word(uint32_t *object)
{
    static uint32_t sentinel;
    if (object != &sentinel) {
        *object = *object + 1;
    }
}

void set_dat_8(uint32_t value)
{
    static uint32_t dat_storage[3];
    dat_storage[2] = value;
    (void)dat_storage;
}

void init_pair_0_93(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0x93;
}

void set_dat_byte_1(void)
{
    static uint8_t dat_storage[2];
    dat_storage[1] = 1;
    (void)dat_storage;
}

static uint32_t dat_18_storage[7];

uint32_t check_dat_18_mask_7_is_6(void)
{
    return (dat_18_storage[6] & 7) == 6;
}

void set_dat_18(uint32_t value)
{
    dat_18_storage[6] = value;
}

void set_dat_14(uint32_t value)
{
    static uint32_t dat_storage[6];
    dat_storage[5] = value;
    (void)dat_storage;
}

void set_dat(uint32_t value)
{
    static uint32_t dat_storage;
    dat_storage = value;
    (void)dat_storage;
}

void set_dat_4(uint32_t value)
{
    static uint32_t dat_storage[2];
    dat_storage[1] = value;
    (void)dat_storage;
}

void set_dat_byte_d(uint8_t value)
{
    static uint8_t dat_storage[14];
    dat_storage[0xd] = value;
    (void)dat_storage;
}

uint32_t svc_8_store(uint32_t *object, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    (void)b; (void)c;
    *object = a;
    return d;
}

void svc_2b_store(uint32_t *object, uint32_t a, uint32_t b)
{
    *object = a;
    object[1] = b;
}

void init_list_heads(uint32_t *object)
{
    object[1] = (uint32_t)(uintptr_t)(object + 3);
    object[0] = 0;
    object[2] = (uint32_t)(uintptr_t)(object + 3);
    object[8] = (uint32_t)(uintptr_t)(object + 10);
    object[7] = 0;
    object[9] = (uint32_t)(uintptr_t)(object + 10);
}

void init_pair_50_5c(uint32_t *object)
{
    object[0x50 / 4] = 0;
    object[0x5c / 4] = 0;
}

void set_pair_dat_4_8(uint32_t a, uint32_t b)
{
    static uint32_t dat_storage[3];
    dat_storage[1] = a;
    dat_storage[2] = b;
    (void)dat_storage;
}

void set_dat_b(uint32_t value)
{
    static uint32_t dat_storage;
    dat_storage = value;
    (void)dat_storage;
}

uint8_t return_dat_byte(void)
{
    static uint8_t dat_storage;
    return dat_storage;
}

void init_triple_0_1_2_b(uint32_t *object)
{
    object[1] = 0;
    object[0] = 0;
    object[2] = 0;
}

uint8_t return_dat_byte_1(void)
{
    static uint8_t dat_storage[2];
    return dat_storage[1];
}

void set_dat_byte_1_2(uint8_t value)
{
    static uint8_t dat_storage[3];
    dat_storage[1] = 1;
    dat_storage[2] = value;
    (void)dat_storage;
}

uint32_t return_dat_b(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

static uint8_t dat_byte_8_storage[9];

void set_dat_byte_8(void)
{
    dat_byte_8_storage[8] = 1;
}

int32_t return_dat_byte_8(void)
{
    return (int32_t)(int8_t)dat_byte_8_storage[8];
}

void clear_dat_byte_8(void)
{
    dat_byte_8_storage[8] = 0;
}

static uint8_t dat_byte_7_storage[8];

void set_dat_byte_7(void)
{
    dat_byte_7_storage[7] = 1;
}

int32_t return_dat_byte_7(void)
{
    return (int32_t)(int8_t)dat_byte_7_storage[7];
}

void clear_dat_byte_7(void)
{
    dat_byte_7_storage[7] = 0;
}

static uint8_t dat_byte_3_storage[4];

uint8_t return_dat_byte_3(void)
{
    return dat_byte_3_storage[3];
}

void set_dat_byte_4(uint8_t value)
{
    static uint8_t dat_storage[5];
    dat_storage[4] = value;
    (void)dat_storage;
}

void set_dat_byte_3(uint8_t value)
{
    dat_byte_3_storage[3] = value;
}

void clear_dat_byte_3(void)
{
    dat_byte_3_storage[3] = 0;
}

void set_dat_byte_2(uint8_t value)
{
    static uint8_t dat_storage[3];
    dat_storage[2] = value;
    (void)dat_storage;
}

void clear_dat_byte_2(void)
{
    static uint8_t dat_storage[3];
    dat_storage[2] = 0;
    (void)dat_storage;
}

static uint32_t return_dat_10_storage[5];

uint32_t return_dat_10(void)
{
    return return_dat_10_storage[4];
}

static uint32_t return_dat_c_storage[4];

uint32_t return_dat_c(void)
{
    return return_dat_c_storage[3];
}

uint8_t return_dat_byte_5(void)
{
    static uint8_t dat_storage[6];
    return dat_storage[5];
}

void set_dat_byte_1_b(void)
{
    static uint8_t dat_storage[2];
    dat_storage[1] = 1;
    (void)dat_storage;
}

void set_byte_4_and_word_0(uint32_t *object, uint8_t value)
{
    *(uint8_t *)((uint8_t *)object + 4) = value;
    object[0] = 0;
}

void set_dat_c(uint32_t value)
{
    static uint32_t dat_storage[4];
    dat_storage[3] = value;
    (void)dat_storage;
}

uint32_t return_dat_d(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

void set_dat_indexed(int32_t index, uint32_t value)
{
    static uint32_t dat_table[16];
    if ((uint32_t)index < 16) dat_table[index] = value;
    (void)dat_table;
}

void store_triple_150_to_dat(uint32_t *object)
{
    static uint32_t dat_storage[3];
    dat_storage[0] = object[0x150 / 4];
    dat_storage[1] = object[0x154 / 4];
    dat_storage[2] = 0;
    (void)dat_storage;
}

uint32_t get_table_byte_bounded(uint32_t index)
{
    static const uint8_t table[14] = {0};
    if (index > 0xd) return 0xffffffff;
    return table[index];
}

uint32_t return_dat_c_b(void)
{
    static uint32_t dat_storage[4];
    return dat_storage[3];
}

uint8_t return_dat_byte_a(void)
{
    static uint8_t dat_storage[11];
    return dat_storage[10];
}

void set_pair_dat_14_54(uint32_t a, uint32_t b)
{
    static uint32_t dat_storage[22];
    dat_storage[5] = a;
    dat_storage[21] = b;
    (void)dat_storage;
}

int32_t return_dat_byte_d(void)
{
    static uint8_t dat_storage[14];
    return (int32_t)(int8_t)dat_storage[13];
}

void set_dat_byte_9(void)
{
    static uint8_t dat_storage[10];
    dat_storage[9] = 1;
    (void)dat_storage;
}

void set_dat_8_b(uint32_t value)
{
    static uint32_t dat_storage[3];
    dat_storage[2] = value;
    (void)dat_storage;
}

void set_dat_to_1_c(void)
{
    static uint32_t dat_storage;
    dat_storage = 1;
    (void)dat_storage;
}

uint32_t return_dat_e(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

void set_dat_byte_1_c(uint8_t value)
{
    static uint8_t dat_storage[2];
    dat_storage[1] = value;
    (void)dat_storage;
}

void set_dat_4_b(uint32_t value)
{
    static uint32_t dat_storage[2];
    dat_storage[1] = value;
    (void)dat_storage;
}

uint32_t get_table_word(int32_t index)
{
    static const uint32_t table[16] = {0};
    return table[index & 0xf];
}

int32_t return_signed_dat_byte(void)
{
    static int8_t dat_storage;
    return (int32_t)dat_storage;
}

uint32_t return_dat_4(void)
{
    static uint32_t dat_storage[2];
    return dat_storage[1];
}

uint32_t map_1_2_4_to_0_1_2(uint32_t value)
{
    if (value == 2) return 1;
    if (value == 4) return 2;
    return 0;
}

void set_dat_4_c(uint32_t value)
{
    static uint32_t dat_storage[2];
    dat_storage[1] = value;
    (void)dat_storage;
}

uint32_t check_nested_byte_b410_is_2(uint32_t *object)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[0];
    return sub[0xb410] == 2;
}

uint32_t get_byte_880_mask_7_shift_2(uint32_t *object)
{
    uint8_t *sub = (uint8_t *)(uintptr_t)object[0];
    return (sub[0x880] & 7) >> 2;
}

uint32_t get_byte_880_mask_3fff_shift_d(uint32_t *object)
{
    uint32_t *sub = (uint32_t *)(uintptr_t)object[0];
    return (sub[0x880 / 4] & 0x3fff) >> 0xd;
}

uint32_t return_dat_4_b(void)
{
    static uint32_t dat_storage[2];
    return dat_storage[1];
}

uint32_t return_dat_f(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

int32_t get_nested_table_byte_5(uint8_t *object)
{
    static uint32_t dat_table[16];
    uint32_t *entry = (uint32_t *)(uintptr_t)dat_table[object[0] & 0xf];
    if (!entry) return 0;
    return (int32_t)*(int8_t *)((uint8_t *)entry + 5);
}

void init_record_4_10(uint32_t *object)
{
    object[0] = 0;
    *(uint16_t *)(object + 1) = 0;
    *(uint8_t *)((uint8_t *)object + 6) = 0;
    *(uint16_t *)(object + 2) = 0;
    *(uint8_t *)((uint8_t *)object + 10) = 0;
}

void init_record_208(uint32_t *object)
{
    object[1] = 0;
    object[0] = 0;
    *(uint16_t *)(object + 0x82) = 0;
    *(uint8_t *)((uint8_t *)object + 0x20a) = 0;
}

void init_pair_0_1(uint32_t *object)
{
    object[0] = 0;
    object[1] = 0;
}

void init_quad_0_1_2_3(uint32_t *object)
{
    object[1] = 0;
    object[0] = 0;
    object[2] = 0;
    object[3] = 0;
}

uint32_t svc_28_return(uint32_t value)
{
    return value;
}

uint32_t svc_1e_store(uint32_t *object, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    (void)b; (void)c;
    *object = a;
    return d;
}

uint32_t svc_10_return(uint32_t value)
{
    return value;
}

uint32_t return_dat_4_c(void)
{
    static uint32_t dat_storage[2];
    return dat_storage[1];
}

uint32_t return_dat_10_b(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

int32_t get_table_halfword_signed(int32_t index)
{
    static const int16_t table[16] = {0};
    return (int32_t)table[index & 0xf];
}

void init_mask_record(uint32_t *object)
{
    object[4 / 4] = 0xff000000;
    object[8 / 4] = 0x00ff0000;
    object[0xc / 4] = 0x00ffffff;
    object[0x10 / 4] = 0xff00ffff;
    object[0x14 / 4] = 0;
}

void init_record_c_string(uint32_t *object, uint16_t value, uint32_t extra)
{
    *(uint16_t *)(object + 3) = value;
    object[0] = 0;
    object[1] = 0;
    object[4] = extra;
    object[2] = 0;
}

uint32_t return_dat_11(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

uint32_t return_after_call_b(uint32_t value)
{
    return value;
}

uint32_t return_dat_12(void)
{
    static uint32_t dat_storage;
    return dat_storage;
}

void set_dat_d(uint32_t value)
{
    static uint32_t dat_storage;
    dat_storage = value;
    (void)dat_storage;
}

int32_t return_dat_byte_67(void)
{
    static uint8_t dat_storage[0x68];
    return (int32_t)(int8_t)dat_storage[0x67];
}

int32_t return_dat_byte_1_b(void)
{
    static uint8_t dat_storage[2];
    return (int32_t)(int8_t)dat_storage[1];
}

uint32_t check_dat_is_8(void)
{
    static uint32_t dat_storage;
    return dat_storage == 8;
}

uint32_t return_dat_138(void)
{
    static uint32_t dat_storage[0x13c / 4];
    return dat_storage[0x138 / 4];
}

void set_dat_to_1_d(void)
{
    static uint32_t dat_storage;
    dat_storage = 1;
    (void)dat_storage;
}

void set_dat_halfword_1c(uint16_t value)
{
    static uint16_t dat_storage[0x1e / 2];
    dat_storage[0x1c / 2] = value;
    (void)dat_storage;
}

void set_dat_byte_8_b(void)
{
    static uint8_t dat_storage[9];
    dat_storage[8] = 1;
    (void)dat_storage;
}

uint32_t return_dat_13c(void)
{
    static uint32_t dat_storage[0x140 / 4];
    return dat_storage[0x13c / 4];
}

int32_t return_dat_byte_69(void)
{
    static uint8_t dat_storage[0x6a];
    return (int32_t)(int8_t)dat_storage[0x69];
}

void set_dat_byte_465(void)
{
    static uint8_t dat_storage[0x466];
    dat_storage[0x465] = 1;
    (void)dat_storage;
}

void clear_dat_b(void)
{
    static uint32_t dat_storage;
    dat_storage = 0;
    (void)dat_storage;
}

void clear_dat_byte_465(void)
{
    static uint8_t dat_storage[0x466];
    dat_storage[0x465] = 0;
    (void)dat_storage;
}

static uint8_t dat_byte_17_storage[0x18];

uint8_t return_dat_byte_17(void)
{
    return dat_byte_17_storage[0x17];
}

uint32_t set_dat_byte_17_if_positive(int32_t value)
{
    if (value < 0) return 0xffffffff;
    dat_byte_17_storage[0x17] = (uint8_t)value;
    return 0;
}

void clear_dat_and_5c(void)
{
    static uint8_t dat_storage[0x60];
    dat_storage[0] = 0;
    *(uint32_t *)(dat_storage + 0x5c) = 0;
    (void)dat_storage;
}

uint8_t return_dat_byte_17_b(void)
{
    static uint8_t dat_storage[0x18];
    return dat_storage[0x17];
}

uint32_t return_dat_40(void)
{
    static uint32_t dat_storage[0x44 / 4];
    return dat_storage[0x40 / 4];
}

int32_t get_float_dat_4_as_int_or_neg(void)
{
    static uint32_t dat_ptr[2];
    if (dat_ptr[0] == 0) return -1;
    return (int32_t)*(float *)(uintptr_t)(dat_ptr[0] + 4);
}

uint32_t pop_dat_4(void)
{
    static uint32_t dat_storage[2];
    uint32_t value = dat_storage[1];
    dat_storage[1] = 0;
    return value;
}

void set_dat_to_1_e(void)
{
    static uint32_t dat_storage;
    dat_storage = 1;
    (void)dat_storage;
}

uint32_t add_to_dat_28_wrap(uint32_t value)
{
    static uint32_t dat_storage[0x2c / 4];
    uint32_t sum = value + dat_storage[0x28 / 4];
    if (sum < dat_storage[0x28 / 4]) sum = 0xffffffff;
    dat_storage[0x28 / 4] = sum;
    return 0;
}

uint16_t get_nested_table_halfword_4(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint16_t *)((uint8_t *)sub + idx2 * 0x20 + 4);
}

uint32_t get_nested_table_word_c(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint32_t *)((uint8_t *)sub + idx2 * 0x20 + 0xc);
}

uint32_t get_nested_table_20_word_8(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint32_t *)((uint8_t *)sub + idx2 * 0x20 + 8);
}

uint32_t get_nested_table_c_word_8(int32_t index)
{
    static uint32_t dat_table[32];
    return dat_table[(index & 0x1f) * 3 + 2];
}

uint32_t get_table_word_bounded_19(uint32_t index)
{
    static const uint32_t table[26] = {0};
    if (index > 0x19) index = 0;
    return table[index];
}

uint32_t check_dat_nonzero(void)
{
    static uint32_t dat_storage;
    return dat_storage != 0;
}

uint8_t get_table_18_byte_c(int32_t index)
{
    static const uint8_t table[16 * 0x18];
    return table[(index & 0xf) * 0x18 + 0xc];
}

uint32_t get_table_18_word_8_or_2(int32_t index, uint32_t mode)
{
    static const uint32_t table[16 * 6];
    uint32_t value = table[(index & 0xf) * 6 + 2];
    if (mode == 0x16) value |= 2;
    return value;
}

uint32_t return_dat_20(void)
{
    static uint32_t dat_storage[9];
    return dat_storage[8];
}

uint32_t check_dat_20_nonzero(void)
{
    static uint32_t dat_storage[9];
    return dat_storage[8] != 0;
}

uint8_t return_byte_49f2(const uint8_t *object)
{
    return object[0x49f2];
}

uint32_t check_word_88_nonzero(const uint32_t *object)
{
    return object[0x88 / 4] != 0;
}

uint32_t get_table_word_bounded_16(uint32_t index)
{
    static const uint32_t table[23] = {0};
    if (index >= 0x17) return 0xffffffff;
    return table[index];
}

void set_dat_byte(uint8_t value)
{
    static uint8_t dat_storage;
    dat_storage = value;
    (void)dat_storage;
}

void copy_pair_bc8(uint32_t *dest, const uint8_t *src)
{
    dest[0] = *(const uint32_t *)(src + 0xbc8);
    dest[1] = *(const uint32_t *)(src + 0xbcc);
}

void unlink_and_clear_18(uint32_t *list, uint8_t *node)
{
    remove_list_entry(list, (uint32_t *)(node + 0x110));
    *(uint32_t *)(node + 0x18) = 0;
}

void clamp_word_34_to_2c(uint32_t *object, uint32_t value)
{
    if (value <= object[0x2c / 4]) {
        object[0x34 / 4] = value;
    }
}

uint32_t get_word_and_halfword(const uint32_t *object, uint32_t *high_out)
{
    *high_out = object[0];
    return *(const uint16_t *)(object + 1);
}

void copy_strided_c_1c_2c(const uint8_t *object, uint32_t *dest)
{
    dest[0] = *(const uint32_t *)(object + 0xc);
    dest[1] = *(const uint32_t *)(object + 0x1c);
    dest[2] = *(const uint32_t *)(object + 0x2c);
}

void copy_word_and_halfword(uint32_t *dest, const uint32_t *src)
{
    dest[0] = src[0];
    *(uint16_t *)(dest + 1) = *(const uint16_t *)(src + 1);
}

uint32_t *get_indexed_380_entry(uint32_t *object, int32_t index)
{
    uint32_t *entry = (uint32_t *)((uint8_t *)(uintptr_t)object[0x10 / 4] + index * 0x380);
    if (entry[4 / 4] == 0) return 0;
    return entry;
}

uint32_t get_table_1c_word_18(int32_t index)
{
    static const uint32_t table[16 * 7];
    return table[(index & 0xf) * 7 + 6];
}

uint32_t get_nested_table_20_word(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint32_t *)((uint8_t *)sub + idx2 * 0x20);
}

uint32_t get_nested_table_18_word_10(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint32_t *)((uint8_t *)sub + idx2 * 0x18 + 0x10);
}

uint32_t get_nested_table_18_word_4(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint32_t *)((uint8_t *)sub + idx2 * 0x18 + 4);
}

uint32_t get_nested_table_18_word_14(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint32_t *)((uint8_t *)sub + idx2 * 0x18 + 0x14);
}

uint32_t get_nested_table_18_word_c(int32_t idx1, int32_t idx2)
{
    static uint32_t dat_table[16];
    uint32_t *sub = (uint32_t *)(uintptr_t)dat_table[(idx1 & 0xf) * 2 + 1];
    if (!sub) return 0;
    return *(uint32_t *)((uint8_t *)sub + idx2 * 0x18 + 0xc);
}

uint8_t get_entry_and_byte(uint32_t *object, int32_t index, uint32_t *entry_out)
{
    static const uint32_t dat_entries[16 * 16];
    static const uint8_t dat_bytes[16];
    (void)object;
    *entry_out = (uint32_t)(uintptr_t)&dat_entries[(index & 0xf) * 16];
    return dat_bytes[index & 0xf];
}

void select_word_by_byte_61(uint32_t *dest, const uint8_t *src)
{
    if (src[0x61] == 1) {
        *dest = 0;
    } else {
        *dest = 0xffffffff;
    }
}

void init_triple_dat(uint32_t *object)
{
    object[1] = 0;
    object[0] = 0;
    object[2] = 0;
}
