#ifndef LM3DS_SYSTEM_INTERFACE_H
#define LM3DS_SYSTEM_INTERFACE_H

#include <stdint.h>

typedef uint32_t Handle;
typedef int32_t Result;

enum {
    SVC_EXIT_THREAD = 0x09,
    SVC_SLEEP_THREAD = 0x0a,
    SVC_CREATE_MUTEX = 0x14,
    SVC_RELEASE_MUTEX = 0x15,
    SVC_CREATE_EVENT = 0x17,
    SVC_SIGNAL_EVENT = 0x18,
    SVC_CLEAR_EVENT = 0x19,
    SVC_CREATE_THREAD = 0x08,
    SVC_WAIT_SYNC = 0x19,
    SVC_WAIT_SYNC2 = 0x21,
    SVC_GET_THREAD_ID = 0x37,
    SVC_GET_PROCESS_ID = 0x39,
    SVC_GET_SYSTEM_TICK = 0x28,
    SVC_MAP_MEMORY = 0x01,
    SVC_UNMAP_MEMORY = 0x02,
    SVC_CREATE_MEMORY_BLOCK = 0x1a,
    SVC_FREE_MEMORY_BLOCK = 0x1b,
    SVC_QUERY_MEMORY = 0x02,
    SVC_EXIT_PROCESS = 0x03,
    SVC_CREATE_ADDRESS_ARBITER = 0x21,
    SVC_ARBITRATE_ADDRESS = 0x22,
    SVC_CLOSE_HANDLE = 0x23,
    SVC_WAIT_SYNC1 = 0x24,
    SVC_WAIT_SYNC2_OLD = 0x25,
    SVC_BREAK = 0x3c,
    SVC_OUTPUT_DEBUG_STRING = 0x3d,
    SVC_GET_RESOURCE_LIMIT = 0x38,
    SVC_GET_RESOURCE_LIMIT_CURRENT = 0x39,
    SVC_GET_RESOURCE_LIMIT_LIMIT = 0x3a,
    SVC_SET_RESOURCE_LIMIT = 0x38,
    SVC_SET_RESOURCE_LIMIT_CURRENT = 0x39,
    SVC_SET_RESOURCE_LIMIT_LIMIT = 0x3a,
    SVC_CREATE_SESSION = 0x32,
    SVC_SEND_SYNC_REQUEST = 0x32,
    SVC_GET_SESSION = 0x32,
    SVC_CLOSE_SESSION = 0x32,
    SVC_GET_PROCESS_INFO = 0x2b,
    SVC_GET_THREAD_INFO = 0x2c,
    SVC_GET_SYSTEM_INFO = 0x2d,
    SVC_GET_THREAD_PRIORITY = 0x0b,
    SVC_SET_THREAD_PRIORITY = 0x0c,
    SVC_GET_THREAD_CORE_MASK = 0x0e,
    SVC_SET_THREAD_CORE_MASK = 0x0f,
    SVC_GET_THREAD_CONTEXT = 0x3b,
    SVC_SET_THREAD_CONTEXT = 0x3c,
    SVC_GET_THREAD_ARGUMENT = 0x3d,
    SVC_SET_THREAD_ARGUMENT = 0x3e,
    SVC_GET_PROCESS_ARGUMENT = 0x3f,
    SVC_SET_PROCESS_ARGUMENT = 0x40,
    SVC_GET_PROCESS_AFFINITY = 0x41,
    SVC_SET_PROCESS_AFFINITY = 0x42,
    SVC_GET_PROCESS_IDEAL_PROCESSOR = 0x43,
    SVC_SET_PROCESS_IDEAL_PROCESSOR = 0x44,
    SVC_GET_PROCESS_LIST = 0x45,
    SVC_GET_THREAD_LIST = 0x46,
    SVC_GET_PROCESS_LIST_OF_PROCESS = 0x47,
    SVC_GET_THREAD_LIST_OF_PROCESS = 0x48,
    SVC_GET_PROCESS_HANDLE = 0x49,
    SVC_GET_THREAD_HANDLE = 0x4a,
    SVC_GET_PROCESS_HANDLE_COUNT = 0x4b,
    SVC_GET_THREAD_HANDLE_COUNT = 0x4c,
    SVC_GET_PROCESS_HANDLE_LIST = 0x4d,
    SVC_GET_THREAD_HANDLE_LIST = 0x4e,
    SVC_GET_PROCESS_HANDLE_TYPE = 0x4f,
    SVC_GET_THREAD_HANDLE_TYPE = 0x50,
    SVC_GET_PROCESS_HANDLE_SIGNAL = 0x51,
    SVC_GET_THREAD_HANDLE_SIGNAL = 0x52,
    SVC_GET_PROCESS_HANDLE_INFO = 0x55,
    SVC_GET_THREAD_HANDLE_INFO = 0x56,
    SVC_GET_PROCESS_HANDLE_NAME = 0x57,
    SVC_GET_THREAD_HANDLE_NAME = 0x58,
    SVC_GET_PROCESS_HANDLE_OWNER = 0x59,
    SVC_GET_THREAD_HANDLE_OWNER = 0x5a,
    SVC_GET_PROCESS_HANDLE_PARENT = 0x5b,
    SVC_GET_THREAD_HANDLE_PARENT = 0x5c,
    SVC_GET_PROCESS_HANDLE_CHILDREN = 0x5d,
    SVC_GET_THREAD_HANDLE_CHILDREN = 0x5e,
    SVC_GET_PROCESS_HANDLE_STATE = 0x5f,
    SVC_GET_THREAD_HANDLE_STATE = 0x60,
    SVC_GET_PROCESS_HANDLE_FLAGS = 0x61,
    SVC_GET_THREAD_HANDLE_FLAGS = 0x62,
    SVC_GET_PROCESS_HANDLE_ATTRIBUTES = 0x63,
    SVC_GET_THREAD_HANDLE_ATTRIBUTES = 0x64,
    SVC_GET_PROCESS_HANDLE_REFERENCE = 0x65,
    SVC_GET_THREAD_HANDLE_REFERENCE = 0x66,
    SVC_GET_PROCESS_HANDLE_SECURITY = 0x67,
    SVC_GET_THREAD_HANDLE_SECURITY = 0x68,
    SVC_GET_PROCESS_HANDLE_CAPABILITY = 0x69,
    SVC_GET_THREAD_HANDLE_CAPABILITY = 0x6a,
    SVC_GET_PROCESS_HANDLE_PROTECTION = 0x6b,
    SVC_GET_THREAD_HANDLE_PROTECTION = 0x6c,
    SVC_GET_PROCESS_HANDLE_ACCESS = 0x6d,
    SVC_GET_THREAD_HANDLE_ACCESS = 0x6e,
    SVC_GET_PROCESS_HANDLE_RIGHTS = 0x6f,
    SVC_GET_THREAD_HANDLE_RIGHTS = 0x70,
    SVC_GET_PROCESS_HANDLE_GRANTED = 0x71,
    SVC_GET_THREAD_HANDLE_GRANTED = 0x72,
    SVC_GET_PROCESS_HANDLE_INHERITED = 0x73,
    SVC_GET_THREAD_HANDLE_INHERITED = 0x74,
    SVC_GET_PROCESS_HANDLE_DUPLICATE = 0x75,
    SVC_GET_THREAD_HANDLE_DUPLICATE = 0x76,
    SVC_GET_PROCESS_HANDLE_OPEN = 0x77,
    SVC_GET_THREAD_HANDLE_OPEN = 0x78,
    SVC_GET_PROCESS_HANDLE_CLOSE = 0x79,
    SVC_GET_THREAD_HANDLE_CLOSE = 0x7a,
    SVC_GET_PROCESS_HANDLE_COPY = 0x7b,
    SVC_GET_THREAD_HANDLE_COPY = 0x7c,
    SVC_GET_PROCESS_HANDLE_MOVE = 0x7d,
    SVC_GET_THREAD_HANDLE_MOVE = 0x7e,
    SVC_GET_PROCESS_HANDLE_WAIT = 0x7f,
    SVC_GET_THREAD_HANDLE_WAIT = 0x80
};

Result svc_exit_thread(void);
Result svc_sleep_thread(int64_t nanoseconds);
Result svc_create_mutex(Handle *handle, int initially_locked);
Result svc_release_mutex(Handle handle);
Result svc_create_event(Handle *handle, int reset_type);
Result svc_signal_event(Handle handle);
Result svc_clear_event(Handle handle);
Result svc_create_thread(Handle *handle, void (*entry)(void *), void *argument,
    void *stack_top, int priority, int processor);
Result svc_wait_sync(Handle handle, int64_t timeout);
Result svc_wait_sync2(Handle *handles, uint32_t count, int64_t timeout);
Result svc_get_thread_id(uint32_t *thread_id);
Result svc_get_process_id(uint32_t *process_id);
Result svc_get_system_tick(uint64_t *tick);
Result svc_map_memory(Handle process, void *address, void *source, uint32_t size);
Result svc_unmap_memory(Handle process, void *address, uint32_t size);
Result svc_create_memory_block(Handle *handle, void *address, uint32_t size,
    uint32_t permissions);
Result svc_free_memory_block(Handle handle);
Result svc_query_memory(void *address, uint32_t *info);
Result svc_exit_process(int32_t status);
Result svc_create_address_arbiter(Handle *handle);
Result svc_arbitrate_address(Handle handle, void *address, uint32_t type,
    int32_t value, int64_t timeout);
Result svc_close_handle(Handle handle);
Result svc_output_debug_string(const char *string, uint32_t length);
Result svc_break(int32_t reason);
Result svc_get_resource_limit(Handle *handle);
Result svc_get_resource_limit_current(Handle handle, uint32_t *values);
Result svc_get_resource_limit_limit(Handle handle, uint32_t *values);
Result svc_set_resource_limit(Handle handle, uint32_t *values);
Result svc_set_resource_limit_current(Handle handle, uint32_t *values);
Result svc_set_resource_limit_limit(Handle handle, uint32_t *values);
Result svc_create_session(Handle *handle, const char *name);
Result svc_send_sync_request(Handle session);
Result svc_get_session(Handle *handle);
Result svc_close_session(Handle handle);
Result svc_get_process_info(uint32_t *info, uint32_t type);
Result svc_get_thread_info(uint32_t *info, uint32_t type);
Result svc_get_system_info(uint32_t *info, uint32_t type);
Result svc_get_thread_priority(uint32_t *priority, Handle thread);
Result svc_set_thread_priority(Handle thread, uint32_t priority);
Result svc_get_thread_core_mask(uint32_t *mask, Handle thread);
Result svc_set_thread_core_mask(Handle thread, uint32_t mask);
Result svc_get_thread_context(void *context, Handle thread);
Result svc_set_thread_context(Handle thread, void *context);
Result svc_get_thread_argument(uint32_t *argument, Handle thread);
Result svc_set_thread_argument(Handle thread, uint32_t argument);
Result svc_get_process_argument(uint32_t *argument, Handle process);
Result svc_set_process_argument(Handle process, uint32_t argument);
Result svc_get_process_affinity(uint32_t *affinity, Handle process);
Result svc_set_process_affinity(Handle process, uint32_t affinity);
Result svc_get_process_ideal_processor(uint32_t *processor, Handle process);
Result svc_set_process_ideal_processor(Handle process, uint32_t processor);
Result svc_get_process_list(uint32_t *list, uint32_t count);
Result svc_get_thread_list(uint32_t *list, uint32_t count);
Result svc_get_process_list_of_process(uint32_t *list, uint32_t count, Handle process);
Result svc_get_thread_list_of_process(uint32_t *list, uint32_t count, Handle process);
Result svc_get_process_handle(Handle *handle, uint32_t index);
Result svc_get_thread_handle(Handle *handle, uint32_t index);
Result svc_get_process_handle_count(uint32_t *count);
Result svc_get_thread_handle_count(uint32_t *count);
Result svc_get_process_handle_list(Handle *list, uint32_t count);
Result svc_get_thread_handle_list(Handle *list, uint32_t count);
Result svc_get_process_handle_type(uint32_t *type, Handle handle);
Result svc_get_thread_handle_type(uint32_t *type, Handle handle);
Result svc_get_process_handle_signal(uint32_t *signal, Handle handle);
Result svc_get_thread_handle_signal(uint32_t *signal, Handle handle);
Result svc_get_process_handle_wait(uint32_t *wait, Handle handle);
Result svc_get_thread_handle_wait(uint32_t *wait, Handle handle);
Result svc_get_process_handle_info(uint32_t *info, Handle handle);
Result svc_get_thread_handle_info(uint32_t *info, Handle handle);
Result svc_get_process_handle_name(char *name, uint32_t length, Handle handle);
Result svc_get_thread_handle_name(char *name, uint32_t length, Handle handle);
Result svc_get_process_handle_owner(Handle *owner, Handle handle);
Result svc_get_thread_handle_owner(Handle *owner, Handle handle);
Result svc_get_process_handle_parent(Handle *parent, Handle handle);
Result svc_get_thread_handle_parent(Handle *parent, Handle handle);
Result svc_get_process_handle_children(Handle *children, uint32_t count, Handle handle);
Result svc_get_thread_handle_children(Handle *children, uint32_t count, Handle handle);
Result svc_get_process_handle_state(uint32_t *state, Handle handle);
Result svc_get_thread_handle_state(uint32_t *state, Handle handle);
Result svc_get_process_handle_flags(uint32_t *flags, Handle handle);
Result svc_get_thread_handle_flags(uint32_t *flags, Handle handle);
Result svc_get_process_handle_attributes(uint32_t *attributes, Handle handle);
Result svc_get_thread_handle_attributes(uint32_t *attributes, Handle handle);
Result svc_get_process_handle_reference(uint32_t *reference, Handle handle);
Result svc_get_thread_handle_reference(uint32_t *reference, Handle handle);
Result svc_get_process_handle_security(uint32_t *security, Handle handle);
Result svc_get_thread_handle_security(uint32_t *security, Handle handle);
Result svc_get_process_handle_capability(uint32_t *capability, Handle handle);
Result svc_get_thread_handle_capability(uint32_t *capability, Handle handle);
Result svc_get_process_handle_protection(uint32_t *protection, Handle handle);
Result svc_get_thread_handle_protection(uint32_t *protection, Handle handle);
Result svc_get_process_handle_access(uint32_t *access, Handle handle);
Result svc_get_thread_handle_access(uint32_t *access, Handle handle);
Result svc_get_process_handle_rights(uint32_t *rights, Handle handle);
Result svc_get_thread_handle_rights(uint32_t *rights, Handle handle);
Result svc_get_process_handle_granted(uint32_t *granted, Handle handle);
Result svc_get_thread_handle_granted(uint32_t *granted, Handle handle);
Result svc_get_process_handle_inherited(uint32_t *inherited, Handle handle);
Result svc_get_thread_handle_inherited(uint32_t *inherited, Handle handle);
Result svc_get_process_handle_duplicate(Handle *duplicate, Handle handle);
Result svc_get_thread_handle_duplicate(Handle *duplicate, Handle handle);
Result svc_get_process_handle_open(Handle *open, Handle handle);
Result svc_get_thread_handle_open(Handle *open, Handle handle);
Result svc_get_process_handle_close(Handle *close, Handle handle);
Result svc_get_thread_handle_close(Handle *close, Handle handle);
Result svc_get_process_handle_copy(Handle *copy, Handle handle);
Result svc_get_thread_handle_copy(Handle *copy, Handle handle);
Result svc_get_process_handle_move(Handle *move, Handle handle);
Result svc_get_thread_handle_move(Handle *move, Handle handle);
Result svc_get_process_handle_wait(uint32_t *wait, Handle handle);
Result svc_get_thread_handle_wait(uint32_t *wait, Handle handle);

uint32_t coproc_movefrom_user_r_thread_and_process_id(void);

void *rt_memset(void *dest, uint32_t size, uint8_t value);
void get_system_tick(uint64_t *tick);
void recursive_mutex_lock(uint32_t *lock);
void recursive_mutex_unlock(uint32_t *lock);

void initialize_linked_list(uint32_t *list);
void push_list_front(uint32_t *list, uint32_t **head, uint32_t *node);
void pop_list_front(uint32_t *list);
void pop_list_back(uint32_t *list);
uint32_t get_block_size(uint32_t *block);
uint32_t map_event_type(uint32_t type);
int32_t clamp_with_deadzone(int32_t value, int32_t origin, int32_t deadzone, int32_t gain);
void set_field_value(uint32_t *field, uint32_t value);
uint32_t get_constant_value(void);
int check_object_ready(const uint8_t *object);
void reset_object_fields(uint32_t *object);
uint32_t wide_string_length(const uint16_t *string);
void copy_short_struct(uint32_t *dest, const uint32_t *src);
int is_field_zero(const uint32_t *object);
void invalidate_field(uint32_t *object);
void invalidate_handle_field(uint32_t *object);
void unlink_handle_reference(uint32_t *slot);
void unlink_object_reference(uint32_t *object);
void clear_short_struct(uint32_t *dest);
int is_alternate_mode(uint32_t mode);
void set_byte_pair_high(uint32_t *object, uint8_t first, uint8_t second);
void set_byte_pair_low(uint32_t *object, uint8_t first, uint8_t second);
void set_conditional_field(uint32_t *object, uint32_t mode, uint32_t value);
uint32_t get_slot_index(uint32_t *table_base, uint32_t handle);
void initialize_flag_block(uint32_t *object);
uint32_t get_indexed_field(const uint32_t *object, uint32_t index);
void accumulate_global(uint32_t *total, uint32_t value);
void set_global_halfword(uint16_t *target, uint16_t value);
uint8_t get_indexed_byte(const uint32_t *pair, uint32_t index);
void *rt_memzero(void *dest, uint32_t size);
char *copy_string_padded(char *dest, const char *src, uint32_t size);
void *rt_memcpy(void *dest, const void *src, uint32_t size);
int32_t semaphore_post(uint32_t *semaphore, int32_t count);
int queue_pop(uint32_t *queue, uint32_t *out_value);
void write_command_record(uint32_t *ring, uint32_t command, const void *payload);
void write_command_record_indexed(uint32_t *ring, const uint32_t *table,
                                  const void *payload);
void remove_list_node(uint32_t *list, uint32_t *node);
void set_global_byte(uint8_t *target, uint8_t value);
void remove_list_entry(uint32_t *count, uint32_t *node);
void transform_point_affine(float *out, const float *matrix, const float *point);
void fill_word_range(uint32_t *start, uint32_t *end, uint32_t value);
void initialize_render_descriptor(uint16_t *descriptor);
void saturating_add_indexed(uint32_t *object, const uint32_t *amount, uint32_t index);
void clear_global_block(uint32_t *block);
void saturating_add_total(uint32_t *object, const uint32_t *amount);
int test_flag_bit(const uint32_t *object, uint32_t bit);
uint32_t *get_indexed_slot(uint32_t *object, uint32_t index);
int has_attached_pointer(const uint32_t *object);
uint16_t *append_wide_string_bounded(uint16_t *dest, const uint16_t *src, uint32_t limit);
void store_vector4(uint32_t *dest, const uint32_t *src);
uint32_t *build_wide_string_descriptor(uint32_t *descriptor, uint32_t tag, const uint16_t *string);
int has_backing_store(const uint32_t *object);
int has_active_subobject(const uint32_t *object);
void transpose_matrix_rows(uint32_t *dest, const uint32_t *src);
void set_object_handle_field(uint32_t *object, uint32_t handle, uint32_t value);
uint32_t take_and_clear_global(uint32_t *slot);
uint32_t *insert_list_back(uint32_t *list, uint32_t *node);
uint32_t *insert_list_after(uint32_t *count, uint32_t *at, uint32_t *node);
void copy_pair(uint32_t *dest, const uint32_t *src);
void clear_list(uint32_t *count, uint32_t *head);
void set_byte_at_offset(uint8_t *base, uint8_t value);
uint32_t get_table_entry(const uint32_t *table, uint32_t index);
uint32_t resolve_range_entry(uint32_t table, uint32_t key);
void clamp_render_descriptor(int16_t *descriptor);
void build_range_descriptor(uint32_t *descriptor, uint32_t tag, uint32_t base, uint32_t size);
uint32_t get_region_tag(void);
int get_service_state_byte(void);
void set_bitset_bit(uint32_t *bitset, uint32_t bit);
void clear_byte_flag(uint8_t *object);
void initialize_command_descriptor(uint8_t *descriptor);
uint32_t *copy_quad_pair(uint32_t *dest, const uint32_t *src);
void clear_pair(uint32_t *dest);
void noop_operation(void);
void build_region_record(uint8_t *record, int32_t x, int32_t y, int32_t x2, int32_t y2,
                         uint32_t extra_a, uint32_t extra_b);
void reset_write_buffer(uint32_t *buffer);
void lookup_command_value(int16_t *out_tag, int16_t *out_value, uint32_t command);
void initialize_region_block(uint8_t *block);
void initialize_list_head_pair(uint32_t *list);
void initialize_record(uint32_t *record, uint32_t tag);
void clear_quad(uint32_t *dest);
void clear_state_fields(uint8_t *object);
void set_status_byte_b(uint8_t *block, uint8_t value);
int get_status_byte_9(const uint8_t *block);
void set_status_byte_c(uint8_t *block, uint8_t value);
uint8_t get_status_byte_c(const uint8_t *block);
int get_status_byte_1(const uint8_t *block);
uint8_t get_status_byte_6(const uint8_t *block);
uint8_t get_status_byte_2(const uint8_t *block);
int get_object_field_120(const uint8_t *object);
uint32_t map_service_mode(uint32_t mode);
uint8_t get_indexed_status_byte(const uint8_t *block, uint32_t offset);
void svc_store_word(uint32_t *target, uint32_t value);
void add_map_entry(uint32_t *map, uint32_t key, uint32_t value);
uint32_t get_word_field_1c(const uint32_t *object);
uint32_t get_word_field_18(const uint32_t *object);
uint32_t compare_wide_strings(const uint16_t *a, const uint16_t *b);
uint32_t test_flag_80(const uint32_t *object);
void increment_reference_count(uint32_t *slot, uint32_t *target);
uint32_t *get_indexed_pointer(uint32_t *base, uint32_t index);
uint32_t *select_larger(uint32_t *a, uint32_t *b);
void clear_byte_at_202(uint8_t *object);
void set_quad_fields(uint32_t *object, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
uint32_t get_region_base(void);
void set_flag_854(uint8_t *object);
void set_flag_855(uint8_t *object);
uint32_t identity_word(uint32_t value);
void clear_record_fields(uint32_t *record);
void clear_six_fields(uint32_t *record);
void set_four_offsets(uint32_t *object, uint32_t value);
void clear_first_word(uint32_t *object);
void clear_byte_84(uint8_t *object);
void clear_byte_18(uint8_t *object);
void clear_three_halfwords(uint32_t *object);
void clear_four_words(uint32_t *object);
void store_indexed_value(uint32_t *object, uint32_t index, const uint32_t *value);
int has_valid_attachment(uint32_t *object);
uint32_t get_locked_field_5c(uint32_t *object);
uint32_t set_field_and_confirm(uint32_t *object, uint32_t value);
void clear_indexed_slot_138(uint32_t *object, uint32_t index);
void copy_field_180_to_184(uint32_t *object);
void clear_indexed_slot_128(uint32_t *object, uint32_t index);
void build_state_record(uint32_t *object, uint32_t field_20, uint32_t field_28, const uint32_t *values);
void clear_byte_49(uint8_t *object);
void noop_return(void);
void clear_byte_16c(uint8_t *object);
void clear_four_words_and_byte(uint32_t *object);
uint32_t *detach_handle_references(uint32_t *object);
void set_flag_1fd(uint8_t *object);
uint32_t get_indexed_record_address(uint32_t base, uint32_t index);
int is_field_20ac_zero(const uint32_t *object);
void set_first_word_one(uint32_t *object);
uint32_t get_thread_field_5c(void);
uint32_t get_indexed_word_18(const uint32_t *object, uint32_t index);
uint32_t compute_record_offset(uint32_t base, uint32_t row, uint32_t column);
void set_bit_in_field(uint8_t *object, uint32_t bit);
void clear_word_28(uint32_t *object);
void clear_pair_38(uint32_t *object);
void initialize_status_record(uint32_t *record);
void clear_triple_38(uint32_t *object);
void set_pair_8_5c(uint32_t *object, uint32_t a, uint32_t b);
void clear_status_block(uint32_t *block);
uint32_t get_nested_field_18(uint32_t *object);
uint32_t get_field_14_offset_658(const uint32_t *object);
void clear_word_20_and_pointed(uint32_t *object);
uint32_t get_indexed_pointed_field(uint32_t *object, uint32_t offset);
uint32_t get_pointed_field_48(const uint32_t *object);
void clear_byte_4c(uint8_t *object);
void clear_record_10(uint8_t *object);
void clear_word_14(uint32_t *object);
void clear_byte_190(uint8_t *object);
void clear_pointed_word_20(uint32_t *object);
void set_byte_98(uint8_t *object);
void set_byte_and_mark_dirty(uint8_t *object, uint8_t value);
int is_double_match(const uint32_t *object, uint32_t field_c, uint32_t field_64);
void invalidate_range_fields(uint32_t *object);
void clear_pair_c_8(uint32_t *object);
void clear_record_4c(uint32_t *object);
void clear_sub_record(uint32_t *parent, uint16_t *sub);
uint32_t get_conditional_field_21c(const uint32_t *object);
int has_pointed_field_44(const uint32_t *object);
uint32_t get_double_pointed_field_8(const uint32_t *object);
uint32_t passthrough_word(uint32_t value);
uint32_t mark_if_type_102(uint32_t *object);
void set_bytes_ff(uint8_t *dest);
uint32_t clear_word_21c_and_confirm(uint32_t *object);
void clear_byte_2c_and_word_20(uint8_t *object);
void noop_b(void);
void noop_c(void);
void noop_d(void);
uint64_t multiply_accumulate_64(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
void clear_byte_f7_and_mask(uint32_t *object);
void clear_byte_f7(uint32_t *object);
uint32_t set_field_if_mask_60000(uint32_t *object);
uint32_t initialize_channel_record(uint32_t *record, uint32_t handle, uint32_t value, uint32_t extra);
void set_field_4(uint32_t *object, uint32_t value);
void set_halfword_c_100(uint8_t *object);
void clear_quad_words(uint32_t *object);
void set_fields_18_14_with_null_flag(uint32_t *object, uint32_t a, uint32_t b);
void set_field_138_if_nonzero(uint32_t *object, uint32_t value);
uint32_t pop_field_244(uint32_t *object, uint32_t *out);
uint32_t pop_field_278(uint32_t *object, uint32_t *out);
void set_field_110_and_clear(uint32_t *object, uint32_t value);
void store_pointed_100(uint32_t *object, const uint32_t *value);
void store_pointed_104(uint32_t *object, const uint32_t *value);
void noop_e(void);
void scale_pair_by_field_c(float *object, float *target);
uint32_t get_field_1c_or_pointed(const uint32_t *object);
void initialize_state_block(uint8_t *object);
void store_pointed_68_24(uint32_t *object, const uint32_t *value);
uint32_t advance_state_byte_19(uint8_t *object);
int8_t advance_state_byte_4d(uint8_t *object);
uint16_t swap_halfword_34(uint8_t *object, uint16_t value);
uint16_t swap_halfword_36_bit0(uint8_t *object, uint16_t value);
int32_t swap_byte_38(uint8_t *object, uint8_t value);
void clear_byte_4(uint8_t *object);
void clear_word_0_and_set_c(uint32_t *object, uint16_t *target, uint16_t value);
void clear_record_with_byte_3(uint32_t *record);
void clear_word_field_4(uint32_t *object);
void clear_byte_pair_4_5(uint8_t *object);
void set_byte_field_1438(uint8_t *object, uint8_t value);
void set_word_fields_26c_270(uint32_t *object, uint32_t a, uint32_t b);
void clear_word_b0(uint32_t *object);
void clear_flag_bits(uint32_t *object, uint32_t bit);
void clear_fields_40_44(uint32_t *object);
void set_word_and_halfword(uint32_t *object, uint32_t word, uint16_t half);
void set_halfword_8_and_byte_10(uint8_t *object, uint16_t half);
void clear_word_60_64(uint32_t *object);
void clear_fields_6c_70(uint32_t *object);
void clear_word_a8(uint32_t *object);
void clear_word_3c(uint32_t *object);
void clear_word_40(uint32_t *object);
void set_indexed_byte_d4(uint8_t *object, uint8_t value);
void copy_fields_8_c(uint32_t *object);
void set_word_1000_and_byte_1(uint32_t *object);
void set_first_word_1(uint32_t *object);
void store_bytes_split(uint8_t *dest, uint32_t value);
void store_indexed_184(uint32_t *object, uint32_t index, uint32_t value);
void clear_word_field_4_b(uint32_t *object);
void clear_pair_words(uint32_t *object);
void set_first_word_1_b(uint32_t *object);
uint32_t test_bit_2(const uint8_t *object);
void clear_byte_179(uint8_t *object);
void toggle_byte_1(uint8_t *object);
void clear_bytes_78_80(uint8_t *object);
void set_pair_1c_20(uint32_t *object, uint32_t a, uint32_t b);
void advance_list_node(uint32_t *node);
void swap_head_pointer(uint32_t *object, uint32_t *node);
void set_byte_17_if_different(uint8_t *object, uint8_t value);
void clear_fields_1a0(uint32_t *object);
void clear_six_words_and_byte(uint32_t *object);
uint32_t compute_stride_1b8(uint32_t index);
uint32_t compute_stride_60(uint32_t index);
uint8_t get_pointed_byte_14(const uint32_t *object, uint32_t offset);
uint32_t get_constant_23(void);
uint32_t get_halfword_38_masked(const uint32_t *object);
uint16_t byte_swap_halfword(uint16_t value);
void copy_field_8_to_4(uint32_t *object);
void store_pair_10_14(uint32_t *object, const uint32_t *value);
void clear_byte_and_words(uint8_t *object);
void clear_byte_field_4(uint8_t *object);
uint32_t get_indexed_halfword_address(uint32_t object, uint32_t index);
int has_flag_and_subobject(const uint32_t *object);
void noop_l(void);
void noop_m(void);
void clear_byte_358(uint8_t *object);
void clear_record_4_8(uint8_t *object);
void clear_word_18(uint32_t *object);
void clear_word_8(uint32_t *object);
void clear_word_4(uint32_t *object);
void clear_word_250(uint32_t *object);
uint32_t set_byte_14_if_nonzero(uint32_t *record, uint32_t *sub);
void set_byte_f7_to_1(uint32_t *object);
void set_byte_f7_to_fa(uint32_t *object);
void set_byte_90_and_91(uint8_t *object, uint8_t a, uint8_t b);
void advance_byte_by_two(uint8_t *object);
void set_byte_4_and_word_8(uint8_t *object, uint8_t a, uint32_t b);
void clear_byte_and_four_words(uint8_t *object);
uint32_t initialize_pair_record(uint8_t *record, uint32_t value);
uint32_t get_word_b08_offset_4c(const uint32_t *object);
void noop_o(void);
void noop_p(void);
void noop_q(void);
void noop_r(void);
uint16_t get_pointed_halfword_22(const uint32_t *object);
int32_t get_float_as_int_8c(const uint32_t *object);
void store_triple_5c(uint32_t *object, const uint32_t *value);
void store_triple_50(uint32_t *object, const uint32_t *value);
void store_triple_44(uint32_t *object, const uint32_t *value);
uint32_t test_low_bit(const uint8_t *object);
uint32_t get_indexed_entry_by_byte(uint32_t *object, uint32_t index);
void set_high_bitset_bit(uint32_t *bitset, uint32_t bit);
void clear_high_bitset_bit(uint32_t *bitset, uint32_t bit);
void set_quad_2e0(uint32_t *object, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
int32_t get_signed_byte_148(const uint8_t *object);
uint32_t get_indexed_record_a0(const uint32_t *object, uint32_t index);
void noop_s(void);
uint32_t get_indexed_field_10c(uint32_t *object, uint32_t index);
uint32_t get_low_bit_3c(const uint8_t *object);
uint32_t get_nested_table_word(const uint32_t *object);
void noop_t(void);
uint32_t allocate_from_arena(uint32_t *object, uint32_t size);
void set_pair_bc8(uint32_t *object, uint32_t a, uint32_t b);
void copy_pair_with_halfword(uint32_t *dest, const uint32_t *src);
void copy_pair_with_byte(uint32_t *dest, const uint32_t *src);
void clear_word_18_b(uint32_t *object);
void clear_eight_words(uint32_t *object);
void clear_word_4_and_halfword_8(uint32_t *object);
void clear_word_and_halfword_1(uint32_t *object);
void set_byte_10_1(uint8_t *object);
void clear_byte_pair_1_2(uint8_t *object);
void clear_first_word_c(uint32_t *object);
void set_word_1b8_if_different(uint32_t *object, uint32_t value);
void set_pointed_word_10_and_clear(uint32_t *object, uint32_t *sub, uint32_t value);
void clear_word_and_byte_1(uint32_t *object);
void set_self_link_4(uint32_t *object);
void clear_byte_4_b(uint8_t *object);
void add_to_word_184(uint32_t *object, uint32_t value);
void set_byte_1ac6_ff(uint8_t *object);
void clear_word_pair_and_halfword(uint32_t *object);
void store_quad_58(uint32_t *object, const uint32_t *value);
uint32_t check_pair_480_481(const uint8_t *object);
uint32_t check_idle_1fd_201(const uint8_t *object);
void clear_record_with_list_head(uint32_t *record);
uint32_t get_indexed_pointed_word(uint32_t *object, uint32_t index);
void noop_w(void);
void noop_x(void);
void noop_y(void);
void noop_z(void);
uint32_t is_decimal_digit(uint32_t value);
void copy_field_c_to_14(uint32_t *object);
void clear_pair_0_1(uint32_t *object);
void set_word_3c_offset_8(uint32_t *object, uint32_t value);
void set_word_38_offset_8(uint32_t *object, uint32_t value);
void clear_triple_0(uint32_t *object);
void set_byte_2c_if_different(uint8_t *object, uint8_t value);
void set_byte_2d_if_different(uint8_t *object, uint8_t value);
void set_byte_15_1_and_clear_17(uint8_t *object);
void set_byte_83(uint8_t *object, uint8_t value);
void set_byte_f4(uint8_t *object, uint8_t value);
void set_indexed_halfword_10c(uint8_t *object, uint32_t index, uint16_t value);
void set_byte_f0(uint8_t *object, uint8_t value);
void set_pair_8c_90(uint32_t *object, uint32_t a, uint32_t b);
void add_to_word_16c(uint32_t *object, uint32_t value);
void or_word_48_c400(uint32_t *object);
void set_word_4(uint32_t *object, uint32_t value);
void increment_word_1c(uint32_t *object);
void set_pair_14_6c(uint32_t *object, uint32_t a, uint32_t b);
void clear_halfwords_a0_a2(uint8_t *object);
void clear_first_word_d(uint32_t *object);
void noop_aa(void);
void noop_ab(void);
void noop_ac(void);
void noop_ad(void);
void clear_word_0_e(uint32_t *object);
void clear_word_0_f(uint32_t *object);
void set_byte_1621_1(uint8_t *object);
void set_triple_halfword_pairs(uint8_t *object, uint16_t a, uint16_t b, uint16_t c);
void clear_byte_1d08(uint8_t *object);
void clear_byte_2e05(uint8_t *object);
void clear_pair_4_8(uint32_t *object);
void and_word_4_fffd(uint32_t *object);
void set_byte_14_10(uint8_t *object);
void set_byte_970_1(uint8_t *object);
void clear_byte_f88(uint8_t *object);
void set_byte_f88_1(uint8_t *object);
void set_byte_150e(uint8_t *object, uint8_t value);
void set_byte_150d(uint8_t *object, uint8_t value);
void clear_byte_428(uint8_t *object);
void clear_word_3e4(uint32_t *object);
void set_byte_200_1(uint8_t *object);
void set_word_4_b(uint32_t *object, uint32_t value);
void clear_halfword_58(uint8_t *object);
void clear_pair_368_36c(uint32_t *object);
void set_halfword_c_108(uint8_t *object);
void clear_byte_589(uint8_t *object);
void copy_byte_1b31_to_1b30(uint8_t *object);
void set_byte_15c5_if_set(uint8_t *object);
void set_byte_24cd_if_set(uint8_t *object);
void clear_byte_4_and_mask_e4(uint8_t *object);
void clear_record_3b303c(uint32_t *record);
uint32_t get_byte_5_if_state_1(const uint8_t *object);
void noop_ae(void);
void noop_af(void);uint32_t get_constant_10(void);
uint32_t get_constant_4(void);
uint32_t get_constant_8(void);
void noop_bd(void);
void noop_be(void);
void noop_bf(void);
void noop_c0(void);
uint32_t get_indexed_field_10c_b(uint32_t *object, uint32_t index);
uint32_t get_low_bit_3c_b(const uint8_t *object);
uint32_t get_nested_word_8(const uint32_t *object);
void noop_c1(void);
uint32_t add_field_3c(uint32_t *object);
uint32_t add_field_2c(uint32_t *object);
uint32_t add_field_c(uint32_t *object);
uint32_t add_field_1c(uint32_t *object);
uint32_t add_field_14(uint32_t *object);
uint32_t add_field_10(uint32_t *object);
uint32_t add_field_4(uint32_t *object);
uint32_t add_field_8(uint32_t *object);
void noop_c3(void);
void noop_c4(void);
void noop_c5(void);
void noop_c6(void);
uint32_t clear_byte_24d_and_confirm(uint8_t *object);
void clear_pair_54_58(uint32_t *object);
void set_byte_2a_1(uint8_t *object);
void copy_fields_4_8_to_138(uint32_t *object);
void initialize_link_record(uint8_t *record);
void clear_byte_5_to_2(uint8_t *object);
uint32_t copy_record_if_different(uint32_t *dest, const uint32_t *src);
int is_not_type_8579(uint32_t value);
void initialize_state_record(uint32_t *record);
void set_self_link_2(uint32_t *object);
void noop_c7(void);
void noop_c8(void);
void initialize_link_record_full(uint32_t *record);
void initialize_tagged_record(uint32_t *record, uint32_t tag);
void initialize_tagged_record_b(uint32_t *record, uint32_t tag);
void set_pair_1cc_1cd_if_different(uint8_t *object, uint8_t a, uint8_t b);
uint32_t get_state_1a_mapped(const uint8_t *object);
uint32_t get_state_4e_mapped(const uint8_t *object);
void noop_c9(void);
void noop_ca(void);
void clear_byte_5c(uint8_t *object);
void clear_word_0_and_byte_3_4(uint32_t *object);
void clear_word_0_and_byte_10_11(uint32_t *object);
void clear_word_0_1_and_halfword_2(uint32_t *object);
void set_byte_14_if_0x102(uint8_t *object);
void push_tagged_818(uint32_t *object, uint32_t value);
void push_tagged_c(uint32_t *object, uint32_t value);
void set_byte_290_if_0x102(uint8_t *object);
void noop_cb(void);
void clear_word_14_and_set_c(uint32_t *object, uint32_t value);
void clear_state_record_970c(uint32_t *record);
void initialize_state_record_788c(uint32_t *record);
void set_byte_4_or_bit(uint8_t *object, uint32_t bit);
void set_pointed_word_3c(uint32_t *object, uint32_t value);
void set_byte_2_and_flag(uint8_t *object, uint32_t bit);
void clear_byte_49a_and_set_234(uint8_t *object);
void copy_state_and_clear(uint8_t *dest, const uint8_t *src);
void clear_word_14_and_set_word_c(uint32_t *object, uint32_t value);
uint32_t find_offset_for_type_6800(const uint8_t *object);
uint32_t get_field_after_type_6800(const uint8_t *object);
uint32_t get_record_entry_field(uint32_t *record, uint32_t index);
void store_indexed_entry_pointer(uint32_t *out, uint32_t *object, uint32_t index);
uint32_t map_mode_to_state(uint32_t object);
uint32_t check_mode_flag(uint32_t object);
void reset_counter_and_copy(uint32_t *record);
void init_record_738(uint32_t *object);
uint32_t check_nested_chain_10_90_8(const uint32_t *object);
void set_byte_c4d_if_valid(uint8_t *object);
uint32_t check_nested_chain_10_90_8_b(const uint32_t *object);
void unlink_list_node(uint32_t *node);
uint32_t append_if_room(uint32_t *object, uint32_t value);
void move_list_entry(uint32_t *list, uint32_t *entry);
void write_be32(uint8_t *object, uint32_t value, uint32_t offset);
uint64_t shift_right_64(uint32_t low, uint32_t high, uint32_t shift);
void allocate_and_clear(uint32_t object, uint32_t size);
void init_record_fields(uint32_t *record, const uint32_t *src, uint32_t value, uint8_t flag_a, uint8_t flag_b);
uint32_t count_list_entries(uint32_t *object);
int32_t wrap_index(int32_t *object, int32_t value);
uint32_t set_halfword_6c_if_valid(uint8_t *object);
void unlink_circular_entry(uint32_t *object);
uint32_t check_nested_chain_10_90_8_c(const uint32_t *object);
int32_t clamp_toward_target(int32_t value, int32_t target, int32_t step);
void copy_two_halfwords(uint8_t *dest, const uint8_t *src);
uint32_t classify_value_bits(uint32_t value);
uint32_t get_indexed_nested_table_entry(uint32_t *object, uint32_t index);
uint32_t check_mode_31d_10(uint32_t object);
void copy_and_scale_vector(float *dest, const float *src, const uint8_t *object);
void remove_counted_list_entry(uint32_t *owner, uint32_t *node);
void insert_counted_list_entry(uint32_t *owner, uint32_t *at, uint32_t *node);
void init_record_by_mode(uint8_t *record);
uint32_t test_flag_bit_array(const uint8_t *object, uint32_t bit);
uint32_t get_field_by_code(const uint8_t *object, uint32_t code);
char *find_substring(char *haystack, const char *needle);
int32_t finalize_counter_and_flag(uint8_t *object);
uint32_t *get_or_init_singleton(void);
uint64_t shift_left_64(uint32_t low, uint32_t high, uint32_t shift);
int32_t clear_list_and_get_base(uint32_t *object);
uint32_t init_range_aligned(uint32_t *object, uint32_t start, uint32_t size);
void init_record_offsets(uint32_t *record, uint32_t a, uint32_t b, uint32_t c, uint32_t base, uint32_t d);
uint32_t map_type_code(uint32_t code);
void call_flag_if_nested_nonzero(uint32_t *object);
void propagate_flag_change(uint8_t *object);
void clear_indexed_word_54(uint32_t *object, uint32_t index);
uint32_t reset_state_fields(uint8_t *object);
uint32_t set_halfword_c_for_range(uint8_t *object);
int32_t compare_wide_string_bounded(const uint16_t *a, const uint16_t *b, int32_t count);
uint32_t get_indexed_word_base(const uint32_t *object, uint32_t index);
void svc_38_store(uint32_t *object, uint32_t value);
void svc_21_store(uint32_t *object, uint32_t value);
void clear_four_words_b(uint32_t *object);
void clear_record_13(uint32_t *object);
void clear_two_bytes(uint8_t *object);
void init_pointer_pairs_500(uint32_t *object);
void svc_2d_store(uint32_t *object, uint32_t value);
uint32_t svc_25_store(uint32_t *object, uint32_t value, uint32_t unused_a, uint32_t unused_b, uint32_t result);
uint32_t return_minus_one(void);
uint32_t return_minus_one_b(void);
void svc_29_store_pair(uint32_t *object, uint32_t a, uint32_t b);
uint32_t check_word_c_nonzero(const uint32_t *object);
uint32_t check_words_not_fd(const uint32_t *object);
uint32_t get_pointed_word_8(const uint32_t *object);
uint32_t get_masked_entry_5c(const uint32_t *object, uint32_t index);
void clear_word_14_only(uint32_t *object);
uint32_t get_self_offset_10d(uint32_t *object);
int32_t get_indexed_halfword_d4(const uint8_t *object, uint32_t index);
void noop_g(void);
void copy_nine_words(uint32_t *dest, const uint32_t *src);
void copy_and_offset_vector(float *dest, const float *offset, const float *src);
void svc_b_store(uint32_t *object, uint32_t value);
uint32_t check_word_b04_zero(const uint32_t *object);
uint32_t get_nested_word_8e8_14(const uint32_t *object);
void mask_nested_word_48(uint32_t *object);
void init_record_1b34(uint8_t *object);
uint32_t check_word_8_nonzero(const uint32_t *object);
void store_joy_and_flag_db(uint32_t *object, uint8_t value);
void store_joy_and_flag_da(uint32_t *object, uint8_t value);
void store_joy_and_flag_d9(uint32_t *object, uint8_t value);
void store_joy_and_flag_d8(uint32_t *object, uint8_t value);
void store_joy_and_flag_e3(uint32_t *object, uint8_t value);
void store_joy_and_flag_e2(uint32_t *object, uint8_t value);
void store_joy_and_flag_e1(uint32_t *object, uint8_t value);
void store_joy_and_flag_e0(uint32_t *object, uint8_t value);
void store_joy_and_flag_df(uint32_t *object, uint8_t value);
void store_joy_and_flag_de(uint32_t *object, uint8_t value);
void store_joy_and_flag_dd(uint32_t *object, uint8_t value);
void store_joy_and_flag_dc(uint32_t *object, uint8_t value);
void store_joy_and_flag_d3(uint32_t *object, uint8_t value);
void store_joy_and_flag_d2(uint32_t *object, uint8_t value);
void store_joy_and_flag_d1(uint32_t *object, uint8_t value);
void store_joy_and_flag_d0(uint32_t *object, uint8_t value);
void store_joy_and_flag_d6(uint32_t *object, uint8_t value);
void store_joy_and_flag_d5(uint32_t *object, uint8_t value);
void store_joy_and_flag_d4(uint32_t *object, uint8_t value);
uint32_t map_code_to_value(uint32_t code);
void mask_cc_fields(uint32_t *object);
void or_cc_fields(uint32_t *object);
void copy_vector_200(uint32_t *object, const uint32_t *src, uint32_t extra);
void clear_word_c_and_38(uint32_t *object);
void init_record_e_14(uint8_t *object);
void init_record_22_24(uint8_t *object);
void store_two_words_108(uint8_t *object, const uint32_t *src);
void increment_word_18(uint32_t *object);
void set_byte_a28(uint32_t *object, int32_t value);
uint32_t get_if_byte_4_is_5(const uint32_t *object);
void set_word_a18(uint32_t *object);
uint32_t svc_23_release_0(uint32_t *object);
uint32_t svc_23_release_1(uint32_t *object);
uint32_t svc_23_release_2(uint32_t *object);
uint32_t svc_23_release_3(uint32_t *object);
int32_t normalize_index(int32_t index);
void mask_byte_1ea(uint8_t *object, uint8_t value);
void push_word_1c(uint32_t *object, uint32_t value);
void set_byte_1b5_if_different(uint8_t *object, uint8_t value);
float get_word_114_as_float(const uint8_t *object);
int32_t get_byte_at_8_bounded(const uint8_t *object, uint32_t index);
uint32_t check_byte_1508_is_2(const uint8_t *object);
uint32_t check_byte_1508_is_2_b(const uint8_t *object);
void clear_byte_2367(uint8_t *object);
uint32_t check_byte_45b0_is_5(const uint8_t *object);
uint32_t identity_word_b(uint32_t value);
void reset_counters_30(uint32_t *object);
void push_by_mode(uint32_t *object);
void copy_vector_200_b(uint32_t *object, const uint32_t *src, uint32_t extra, uint32_t tag);
uint32_t identity_word_c(uint32_t value);
void push_front_node(uint32_t *head, uint32_t *node);
uint32_t check_byte_1aa2_under_2(const uint8_t *object);
void increment_word_258(uint8_t *object);
void init_record_0_10(uint8_t *object);
int32_t get_byte_11d1(const uint8_t *object);
uint32_t add_d4_entry(const uint32_t *object, uint32_t index);
uint32_t add_word_c_indexed(const uint32_t *object, uint32_t index);
uint32_t add_word_4_by_halfword(const uint32_t *object, uint32_t index);
uint16_t get_chained_halfword_2(const uint32_t *object, uint32_t index, uint32_t sub);
uint32_t add_word_8_indexed(const uint32_t *object, uint32_t index);
uint32_t get_pointed_word_0(const uint32_t *object);
uint8_t get_pointed_byte_5(const uint32_t *object);
int32_t get_pointed_halfword_6(const uint32_t *object);
uint32_t check_pair_18_19(const uint8_t *object);
uint32_t map_to_012(uint32_t value);
uint32_t check_byte_254_is_1(const uint8_t *object);
uint32_t check_nested_word_44(const uint32_t *object);
uint32_t add_offset_1c(uint32_t object, uint32_t offset);
uint32_t return_ten(void);
uint8_t get_byte_6f_flag(const uint32_t *object);
uint32_t get_word_e4_low(const uint32_t *object);
void noop_h(void);
void store_word_60_if_mode_1_3(uint32_t *out, const uint8_t *object);
uint32_t check_mode_20_byte_55_1(const uint8_t *object);
uint32_t add_word_4(uint32_t *object);
uint32_t add_word_4_b(uint32_t *object);
uint32_t get_pointed_word_0_b(const uint32_t *object);
uint32_t get_if_halfword_4_is_300(uint16_t *object);
uint32_t add_word_34(uint32_t *object);
uint32_t get_if_halfword_4_is_101(uint32_t *object);
uint32_t get_if_halfword_4_is_101_b(uint32_t *object);
uint32_t get_if_pair_18_1c(uint32_t *object);
uint32_t get_if_halfword_0_is_220c(uint16_t *object);
uint32_t map_halfword_220c(uint16_t *object);
uint32_t get_pointed_word_0_c(const uint8_t *object);
uint32_t get_nested_68_8(const uint32_t *object);
uint32_t check_pointed_byte_4_zero(const uint32_t *object);
uint8_t get_byte_50_or_1(const uint32_t *object);
uint32_t check_byte_51_word_84(const uint8_t *object);
uint32_t get_if_word_4_is_21f(uint32_t *object);
uint32_t add_word_c(uint32_t *object);
uint32_t add_word_4_offset(const uint32_t *object, uint32_t offset);
uint32_t get_indexed_entry_14(uint32_t *object, uint32_t index);
uint32_t add_nested_8_16c(uint32_t *object);
void store_deref_offset_10(uint32_t *out, uint32_t *object, uint32_t index);
uint32_t add_8_180_10(uint32_t *object, uint32_t a, uint32_t b);
void store_8_180_18_130(uint32_t *out, uint32_t *object, uint32_t a, uint32_t b);
uint32_t get_nested_8_180_17c(uint32_t *object, uint32_t a, uint32_t b);
uint32_t copy_4c_from_pointed(uint8_t *dest, const uint32_t *object);
uint32_t check_pointed_word_68(const uint32_t *object);
uint32_t get_pointed_byte_4_zero(const uint32_t *object);
void clear_byte_end(uint32_t *object);
int32_t get_byte_15bc(const uint8_t *object);
int32_t get_byte_15b8_indexed(const uint8_t *object, uint32_t index);
uint32_t check_31e_328(const uint8_t *object);
uint32_t check_315_314(const uint8_t *object);
uint32_t map_flags_18(const uint32_t *object);
uint8_t get_byte_6_low(const uint8_t *object);
uint8_t get_byte_6_high(const uint8_t *object);
uint8_t get_byte_49f0(const uint8_t *object, uint32_t index);
uint32_t get_word_18_if_byte_1(const uint8_t *object);
int32_t get_byte_118(const uint8_t *object);
uint32_t get_word_4(const uint32_t *object);
uint16_t get_halfword_2_chained(const uint32_t *object);
uint16_t get_halfword_28_chained(const uint32_t *object);
uint32_t get_word_8_chained(const uint32_t *object);
uint32_t get_word_c_chained(const uint32_t *object);
uint32_t get_word_14_chained(const uint32_t *object);
uint32_t add_38_110(const uint32_t *object, uint32_t index);
int32_t get_byte_1b3c(const uint8_t *object);
void clear_two_words(uint32_t *object);
void fill_pair_ff(uint32_t *object, uint32_t value);
void increment_word_1c_b(uint32_t *object);
void push_word_1c_b(uint32_t *object, uint32_t value);
uint32_t return_16(void);
uint32_t check_mask_18400(uint32_t value);
int32_t locked_get_byte_10(uint8_t *object);
int32_t locked_get_byte_11(uint8_t *object);
int32_t locked_get_byte_1c(uint8_t *object);
int32_t locked_get_byte_14(uint8_t *object);
void reset_counters_4(uint32_t *object);
void init_record_4_1c(uint8_t *object);
void set_bytes_94_98(uint32_t *object, uint8_t value);
void add_pointed_byte_d(uint8_t *object, uint8_t value);
void set_pointed_byte_17(uint8_t *object, uint8_t value);
void scale_word_8c(uint8_t *object);
uint32_t check_word_40_is_1(const uint32_t *object);
uint32_t get_word_40(const uint32_t *object);
uint32_t test_byte_6c_bit(const uint8_t *object, uint32_t bit);
void set_word_pair(uint32_t *object, uint32_t value);
void copy_eleven_words(uint32_t *dest, const uint32_t *src);
uint32_t add_8_180_4(const uint32_t *object, uint32_t a, uint32_t b);
void set_word_30_if_diff(uint8_t *object, float value);
uint32_t get_if_halfword_10_is_101(uint32_t *object);
uint32_t clamp_to_3(uint32_t value);
void call_add_field_4_if_set(uint32_t *object);
void remove_list_entry_b(uint32_t *count, uint32_t *node);
void insert_list_after_b(uint32_t *count, uint32_t *node);
void set_word_50_byte_9d(uint8_t *object, uint8_t value, uint32_t word);
void set_byte_60_ff_if_lower(uint8_t *object, uint32_t index);
void set_byte_77_if_match(uint8_t *object, uint8_t value);
void store_pair_4_8(uint32_t *object, uint32_t a, uint32_t b);
void copy_record_c(uint8_t *dest, const uint8_t *src);
void store_pair_80_84(uint32_t *object, const uint32_t *src);
void store_pair_54_58(uint32_t *object, uint32_t a, uint32_t b);
void store_pair_8_c(uint32_t *object, const uint32_t *src);
void clear_record_8_10(uint8_t *object);
void store_word_4_byte_1c(uint32_t *object, uint32_t value);
void store_word_14_if_valid(uint32_t *object, uint32_t value);
void set_halfword_1e_mask(uint8_t *object, uint16_t value);
void set_halfword_1c(uint8_t *object, uint16_t value);
void set_byte_1b7_if_diff(uint8_t *object, uint8_t value);
void init_record_1c_28(uint8_t *object);
void init_record_90(uint8_t *object);
uint32_t check_word_4_nonzero(const uint32_t *object);
uint32_t check_byte_8_is_0_or_7(const uint8_t *object);
uint32_t check_byte_28_is_0_or_8(const uint8_t *object);
void copy_or_clear_80(uint8_t *object, const uint8_t *src);
void push_word_fa8(uint32_t *object, uint32_t value);
void set_byte_d6_bit(uint8_t *object, uint32_t bit);
int32_t get_byte_cff_if_cfe(const uint8_t *object);
uint32_t check_1ff_1a4(const uint8_t *object);
uint32_t check_1ff_178(const uint8_t *object);
void clear_byte_202(uint8_t *object);
void add_158_15c(uint32_t *object);
void or_byte_9894(uint8_t *object);
void store_four_halfwords_114(uint8_t *object, uint16_t a, uint16_t b, uint16_t c, uint16_t d);
void toggle_byte_5e8(uint8_t *object);
void store_pair_594_1720(uint32_t *object, uint32_t a, uint32_t b);
uint32_t set_state_2_if_flag(uint8_t *object);
uint32_t set_state_10_if_flag(uint8_t *object);
uint32_t set_state_2_if_flag_b(uint8_t *object);
uint32_t set_state_8_if_halfword_96_zero(uint8_t *object);
void or_byte_3eff_set_3f05_4(uint8_t *object);
void and_byte_3eff_set_3f05_2(uint8_t *object);
void or_byte_3eff_2_set_3f05_4(uint8_t *object);
void and_byte_3eff_fd_set_3f05_2(uint8_t *object);
void store_word_4(uint32_t *object, uint32_t value);
void store_word_4_b(uint32_t *object, uint32_t value);
void store_word_4_c(uint32_t *object, uint32_t value);
void reset_record_10(uint8_t *object);
void store_word_1_word_2_len(uint32_t *object, const uint16_t *string);
uint32_t count_bits_and_index(const uint32_t *table, uint32_t *out, uint32_t slot);
uint32_t set_state_5_if_flag(uint8_t *object);
uint32_t set_state_15_if_flag(uint8_t *object);
void split_four_words(const uint32_t *object, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);
uint32_t get_config_byte_14_1(uint32_t *object, uint32_t value);
uint32_t get_config_byte_14_2(uint32_t *object, uint32_t value);
uint32_t get_config_byte_14_0(uint32_t *object, uint32_t value);
uint32_t get_config_word_14_2(uint32_t *object, uint32_t value);
uint32_t get_config_word_14_2_high(uint32_t *object, uint32_t value);
int32_t get_config_signed_byte_14_0(uint32_t *object, uint32_t value);
uint32_t get_config_byte_4_0(uint32_t *object, uint32_t value);
uint32_t get_config_byte_4_2(uint32_t *object, uint32_t value);
uint32_t get_config_byte_4_1_60(uint32_t *object, uint32_t value);
uint32_t get_config_word_4_1(uint32_t *object, uint32_t value);
uint32_t get_config_byte_8_0(uint32_t *object, uint32_t value);
uint32_t get_config_word_8_1(uint32_t *object, uint32_t value);
uint32_t get_config_word_c_0(uint32_t *object, uint32_t value);
uint32_t get_config_byte_c_1(uint32_t *object, uint32_t value);
uint32_t get_config_word_18_2(uint32_t *object, uint32_t value);
uint32_t get_config_word_18_1(uint32_t *object, uint32_t value);
uint32_t get_config_byte_18_0(uint32_t *object, uint32_t value);
uint32_t get_config_offset_14_8(uint32_t *object, uint32_t value);
uint32_t get_config_byte_4_0_3c(uint32_t *object, uint32_t value);
uint32_t get_config_byte_4_2_b(uint32_t *object, uint32_t value);
uint32_t get_config_byte_4_1_7f(uint32_t *object, uint32_t value);
uint32_t get_config_byte_14_1_or_0(uint32_t *object, uint32_t value);
uint32_t get_config_word_14_1_high(uint32_t *object, uint32_t value);
uint32_t get_config_bit_14_17(uint32_t *object, uint32_t value);
uint32_t get_config_word_14_2_high_b(uint32_t *object, uint32_t value);
uint32_t get_config_word_4_2_high(uint32_t *object, uint32_t value);
uint32_t get_config_word_8_0_high(uint32_t *object, uint32_t value);
uint32_t get_config_word_4_4_high(uint32_t *object, uint32_t value);
uint32_t get_config_flag_4_4(uint32_t *object, uint32_t value);
uint32_t get_config_top_byte_4_4(uint32_t *object, uint32_t value);
void clear_if_byte_8(uint32_t *object);
void clear_if_byte_c(uint32_t *object);
void clear_two_words_b(uint32_t *object);
void init_record_4_14(uint32_t *object, uint32_t a, uint32_t b);
void set_word_38_if_diff(uint8_t *object, float value);
void set_word_34_if_diff(uint8_t *object, float value);
void set_word_28_if_diff(uint8_t *object, float value);
void store_word_108_byte_fe(uint8_t *object, uint32_t word, uint8_t value);
void store_word_28_byte_2c(uint8_t *object, uint32_t word, uint8_t value);
void store_word_indexed_38(uint32_t *object, uint32_t index, uint32_t value);
uint32_t get_indexed_word_94(const uint32_t *object, uint32_t index);
void set_halfword_d4(uint8_t *object, uint32_t index, uint16_t value);
uint32_t get_nested_b08_word(const uint32_t *object);
void set_nested_f7_f8(uint8_t *object, uint8_t value, int32_t mode);
void and_nested_b08_word_48(uint32_t *object);
uint32_t check_nested_b08_halfword_96(const uint32_t *object);
uint32_t set_state_1_if_nested_f3_zero(uint8_t *object);
uint32_t find_tagged_entry(uint8_t *object, uint32_t tag);
void store_8_180_18_e4(uint32_t *out, uint32_t *object, uint32_t a, uint32_t b);
void store_nested_8_180_18_f8(uint32_t *object, uint32_t a, uint32_t b, uint32_t *out);
int32_t get_nested_90_8_4(uint32_t object);
uint32_t get_if_halfword_8_is_101(uint32_t *object);
uint32_t check_tag_4001_exists(uint32_t *object);
uint32_t check_tag_4003_exists(uint32_t *object);
uint32_t get_tag_4000_word_8(uint32_t *object);
uint32_t get_tag_4002_word_4(uint32_t *object);
uint32_t get_tag_4000_word_4(uint32_t *object);
uint32_t get_tag_4001_word_4(uint32_t *object);
uint32_t get_tag_4003_word_4(uint32_t *object);
uint32_t abs_diff_within_wrap(int32_t a, int32_t b, int32_t limit);
uint32_t set_state_3_if_halfword_e_is_2(uint8_t *object);
void set_halfword_41e_4(uint8_t *object);
uint32_t set_state_2_if_halfword_e_not_2(uint8_t *object);
void set_word_24_flag_2b(uint32_t *object, uint32_t value);
uint32_t check_halfword_e_is_2(const uint8_t *object);
void init_record_70(uint8_t *object);
void copy_pair_b08(uint32_t *dest, const uint8_t *src);
uint32_t get_nested_c48_14(const uint32_t *object);
void store_word_254_pair(uint32_t *object, const uint32_t *value);
void advance_and_mark_179(uint8_t *object);
uint32_t get_nested_3c_34_deref(uint32_t *object);
uint32_t get_nested_word_4_plus_4(uint32_t *object);
uint32_t get_word_14c_as_float(const uint8_t *object);
uint32_t check_149_150(const uint8_t *object);
int32_t get_byte_121(const uint8_t *object);
uint32_t add_word_c_indexed_b(const uint32_t *object, uint32_t index);
uint32_t get_indexed_byte_5e8_word_5a8(const uint8_t *object);
uint32_t check_pointed_byte_8c_bit0(const uint32_t *object);
uint32_t get_nested_3c_2c_deref(uint32_t *object);
uint32_t get_nested_3c_1c_deref(uint32_t *object);
void raise_float_to_min(float *value, float input);
void lower_float_to_max(float *value, float input);
uint32_t test_high_bit(const uint32_t *object, uint32_t bit);
void noop_i(void);
void noop_j(void);
void store_word_138_indexed(uint32_t *object, uint32_t index, uint32_t value);
void store_word_130_indexed(uint32_t *object, uint32_t index, uint32_t value);
int32_t find_char_from(const char *string, char target);
uint16_t get_pointed_halfword_word(const uint32_t *object);
void store_triple_a4_mark_b0(uint8_t *object, uint32_t a, uint32_t b, uint32_t c);
uint32_t append_list_tail_170(uint32_t *object, uint32_t *node);
uint32_t check_entry_20_empty(uint32_t *object, uint32_t index);
uint32_t check_byte_14_in_set(const uint8_t *object);
uint32_t check_byte_14_is_b(const uint8_t *object);
void set_byte_150b_if_1508_is_2(uint8_t *object);
void set_byte_150a_if_1508_is_2(uint8_t *object);
void set_halfword_4_bit(uint8_t *object, uint32_t bit, uint32_t value);
uint32_t get_nested_byte_e8_high(const uint32_t *object);
uint32_t set_state_2_if_word_10_high(uint8_t *object);
void move_word_8_to_c(uint32_t *object);
uint32_t copy_byte_1_halfword_2(uint8_t *object);
uint32_t copy_triple_from_pointed(uint8_t *object);
void clear_pointed_pair_26c(uint32_t *object);
void clear_word_4_only(uint32_t *object);
void set_byte_ea_recursive(uint32_t *object, uint8_t value, uint32_t recurse);
void copy_sixteen_words(uint32_t *dest, const uint32_t *src);
void copy_sixteen_words_b(uint32_t *dest, const uint32_t *src);
void call_each(uint32_t base, uint32_t size, void (*fn)(uint32_t), uint32_t count);
void svc_17_store(uint32_t *object, uint32_t value);
uint32_t swap_byte(uint8_t *object, uint8_t value);
uint32_t check_mask_7_is_6(const uint32_t *object);
uint32_t get_word_18_mask_7(const uint32_t *object);
uint32_t return_word_10(const uint32_t *object);
uint32_t return_word_14(const uint32_t *object);
uint32_t return_word_18(const uint32_t *object);
uint32_t return_word_1c(const uint32_t *object);
void set_byte_6(uint8_t *object, uint8_t value);
void set_byte_5(uint8_t *object, uint8_t value);
#endif

void set_1e_low2(uint32_t *object, uint16_t value);
void set_1e_mid2(uint32_t *object, uint16_t value);
void set_1e_high4(uint32_t *object, int16_t value);
void set_byte_5_and_nested(uint32_t *object, uint8_t value);
void set_1e_bit6(uint32_t *object, int16_t value);

void init_state_18(uint32_t *object);
void clamp_float_min_c8(uint32_t *object, float value);
void set_float_scaled(uint8_t *object, float value);
void init_state_10_1c(uint32_t *object);
void clear_bit_6c(uint32_t *object, uint32_t bit);
void set_indexed_halfword_130(uint32_t *object, int32_t idx1, int32_t idx2, uint16_t value);
void set_indexed_word_f8(uint32_t *object, int32_t idx1, int32_t idx2, const uint32_t *value);
void set_state_168(uint32_t *object, uint32_t a, uint8_t b);
void set_state_154(uint32_t *object, uint32_t a, uint8_t b);
void set_state_118(uint32_t *object, uint32_t a, uint8_t b);
void copy_quad_58(uint32_t *object, uint32_t *dest);
void set_word_14_6c(uint32_t *object, uint32_t value);
uint32_t *get_nested_90_1c_indexed(uint32_t *object, int32_t index);

uint32_t get_nested_table_word_8(uint32_t *object, int32_t index);
uint32_t get_table_word_4(int32_t index);
uint32_t get_table_word_4_b(int32_t index);
uint32_t get_word_1f18_indexed(uint32_t *object, int32_t index);
uint32_t *add_804(uint32_t *object);
void init_pair_4_8(uint32_t *object);
uint32_t clear_nested_c0_halfword_c(uint32_t *object);
uint32_t clear_nested_c4_halfword_c(uint32_t *object);
void insert_list_head(uint32_t *object, uint32_t *node);

void set_halfword_c_to_7(uint32_t *object);
uint32_t set_halfword_c_to_4_if_greater(uint32_t *object, uint32_t threshold);
void set_word_10_to_dat(uint32_t value);
void clear_byte_5c_if_9c4(uint8_t *object);
void init_triple_0_1_2(uint32_t *object);
void set_byte_1d08_if_zero(uint8_t *object);

void push_tagged_818_1(uint32_t *object, uint32_t value);
void push_tagged_818_0(uint32_t *object, uint32_t value);
void push_tagged_c_1(uint32_t *object, uint32_t value);
void push_tagged_c_2(uint32_t *object, uint32_t value);
void push_tagged_c_0(uint32_t *object, uint32_t value);
uint32_t check_byte_1088_and_clear_dat(uint8_t *object);
void set_dat_to_1(void);
void set_dat_to_1_b(void);
void clear_byte_428_and_9_if_8(uint8_t *object);

void clear_state_8_10_14(uint32_t *object);
uint32_t get_byte_880_shift_7(uint32_t *object);
uint32_t get_byte_880_mask_7fff_shift_e(uint32_t *object);
uint32_t check_byte_ff1_is_2(uint8_t *object);
void set_byte_ff1_to_2(uint8_t *object);
void clear_byte_ff1(uint8_t *object);
uint32_t return_dat(void);
void init_byte_4_5(uint32_t *object);
void call_nested_3dc(uint32_t *object);
void call_nested_3e4(uint32_t *object);
void call_nested_3d0(uint32_t *object);

void set_pair_dat(uint32_t a, uint32_t b);
void clear_dat(void);

void increment_word(uint32_t *object);
void set_dat_8(uint32_t value);
void init_pair_0_93(uint32_t *object);
void set_dat_byte_1(void);
uint32_t check_dat_18_mask_7_is_6(void);
void set_dat_18(uint32_t value);
void set_dat_14(uint32_t value);
void set_dat(uint32_t value);
void set_dat_4(uint32_t value);
void set_dat_byte_d(uint8_t value);
uint32_t svc_8_store(uint32_t *object, uint32_t a, uint32_t b, uint32_t c, uint32_t d);
void svc_2b_store(uint32_t *object, uint32_t a, uint32_t b);

void init_list_heads(uint32_t *object);
void init_pair_50_5c(uint32_t *object);
void set_pair_dat_4_8(uint32_t a, uint32_t b);
void set_dat_b(uint32_t value);
uint8_t return_dat_byte(void);
void init_triple_0_1_2_b(uint32_t *object);
uint8_t return_dat_byte_1(void);
void set_dat_byte_1_2(uint8_t value);

uint32_t return_dat_b(void);
void set_dat_byte_8(void);
int32_t return_dat_byte_8(void);
void clear_dat_byte_8(void);
void set_dat_byte_7(void);
int32_t return_dat_byte_7(void);
void clear_dat_byte_7(void);
uint8_t return_dat_byte_3(void);
void set_dat_byte_4(uint8_t value);
void set_dat_byte_3(uint8_t value);
void clear_dat_byte_3(void);
void set_dat_byte_2(uint8_t value);
void clear_dat_byte_2(void);
uint32_t return_dat_10(void);
uint32_t return_dat_c(void);
uint8_t return_dat_byte_5(void);
void set_dat_byte_1_b(void);
void set_byte_4_and_word_0(uint32_t *object, uint8_t value);
void set_dat_c(uint32_t value);
uint32_t return_dat_d(void);
