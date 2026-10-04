#include <assert.h>
#include <stdint.h>
#include <string.h>

void store_runtime_flag(uint8_t *target, uint8_t value);
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
void clear_word_20(uint32_t *object);
void set_word_1d0_and_link(uint32_t *object, uint32_t *node);
void set_byte_pair_481_482(uint8_t *object, uint8_t a, uint8_t b);
void or_halfword_e8_10(uint8_t *object);
void or_word_48_8(uint32_t *object);
uint32_t or_word_48_2_if_nonzero(uint32_t *object, uint32_t value);
uint32_t or_word_48_1_if_nonzero(uint32_t *object, uint32_t value);
void clear_halfword_c(uint8_t *object);
void store_pointed_244_248(uint32_t *object, const uint32_t *value);
void store_pointed_250_254(uint32_t *object, const uint32_t *value);
void store_pointed_25c_260(uint32_t *object, const uint32_t *value);
void store_indexed_d0_80(uint32_t *object, uint32_t index, uint32_t value);
void clear_halfword_bit(uint8_t *object, uint32_t bit);
void set_halfword_bit(uint8_t *object, uint32_t bit);
void set_byte_6_and_mark(uint8_t *object, uint8_t value);
void set_sub_record_pointer(uint32_t *object, uint32_t index);
void append_counted_value(uint32_t *object, uint32_t value);
void noop_q(void);
void clear_word_20(uint32_t *object);
void set_word_1d0_and_link(uint32_t *object, uint32_t *node);
void set_byte_pair_481_482(uint8_t *object, uint8_t a, uint8_t b);
void or_halfword_e8_10(uint8_t *object);
void or_word_48_8(uint32_t *object);
uint32_t or_word_48_2_if_nonzero(uint32_t *object, uint32_t value);
uint32_t or_word_48_1_if_nonzero(uint32_t *object, uint32_t value);
void clear_halfword_c(uint8_t *object);
void store_pointed_244_248(uint32_t *object, const uint32_t *value);
void store_pointed_250_254(uint32_t *object, const uint32_t *value);
void store_pointed_25c_260(uint32_t *object, const uint32_t *value);
void store_indexed_d0_80(uint32_t *object, uint32_t index, uint32_t value);
void clear_halfword_bit(uint8_t *object, uint32_t bit);
void set_halfword_bit(uint8_t *object, uint32_t bit);
void set_byte_6_and_mark(uint8_t *object, uint8_t value);
void set_sub_record_pointer(uint32_t *object, uint32_t index);
void append_counted_value(uint32_t *object, uint32_t value);
void noop_q(void);
void noop_r(void);
void noop_o(void);
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
void noop_af(void);
uint32_t get_constant_10(void);
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
void noop_af(void);
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
uint64_t multiply_accumulate_64(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
void clear_byte_f7_and_mask(uint32_t *object);
void clear_byte_f7(uint32_t *object);
uint32_t set_field_if_mask_60000(uint32_t *object);
uint32_t initialize_channel_record(uint32_t *record, uint32_t handle, uint32_t value, uint32_t extra);
uint32_t find_offset_for_type_6800(const uint8_t *object);
uint32_t get_field_after_type_6800(const uint8_t *object);
uint32_t get_record_entry_field(uint32_t *record, uint32_t index);
void store_indexed_entry_pointer(uint32_t *out, uint32_t *object, uint32_t index);
uint32_t map_mode_to_state(uint32_t object);
uint32_t check_mode_flag(uint32_t object);
void run_batch_e_tests(void);
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
void run_batch_f_tests(void);
void run_batch_g_tests(void);
void run_batch_h_tests(void);
void run_batch_i_tests(void);
void run_batch_j_tests(void);
void run_batch_k_tests(void);
void run_batch_l_tests(void);
void run_batch_m_tests(void);
void run_batch_n_tests(void);
void run_batch_o_tests(void);
void run_batch_p_tests(void);
void run_batch_q_tests(void);
void run_batch_r_tests(void);
void run_batch_s_tests(void);
void run_batch_t_tests(void);
void run_batch_u_tests(void);
void run_batch_v_tests(void);
void run_batch_w_tests(void);
void run_batch_x_tests(void);
void run_batch_y_tests(void);
void run_batch_z_tests(void);
void run_batch_a2_tests(void);
void run_batch_b2_tests(void);

static uint8_t flag_storage;
static uint8_t fill_storage[16];
static uint32_t lock_storage[3];
static uint64_t tick_storage;
static uint32_t list_storage[5];
static uint32_t node_a[2];
static uint32_t node_b[2];
static uint32_t *head_storage;

void run_runtime_tests(void)
{
    flag_storage = 0;
    store_runtime_flag(&flag_storage, 1);
    assert(flag_storage == 1);

    store_runtime_flag(&flag_storage, 0);
    assert(flag_storage == 0);

    store_runtime_flag(&flag_storage, 0xff);
    assert(flag_storage == 0xff);

    void *end = rt_memset(fill_storage, 16, 0x5a);
    assert(end == fill_storage + 16);
    assert(fill_storage[0] == 0x5a);
    assert(fill_storage[15] == 0x5a);
    end = rt_memset(fill_storage, 3, 0);
    assert(end == fill_storage + 3);
    assert(fill_storage[0] == 0);
    assert(fill_storage[2] == 0);
    assert(fill_storage[3] == 0x5a);

    get_system_tick(&tick_storage);
    assert(tick_storage > 0);

    recursive_mutex_lock(lock_storage);
    assert(lock_storage[2] == 1);
    recursive_mutex_lock(lock_storage);
    assert(lock_storage[2] == 2);
    recursive_mutex_unlock(lock_storage);
    assert(lock_storage[2] == 1);
    recursive_mutex_unlock(lock_storage);
    assert(lock_storage[2] == 0);
    assert(lock_storage[1] == 0);
    assert(lock_storage[0] == 0);

    initialize_linked_list(list_storage);
    assert(list_storage[1] == 0);
    assert(list_storage[3] == 0);
    head_storage = node_a;
    node_a[0] = 0;
    node_a[1] = 0;
    list_storage[1] = (uint32_t)(uintptr_t)node_a;
    push_list_front(list_storage, &head_storage, node_b);
    assert(head_storage == node_b);
    assert(node_b[0] == (uint32_t)(uintptr_t)node_a);
    assert(node_a[1] == (uint32_t)(uintptr_t)node_b);
    assert(list_storage[3] == 1);
    list_storage[1] = (uint32_t)(uintptr_t)node_b;
    pop_list_front(list_storage);
    assert(list_storage[3] == 0);
    assert(node_b[0] == 0);
    assert(node_b[1] == 0);

    static uint32_t sentinel[2];
    static uint32_t prev_slot;
    list_storage[3] = 1;
    list_storage[2] = (uint32_t)(uintptr_t)node_a;
    node_a[0] = (uint32_t)(uintptr_t)sentinel;
    node_a[1] = (uint32_t)(uintptr_t)&prev_slot;
    prev_slot = (uint32_t)(uintptr_t)node_a;
    pop_list_back(list_storage);
    assert(list_storage[3] == 0);
    assert(node_a[0] == 0);
    assert(node_a[1] == 0);
    assert(prev_slot == (uint32_t)(uintptr_t)sentinel);
    assert(sentinel[1] == (uint32_t)(uintptr_t)&prev_slot);

    static uint32_t block_storage[8];
    block_storage[3] = 0x2468;
    assert(get_block_size(&block_storage[4]) == 0x2468);

    static uint32_t fake_storage[4];
    fake_storage[3] = 0x4321;
    block_storage[3] = (uint32_t)(uintptr_t)fake_storage + 1;
    assert(get_block_size(&block_storage[4]) == 0x4321);

    assert(map_event_type(2) == 0);
    assert(map_event_type(6) == 2);
    assert(map_event_type(19) == 17);
    assert(map_event_type(20) == 19);
    assert(map_event_type(1) == 19);

    assert(clamp_with_deadzone(100, 50, 60, 128) == 50);
    assert(clamp_with_deadzone(50, 50, 60, 128) == 50);
    assert(clamp_with_deadzone(200, 50, 60, 128) ==
           (int32_t)(int16_t)(50 + (int16_t)((90 * 128) >> 7)));
    assert(clamp_with_deadzone(-100, 50, 60, 128) ==
           (int32_t)(int16_t)(50 + (int16_t)((-90 * 128) >> 7)));

    static uint32_t field_storage;
    set_field_value(&field_storage, 0xdeadbeef);
    assert(field_storage == 0xdeadbeef);
    set_field_value(&field_storage, 0);
    assert(field_storage == 0);

    assert(get_constant_value() == 0);

    static uint8_t ready_storage[0x61];
    ready_storage[0x60] = 0xb;
    ready_storage[0x5f] = 0xb;
    assert(check_object_ready(ready_storage) == 1);
    ready_storage[0x5f] = 0;
    assert(check_object_ready(ready_storage) == 0);
    ready_storage[0x60] = 5;
    ready_storage[0x5f] = 5;
    assert(check_object_ready(ready_storage) == 1);
    ready_storage[0x5f] = 4;
    assert(check_object_ready(ready_storage) == 0);
    ready_storage[0x60] = 0xc;
    ready_storage[0x5f] = 0;
    assert(check_object_ready(ready_storage) == 0);
    ready_storage[0x60] = 0x8b;
    ready_storage[0x5f] = 0x8b;
    assert(check_object_ready(ready_storage) == 1);

    static uint32_t field_obj[0x16];
    field_obj[0x13] = 1;
    field_obj[0x14] = 2;
    field_obj[0x12] = 3;
    ((uint8_t *)field_obj)[0x44] = 1;
    ((uint8_t *)field_obj)[0x54] = 1;
    reset_object_fields(field_obj);
    assert(field_obj[0x13] == 0);
    assert(field_obj[0x14] == 0);
    assert(field_obj[0x12] == 0);
    assert(((uint8_t *)field_obj)[0x44] == 0);
    assert(((uint8_t *)field_obj)[0x54] == 0);

    static const uint16_t wide_storage[4] = { 'L', 'M', '3', 0 };
    assert(wide_string_length(wide_storage) == 3);
    static const uint16_t empty_wide[1] = { 0 };
    assert(wide_string_length(empty_wide) == 0);

    static const uint32_t src_struct[2] = { 0x11223344, 0xaabb0000 };
    static uint32_t dest_struct[2];
    copy_short_struct(dest_struct, src_struct);
    assert(dest_struct[0] == 0x11223344);
    assert((dest_struct[1] & 0xffff) == 0);

    static uint32_t zero_obj[8];
    zero_obj[7] = 0;
    assert(is_field_zero(zero_obj) == 1);
    zero_obj[7] = 1;
    assert(is_field_zero(zero_obj) == 0);

    invalidate_field(zero_obj);
    assert(zero_obj[7] == 0xffffffff);
    zero_obj[7] = 5;
    invalidate_handle_field(zero_obj);
    assert(zero_obj[7] == 0xffffffff);

    static uint32_t link_target[4];
    static uint32_t link_slot[1];
    link_slot[0] = (uint32_t)(uintptr_t)link_target;
    link_target[2] = (uint32_t)(uintptr_t)link_slot;
    unlink_handle_reference(link_slot);
    assert(link_slot[0] == 0);
    assert(link_target[2] == 0);

    static uint32_t owner_obj[4];
    static uint32_t owner_target[4];
    static uint32_t owner_slot[1];
    owner_obj[3] = (uint32_t)(uintptr_t)owner_slot;
    owner_slot[0] = (uint32_t)(uintptr_t)owner_target;
    owner_target[3] = (uint32_t)(uintptr_t)owner_slot;
    unlink_object_reference(owner_obj);
    assert(owner_slot[0] == 0);
    assert(owner_target[3] == 0);

    static uint32_t short_obj[2];
    short_obj[0] = 0xffffffff;
    short_obj[1] = 0xffff;
    clear_short_struct(short_obj);
    assert(short_obj[0] == 0);
    assert((short_obj[1] & 0xffff) == 0);

    assert(is_alternate_mode(0x2601) == 1);
    assert(is_alternate_mode(0x2600) == 0);
    assert(is_alternate_mode(0x1234) == 0);

    static uint32_t byte_obj[3];
    set_byte_pair_high(byte_obj, 0x12, 0x34);
    assert(((uint8_t *)byte_obj)[8] == 0x12);
    assert(((uint8_t *)byte_obj)[9] == 0x34);
    set_byte_pair_low(byte_obj, 0x56, 0x78);
    assert(((uint8_t *)byte_obj)[6] == 0x56);
    assert(((uint8_t *)byte_obj)[7] == 0x78);

    static uint32_t cond_obj[2];
    set_conditional_field(cond_obj, 1, 0xaa);
    assert(cond_obj[1] == 0xaa);
    set_conditional_field(cond_obj, 0, 0xbb);
    assert(cond_obj[1] == 0);
    set_conditional_field(cond_obj, 3, 0xcc);
    assert(cond_obj[1] == 0);
    set_conditional_field(cond_obj, 5, 0xdd);
    assert(cond_obj[1] == 0xdd);

    static uint32_t slot_table[0x105 / 4 + 1];
    slot_table[0xf4 / 4] = 0x111;
    slot_table[0xfc / 4] = 0x222;
    assert(get_slot_index(slot_table, 0x111) == 1);
    assert(get_slot_index(slot_table, 0x222) == 3);
    assert(get_slot_index(slot_table, 0x999) == 0);

    static uint32_t flag_obj[0x174 / 4];
    initialize_flag_block(flag_obj);
    uint8_t *fb = (uint8_t *)flag_obj;
    assert(fb[0x16c] == 1);
    assert(fb[0x172] == 0);
    assert(fb[0x170] == 6);
    assert(fb[0x171] == 1);
    assert(fb[0x173] == 0);

    static uint32_t idx_obj[0x818 / 4];
    idx_obj[0x80c / 4 + 2] = 0x777;
    assert(get_indexed_field(idx_obj, 2) == 0x777);
    assert(get_indexed_field(idx_obj, 0) == 0);

    static uint32_t total_storage;
    total_storage = 100;
    accumulate_global(&total_storage, 23);
    assert(total_storage == 123);

    static uint16_t half_target[2];
    set_global_halfword(half_target, 0xabcd);
    assert(half_target[1] == 0xabcd);

    static const uint32_t pair_storage[2] = { 0x44332211, 0x88776655 };
    assert(get_indexed_byte(pair_storage, 0) == 0x11);
    assert(get_indexed_byte(pair_storage, 3) == 0x44);
    assert(get_indexed_byte(pair_storage, 4) == 0x55);
    assert(get_indexed_byte(pair_storage, 7) == 0x88);

    static uint8_t zero_storage[8];
    zero_storage[0] = 0xff;
    zero_storage[7] = 0xff;
    void *zero_end = rt_memzero(zero_storage, 8);
    assert(zero_end == zero_storage + 8);
    assert(zero_storage[0] == 0);
    assert(zero_storage[7] == 0);

    static char padded_storage[16];
    padded_storage[15] = 'x';
    char *result = copy_string_padded(padded_storage, "Mansion", 16);
    assert(result == padded_storage);
    assert(padded_storage[0] == 'M');
    assert(padded_storage[6] == 'n');
    assert(padded_storage[7] == '\0');
    assert(padded_storage[15] == '\0');
    static char exact_storage[4];
    copy_string_padded(exact_storage, "abcd", 4);
    assert(exact_storage[0] == 'a');
    assert(exact_storage[3] == 'd');

    static const uint8_t copy_src[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    static uint8_t copy_dest[8];
    void *copy_result = rt_memcpy(copy_dest, copy_src, 8);
    assert(copy_result == copy_dest);
    assert(copy_dest[0] == 1);
    assert(copy_dest[7] == 8);

    static uint32_t sem_storage[2];
    sem_storage[0] = 5;
    ((uint16_t *)sem_storage)[3] = 100;
    int32_t prev = semaphore_post(sem_storage, 3);
    assert(prev == 5);
    assert((int32_t)sem_storage[0] == 8);
    prev = semaphore_post(sem_storage, 1);
    assert(prev == 8);
    assert((int32_t)sem_storage[0] == 9);

    static uint32_t queue_buffer[4];
    static uint32_t queue_obj[0xd];
    queue_buffer[0] = 0xaaa;
    queue_buffer[1] = 0xbbb;
    queue_obj[0] = (uint32_t)(uintptr_t)queue_buffer;
    queue_obj[8] = 4;
    queue_obj[9] = 0;
    queue_obj[10] = 2;
    queue_obj[0xc] = 0;
    uint32_t popped = 0;
    assert(queue_pop(queue_obj, &popped) == 1);
    assert(popped == 0xaaa);
    assert(queue_obj[9] == 1);
    assert(queue_obj[10] == 1);
    assert(queue_pop(queue_obj, &popped) == 1);
    assert(popped == 0xbbb);
    assert(queue_obj[9] == 2);
    assert(queue_obj[10] == 0);
    assert(queue_pop(queue_obj, &popped) == 0);

    static uint32_t ring_obj[4];
    static uint32_t cursor_base[0x108];
    static uint32_t ring_state[4];
    ring_state[2] = (uint32_t)(uintptr_t)cursor_base;
    ring_obj[0] = (uint32_t)(uintptr_t)ring_state;
    static const uint8_t cmd_payload[0x408] = { 0 };
    write_command_record(ring_obj, 0x42, cmd_payload);
    assert(cursor_base[0] == 0x42 << 8);
    assert(cursor_base[1] == 0x000f01c5);
    assert(ring_state[2] == (uint32_t)(uintptr_t)(cursor_base + 0x104));

    static const uint32_t cmd_table[1] = { 0x37 };
    ring_state[2] = (uint32_t)(uintptr_t)cursor_base;
    write_command_record_indexed(ring_obj, cmd_table, cmd_payload);
    assert(cursor_base[0] == 0x37 << 8);

    static uint32_t rm_list[0x1e0 / 4];
    static uint32_t rm_node[3];
    static uint32_t rm_prev[2];
    static uint32_t rm_next[1];
    rm_list[0x1dc / 4] = 5;
    rm_node[1] = (uint32_t)(uintptr_t)rm_prev;
    rm_node[2] = (uint32_t)(uintptr_t)rm_next;
    rm_prev[1] = (uint32_t)(uintptr_t)rm_node;
    rm_next[0] = (uint32_t)(uintptr_t)rm_node;
    remove_list_node(rm_list, rm_node);
    assert(rm_list[0x1dc / 4] == 4);
    assert(rm_node[1] == 0);
    assert(rm_node[2] == 0);
    assert(rm_prev[1] == (uint32_t)(uintptr_t)rm_next);
    assert(rm_next[0] == (uint32_t)(uintptr_t)rm_prev);

    static uint8_t byte_target[0xe];
    set_global_byte(byte_target, 0x5a);
    assert(byte_target[0xd] == 0x5a);

    static uint32_t entry_count[1];
    static uint32_t entry_node[2];
    static uint32_t entry_prev[2];
    static uint32_t entry_next[1];
    entry_count[0] = 3;
    entry_node[0] = (uint32_t)(uintptr_t)entry_prev;
    entry_node[1] = (uint32_t)(uintptr_t)entry_next;
    entry_prev[1] = (uint32_t)(uintptr_t)entry_node;
    entry_next[0] = (uint32_t)(uintptr_t)entry_node;
    remove_list_entry(entry_count, entry_node);
    assert(entry_count[0] == 2);
    assert(entry_node[0] == 0);
    assert(entry_node[1] == 0);
    assert(entry_prev[1] == (uint32_t)(uintptr_t)entry_next);
    assert(entry_next[0] == (uint32_t)(uintptr_t)entry_prev);

    static const float identity[12] = {
        1.0f, 0.0f, 0.0f, 10.0f,
        0.0f, 1.0f, 0.0f, 20.0f,
        0.0f, 0.0f, 1.0f, 30.0f
    };
    static const float point[3] = { 1.0f, 2.0f, 3.0f };
    static float out_point[3];
    transform_point_affine(out_point, identity, point);
    assert(out_point[0] == 11.0f);
    assert(out_point[1] == 22.0f);
    assert(out_point[2] == 33.0f);

    static uint32_t fill_storage[6];
    fill_storage[0] = 1;
    fill_storage[5] = 1;
    fill_word_range(fill_storage, fill_storage + 6, 0xcafe);
    assert(fill_storage[0] == 0xcafe);
    assert(fill_storage[5] == 0xcafe);
    fill_word_range(fill_storage, fill_storage, 0);
    assert(fill_storage[0] == 0xcafe);

    static uint16_t desc_storage[0x12];
    initialize_render_descriptor(desc_storage);
    assert(desc_storage[0] == 0x28);
    assert(desc_storage[1] == 0x24);
    assert(desc_storage[2] == 0x28);
    assert(desc_storage[3] == 0x91);
    assert(desc_storage[5] == 0x91);
    assert(desc_storage[7] == 0x8d);
    assert(((uint8_t *)desc_storage)[0xc] == 0);
    float *descf = (float *)(desc_storage + 8);
    assert(descf[0] == 1.5f);
    assert(descf[1] == 141.0f);
    assert(descf[2] == 0.0f);
    assert(descf[3] == 0.0f);
    assert(descf[4] == 0.0f);

    static uint32_t sat_obj[0x230 / 4];
    static const uint32_t amt[2] = { 10, 0 };
    *(uint32_t *)((uint8_t *)sat_obj + 0x1b4 + 2 * 4) = 100;
    saturating_add_indexed(sat_obj, amt, 2);
    assert(*(uint32_t *)((uint8_t *)sat_obj + 0x1b4 + 2 * 4) == 110);
    static const uint32_t big_amt[2] = { 0x7ffffff0, 0 };
    *(uint32_t *)((uint8_t *)sat_obj + 0x1b4) = 0x7fffff00;
    saturating_add_indexed(sat_obj, big_amt, 0);
    assert(*(uint32_t *)((uint8_t *)sat_obj + 0x1b4) == 0x7fffffff);

    static uint32_t blk[8];
    blk[2] = 1;
    blk[7] = 9;
    ((uint8_t *)blk)[0x14] = 1;
    clear_global_block(blk);
    assert(blk[2] == 0);
    assert(blk[7] == 0);
    assert(((uint8_t *)blk)[0x14] == 0);

    *(uint32_t *)((uint8_t *)sat_obj + 0x220) = 50;
    saturating_add_total(sat_obj, amt);
    assert(*(uint32_t *)((uint8_t *)sat_obj + 0x220) == 60);

    static uint32_t flag_obj2[2];
    *(uint16_t *)(flag_obj2 + 1) = 0b101;
    assert(test_flag_bit(flag_obj2, 0) == 1);
    assert(test_flag_bit(flag_obj2, 1) == 0);
    assert(test_flag_bit(flag_obj2, 2) == 1);

    static uint8_t slot_obj[0x120 + 3 * 0x2c];
    uint32_t *slot = get_indexed_slot((uint32_t *)slot_obj, 2);
    assert((uint8_t *)slot == slot_obj + 0x120 + 2 * 0x2c);

    static uint32_t ptr_obj[2];
    ptr_obj[1] = 0;
    assert(has_attached_pointer(ptr_obj) == 0);
    ptr_obj[1] = 1;
    assert(has_attached_pointer(ptr_obj) == 1);

    static uint16_t append_dest[8] = { 'A', 'B', 0 };
    static const uint16_t append_src[4] = { 'C', 'D', 'E', 0 };
    uint16_t *appended = append_wide_string_bounded(append_dest, append_src, 2);
    assert(appended == append_dest);
    assert(append_dest[0] == 'A');
    assert(append_dest[2] == 'C');
    assert(append_dest[3] == 'D');
    assert(append_dest[4] == 0);
    append_wide_string_bounded(append_dest, append_src, 0);
    assert(append_dest[4] == 0);

    static uint32_t vec_dest[0x104 / 4];
    static const uint32_t vec_src[4] = { 0x11, 0x22, 0x33, 0x44 };
    store_vector4(vec_dest, vec_src);
    assert(vec_dest[0xf4 / 4] == 0x11);
    assert(vec_dest[0xf8 / 4] == 0x22);
    assert(vec_dest[0xfc / 4] == 0x33);
    assert(vec_dest[0x100 / 4] == 0x44);

    static const uint16_t wstr[3] = { 'L', 'u', 0 };
    static uint32_t wdesc[3];
    uint32_t *wd = build_wide_string_descriptor(wdesc, 0x99, wstr);
    assert(wd == wdesc);
    assert(wdesc[0] == 0x99);
    assert(wdesc[1] == (uint32_t)(uintptr_t)wstr);
    assert(wdesc[2] == 4);

    static uint32_t store_obj[0x1a8 / 4];
    store_obj[0x1a4 / 4] = 0;
    assert(has_backing_store(store_obj) == 0);
    store_obj[0x1a4 / 4] = 7;
    assert(has_backing_store(store_obj) == 1);

    static uint32_t sub_obj[0x274 / 4 + 2 * (0xd0 / 4) + 2];
    sub_obj[0x274 / 4] = 1;
    sub_obj[1 * (0xd0 / 4) + 1] = 0;
    assert(has_active_subobject(sub_obj) == 0);
    sub_obj[1 * (0xd0 / 4) + 1] = 3;
    assert(has_active_subobject(sub_obj) == 1);

    static const uint32_t mat_src[12] = {
        1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0
    };
    static uint32_t mat_dest[12];
    transpose_matrix_rows(mat_dest, mat_src);
    assert(mat_dest[0] == 1);
    assert(mat_dest[1] == 4);
    assert(mat_dest[2] == 7);
    assert(mat_dest[3] == 0);
    assert(mat_dest[4] == 2);
    assert(mat_dest[5] == 5);
    assert(mat_dest[6] == 8);
    assert(mat_dest[7] == 0);
    assert(mat_dest[8] == 3);
    assert(mat_dest[9] == 6);
    assert(mat_dest[10] == 9);
    assert(mat_dest[11] == 0);

    static uint32_t handle_obj[0x3c / 4];
    set_object_handle_field(handle_obj, 0xdead, 0xbeef);
    assert(handle_obj[1] == 0xbeef);
    assert(handle_obj[0x38 / 4] == 0xdead);

    static uint32_t take_slot[1];
    take_slot[0] = 0xabc;
    assert(take_and_clear_global(take_slot) == 0xabc);
    assert(take_slot[0] == 0);
    assert(take_and_clear_global(take_slot) == 0);

    static const uint32_t pair_src[2] = { 0x11, 0x22 };
    static uint32_t pair_dest[2];
    copy_pair(pair_dest, pair_src);
    assert(pair_dest[0] == 0x11);
    assert(pair_dest[1] == 0x22);

    static uint32_t ins_count[2];
    static uint32_t ins_at[2];
    static uint32_t ins_node[2];
    static uint32_t ins_next[2];
    ins_count[0] = 1;
    ins_at[1] = (uint32_t)(uintptr_t)ins_next;
    ins_next[0] = 0;
    uint32_t *inserted = insert_list_after(ins_count, ins_at, ins_node);
    assert(inserted == ins_node);
    assert(ins_count[0] == 2);
    assert(ins_node[0] == (uint32_t)(uintptr_t)ins_at);
    assert(ins_node[1] == (uint32_t)(uintptr_t)ins_next);
    assert(ins_at[1] == (uint32_t)(uintptr_t)ins_node);
    assert(ins_next[0] == (uint32_t)(uintptr_t)ins_node);

    static uint32_t cl_count[1];
    static uint32_t cl_head[2];
    cl_count[0] = 1;
    cl_head[0] = (uint32_t)(uintptr_t)cl_head;
    cl_head[1] = (uint32_t)(uintptr_t)cl_head;
    clear_list(cl_count, cl_head);
    assert(cl_count[0] == 1);

    static uint8_t off_base[11];
    set_byte_at_offset(off_base, 0x77);
    assert(off_base[10] == 0x77);
    assert(off_base[0] == 0);

    static uint32_t tbl[8];
    tbl[0] = 0xaaaa;
    assert(get_table_entry(tbl, 0) == 0xaaaa);

    static int16_t clamp_desc[6];
    clamp_desc[0] = 0x10;
    clamp_desc[1] = 0x10;
    clamp_desc[3] = 0x200;
    clamp_desc[4] = 0x91;
    clamp_desc[5] = 0xff;
    clamp_render_descriptor(clamp_desc);
    assert(clamp_desc[0] == 0x28);
    assert(clamp_desc[1] == 0x24);
    assert(clamp_desc[3] == 0x91);
    assert(clamp_desc[4] == 0x91);
    assert(clamp_desc[5] == 0x91);

    static uint32_t range_desc[8];
    build_range_descriptor(range_desc, 0x77, 0x1000, 0x200);
    assert(range_desc[0] == 0x77);
    assert(range_desc[1] == 0);
    assert(range_desc[2] == 0x1000);
    assert(range_desc[3] == 0x1000);
    assert(range_desc[4] == 0x1000);
    assert(range_desc[5] == 0x200);
    assert(range_desc[6] == 0);
    assert(range_desc[7] == 0);

    assert(get_region_tag() == 0);
    assert(get_service_state_byte() == 0);

    static uint32_t bits[4];
    set_bitset_bit(bits, 0);
    assert(bits[0] == 1);
    set_bitset_bit(bits, 31);
    assert(bits[0] == 0x80000001u);
    set_bitset_bit(bits, 32);
    assert(bits[1] == 1);
    set_bitset_bit(bits, 65);
    assert(bits[2] == 2);

    static uint8_t flag_obj3[0x1c];
    ((uint8_t *)flag_obj3)[0x1b] = 9;
    clear_byte_flag(flag_obj3);
    assert(((uint8_t *)flag_obj3)[0x1b] == 0);

    static uint8_t cmd_desc[12];
    cmd_desc[2] = 9;
    cmd_desc[11] = 9;
    initialize_command_descriptor(cmd_desc);
    assert(cmd_desc[0] == 4);
    assert(cmd_desc[1] == 2);
    assert(cmd_desc[2] == 0);
    assert(cmd_desc[3] == 0);
    assert(*(uint32_t *)(cmd_desc + 4) == 0);
    assert(*(uint32_t *)(cmd_desc + 8) == 0);

    static const uint32_t quad_src[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    static uint32_t quad_dest[8];
    uint32_t *qr = copy_quad_pair(quad_dest, quad_src);
    assert(qr == quad_dest);
    assert(quad_dest[0] == 1);
    assert(quad_dest[7] == 8);

    quad_dest[0] = 9;
    quad_dest[1] = 9;
    clear_pair(quad_dest);
    assert(quad_dest[0] == 0);
    assert(quad_dest[1] == 0);

    noop_operation();

    static uint8_t region_rec[0x1c];
    build_region_record(region_rec, 10, 20, 30, 50, 0xaa, 0xbb);
    assert(region_rec[0] == 1);
    assert(*(int32_t *)(region_rec + 4) == 10);
    assert(*(int32_t *)(region_rec + 8) == 20);
    assert(*(int32_t *)(region_rec + 0xc) == 20);
    assert(*(int32_t *)(region_rec + 0x10) == 30);
    assert(*(uint32_t *)(region_rec + 0x14) == 0xaa);
    assert(*(uint32_t *)(region_rec + 0x18) == 0xbb);

    static uint8_t write_cursor[8];
    static uint32_t write_buf[0xec / 4];
    write_buf[0xdc / 4] = 5;
    write_buf[0xe0 / 4] = 3;
    write_buf[0xe4 / 4] = (uint32_t)(uintptr_t)write_cursor;
    reset_write_buffer(write_buf);
    assert(write_buf[0xdc / 4] == 0x10000000u);
    assert(write_buf[0xe0 / 4] == 1);
    assert(write_cursor[0] == 0x1c);
    assert(write_buf[0xe8 / 4] == (uint32_t)(uintptr_t)(write_cursor + 1));

    int16_t out_tag = 0;
    int16_t out_value = 0;
    lookup_command_value(&out_tag, &out_value, 0x8056);
    assert(out_tag == (int16_t)0x6752);
    assert(out_value == (int16_t)0x8033);
    lookup_command_value(&out_tag, &out_value, 0x8057);
    assert(out_value == (int16_t)0x8034);
    lookup_command_value(&out_tag, &out_value, 0x8058);
    assert(out_value == (int16_t)0x1401);
    lookup_command_value(&out_tag, &out_value, 0x8d62);
    assert(out_tag == (int16_t)0x6754);
    assert(out_value == (int16_t)0x8363);

    static uint8_t region_blk[0x1c];
    initialize_region_block(region_blk);
    assert(region_blk[0] == 1);
    assert(*(uint32_t *)(region_blk + 4) == 0);
    assert(*(uint32_t *)(region_blk + 0x10) == 0x140);
    assert(*(uint32_t *)(region_blk + 0x14) == 0x100);
    assert(*(uint32_t *)(region_blk + 0x18) == 0x140);
    assert(*(uint32_t *)(region_blk + 8) == 0);
    assert(*(uint32_t *)(region_blk + 0xc) == 0xf0);

    static uint32_t list_pair[8];
    initialize_list_head_pair(list_pair);
    assert(list_pair[0] == 0);
    assert(list_pair[1] == 0);
    assert(list_pair[2] == (uint32_t)(uintptr_t)(list_pair + 4));
    assert(list_pair[3] == (uint32_t)(uintptr_t)(list_pair + 4));

    static uint32_t rec[8];
    rec[1] = 9;
    rec[7] = 9;
    ((uint8_t *)rec)[0x18] = 0;
    initialize_record(rec, 0x55);
    assert(rec[0] == 0);
    assert(rec[1] == 0);
    assert(rec[2] == 0);
    assert(rec[3] == 0);
    assert(rec[5] == 0);
    assert(rec[7] == 0x55);
    assert(((uint8_t *)rec)[0x18] == 1);

    rec[0] = 1;
    rec[1] = 2;
    rec[2] = 3;
    rec[3] = 4;
    clear_quad(rec);
    assert(rec[0] == 0);
    assert(rec[3] == 0);

    static uint8_t state_obj[0x28];
    state_obj[0] = 1;
    state_obj[1] = 1;
    *(uint32_t *)(state_obj + 4) = 5;
    *(uint32_t *)(state_obj + 0x24) = 6;
    clear_state_fields(state_obj);
    assert(state_obj[0] == 0);
    assert(state_obj[1] == 0);
    assert(*(uint32_t *)(state_obj + 4) == 0);
    assert(*(uint32_t *)(state_obj + 8) == 0);
    assert(*(uint32_t *)(state_obj + 0xc) == 0);
    assert(*(uint32_t *)(state_obj + 0x24) == 0);

    static uint8_t status_blk[0xd];
    set_status_byte_b(status_blk, 0x42);
    assert(status_blk[0xb] == 0x42);
    status_blk[9] = 0x80;
    assert(get_status_byte_9(status_blk) == -128);
    status_blk[9] = 0x7f;
    assert(get_status_byte_9(status_blk) == 127);
    set_status_byte_c(status_blk, 0x99);
    assert(get_status_byte_c(status_blk) == 0x99);
    assert(status_blk[0xc] == 0x99);

    status_blk[1] = 0x81;
    assert(get_status_byte_1(status_blk) == -127);
    status_blk[6] = 0x55;
    assert(get_status_byte_6(status_blk) == 0x55);
    status_blk[2] = 0x33;
    assert(get_status_byte_2(status_blk) == 0x33);

    static uint8_t obj120[0x121];
    obj120[0x120] = 0xfe;
    assert(get_object_field_120(obj120) == -2);

    assert(map_service_mode(3) == 1);
    assert(map_service_mode(4) == 1);
    assert(map_service_mode(5) == 2);
    assert(map_service_mode(0) == 0);
    assert(map_service_mode(9) == 0);

    static uint8_t idx_blk[0x10];
    idx_blk[0xd] = 0xaa;
    idx_blk[0xe] = 0xbb;
    assert(get_indexed_status_byte(idx_blk, 0) == 0xaa);
    assert(get_indexed_status_byte(idx_blk, 1) == 0xbb);

    static uint32_t svc_target[1];
    svc_store_word(svc_target, 0xcafe);
    assert(svc_target[0] == 0xcafe);

    static uint32_t map_storage[8];
    add_map_entry(map_storage, 0x11, 0x22);
    assert(map_storage[0] == 1);
    assert(map_storage[1] == 0x11);
    assert(map_storage[2] == 0x22);
    add_map_entry(map_storage, 0x33, 0x44);
    assert(map_storage[0] == 2);
    assert(map_storage[3] == 0x33);
    assert(map_storage[4] == 0x44);

    static uint32_t word_obj[8];
    word_obj[0x1c / 4] = 0x1234;
    word_obj[0x18 / 4] = 0x5678;
    assert(get_word_field_1c(word_obj) == 0x1234);
    assert(get_word_field_18(word_obj) == 0x5678);

    static const uint16_t ws_a[3] = { 'a', 'b', 0 };
    static const uint16_t ws_b[3] = { 'a', 'b', 0 };
    assert(compare_wide_strings(ws_a, ws_b) == 0);
    static const uint16_t ws_c[3] = { 'a', 'c', 0 };
    assert(compare_wide_strings(ws_a, ws_c) == (uint32_t)('b' - 'c'));

    word_obj[3] = 0x80;
    assert(test_flag_80(word_obj) == 0x80);
    word_obj[3] = 0x40;
    assert(test_flag_80(word_obj) == 0);

    static uint32_t rc_pointed[8];
    static uint32_t rc_holder[1];
    static uint32_t rc_slot[1];
    rc_pointed[7] = 5;
    rc_holder[0] = (uint32_t)(uintptr_t)rc_pointed;
    increment_reference_count(rc_slot, rc_holder);
    assert(rc_slot[0] == (uint32_t)(uintptr_t)rc_pointed);
    assert(rc_pointed[7] == 6);

    static uint32_t ptr_base[8];
    static uint32_t ptr_data[8];
    ptr_base[0] = (uint32_t)(uintptr_t)ptr_data;
    assert(get_indexed_pointer(ptr_base, 3) == ptr_data + 3);

    static uint32_t max_a[1];
    static uint32_t max_b[1];
    max_a[0] = 5;
    max_b[0] = 9;
    assert(select_larger(max_a, max_b) == max_b);
    assert(select_larger(max_b, max_a) == max_b);

    static uint8_t obj202[0x203];
    obj202[0x202] = 7;
    clear_byte_at_202(obj202);
    assert(obj202[0x202] == 0);

    static uint32_t quad_obj[0x160 / 4];
    set_quad_fields(quad_obj, 1, 2, 3, 4);
    assert(quad_obj[0x150 / 4] == 1);
    assert(quad_obj[0x15c / 4] == 4);

    assert(get_region_base() == 0x3000000);

    static uint8_t flag_obj854[0x856];
    set_flag_854(flag_obj854);
    assert(flag_obj854[0x854] == 1);
    set_flag_855(flag_obj854);
    assert(flag_obj854[0x855] == 1);

    assert(identity_word(0xdead) == 0xdead);

    static uint32_t rec_fields[7];
    rec_fields[0] = 1;
    clear_record_fields(rec_fields);
    assert(rec_fields[0] == 0);
    assert(rec_fields[2] == 0xffffffffu);

    static uint32_t six_fields[6];
    six_fields[5] = 9;
    clear_six_fields(six_fields);
    assert(six_fields[5] == 0);

    static uint32_t four_obj[0x90 / 4];
    set_four_offsets(four_obj, 0x99);
    assert(four_obj[0x24 / 4] == 0x99);
    assert(four_obj[0x8c / 4] == 0x99);

    four_obj[0] = 7;
    clear_first_word(four_obj);
    assert(four_obj[0] == 0);

    static uint8_t obj84[0x85];
    obj84[0x84] = 5;
    clear_byte_84(obj84);
    assert(obj84[0x84] == 0);

    static uint8_t obj18[0x19];
    obj18[0x18] = 3;
    clear_byte_18(obj18);
    assert(obj18[0x18] == 0);

    static uint32_t hw_obj[3];
    hw_obj[0] = 0xffffffff;
    hw_obj[1] = 0xffffffff;
    clear_three_halfwords(hw_obj);
    assert(hw_obj[0] == 0);
    assert((hw_obj[1] & 0xffff) == 0);

    static uint32_t fw_obj[5];
    fw_obj[1] = 1; fw_obj[4] = 2;
    clear_four_words(fw_obj);
    assert(fw_obj[1] == 0 && fw_obj[4] == 0);

    static uint8_t store_region[0x300];
    static uint32_t idx_table[4];
    *(uint32_t *)(store_region + 0x2fc) = (uint32_t)(uintptr_t)idx_table;
    static const uint32_t idx_val[1] = { 0x77 };
    store_indexed_value((uint32_t *)store_region, 2, idx_val);
    assert(idx_table[2] == 0x77);

    static uint32_t attach_obj[2];
    attach_obj[1] = 0;
    assert(has_valid_attachment(attach_obj) == 0);
    attach_obj[1] = 1;
    assert(has_valid_attachment(attach_obj) == 1);

    static uint32_t lock_obj[0x60 / 4];
    lock_obj[0x5c / 4] = 0xabcd;
    assert(get_locked_field_5c(lock_obj) == 0xabcd);

    static uint32_t confirm_obj[2];
    assert(set_field_and_confirm(confirm_obj, 0x55) == 1);
    assert(confirm_obj[1] == 0x55);

    static uint32_t slot138[0x140 / 4];
    slot138[0x138 / 4 + 1] = 9;
    clear_indexed_slot_138(slot138, 1);
    assert(slot138[0x138 / 4 + 1] == 0);

    static uint32_t copy_obj[0x188 / 4];
    copy_obj[0x180 / 4] = 0x66;
    copy_field_180_to_184(copy_obj);
    assert(copy_obj[0x184 / 4] == 0x66);

    static uint32_t slot128[0x130 / 4];
    slot128[0x128 / 4 + 1] = 7;
    clear_indexed_slot_128(slot128, 1);
    assert(slot128[0x128 / 4 + 1] == 0);

    static const uint32_t state_vals[7] = { 1, 2, 3, 4, 5, 6, 7 };
    static uint32_t state_rec[0x2c / 4];
    build_state_record(state_rec, 0xaa, 0xbb, state_vals);
    assert(state_rec[0x20 / 4] == 0xaa);
    assert(state_rec[0x28 / 4] == 0xbb);
    assert(state_rec[1] == 1);
    assert(state_rec[7] == 7);

    static uint8_t obj49[0x4a];
    obj49[0x49] = 2;
    clear_byte_49(obj49);
    assert(obj49[0x49] == 0);

    noop_return();

    static uint8_t obj16c[0x16d];
    obj16c[0x16c] = 9;
    clear_byte_16c(obj16c);
    assert(obj16c[0x16c] == 0);

    static uint32_t fwb_obj[5];
    fwb_obj[0] = 1; fwb_obj[3] = 2;
    ((uint8_t *)fwb_obj)[0x10] = 5;
    clear_four_words_and_byte(fwb_obj);
    assert(fwb_obj[0] == 0 && fwb_obj[3] == 0);
    assert(((uint8_t *)fwb_obj)[0x10] == 0);

    static uint32_t detach_obj[4];
    static uint32_t detach_tgt_a[4];
    static uint32_t detach_tgt_b[4];
    detach_obj[2] = (uint32_t)(uintptr_t)detach_tgt_a;
    detach_obj[1] = (uint32_t)(uintptr_t)detach_tgt_b;
    detach_tgt_a[0] = 0;
    detach_tgt_b[0] = 0;
    assert(detach_handle_references(detach_obj) == detach_obj);

    static uint8_t obj1fd[0x1fe];
    set_flag_1fd(obj1fd);
    assert(obj1fd[0x1fd] == 1);
    set_flag_1fd(obj1fd);
    assert(obj1fd[0x1fd] == 1);

    assert(get_indexed_record_address(0x1000, 2) == 0x1000 + 2 * 0x80 + 0xff8);

    static uint32_t obj20ac[0x20b0 / 4];
    assert(is_field_20ac_zero(obj20ac) == 1);
    obj20ac[0x20ac / 4] = 1;
    assert(is_field_20ac_zero(obj20ac) == 0);

    static uint32_t one_obj[1];
    set_first_word_one(one_obj);
    assert(one_obj[0] == 1);

    assert(get_thread_field_5c() == 0x5c);

    static uint32_t idxw_obj[0x1c / 4 + 2];
    idxw_obj[0x18 / 4 + 2] = 0x88;
    assert(get_indexed_word_18(idxw_obj, 2) == 0x88);

    assert(compute_record_offset(1, 2, 3) == 3u * 2u + 0xba0u + 0x36c0u);

    static uint8_t bit_obj[0x1d];
    set_bit_in_field(bit_obj, 3);
    assert(bit_obj[0xf] == 0x08);
    set_bit_in_field(bit_obj, 60);
    assert(bit_obj[0xf] == 0x08);
    set_bit_in_field(bit_obj, 8);
    assert(bit_obj[0x10] == 0x01);

    static uint32_t w28_obj[0x2c / 4];
    w28_obj[0x28 / 4] = 5;
    clear_word_28(w28_obj);
    assert(w28_obj[0x28 / 4] == 0);

    static uint32_t p38_obj[0x40 / 4];
    p38_obj[0x38 / 4] = 1;
    p38_obj[0x3c / 4] = 2;
    clear_pair_38(p38_obj);
    assert(p38_obj[0x38 / 4] == 0);
    assert(p38_obj[0x3c / 4] == 0);

    static uint32_t status_rec[4];
    initialize_status_record(status_rec);
    assert(status_rec[1] == 0);
    assert(((uint8_t *)status_rec)[0xc] == 0x2f);
    assert(((uint8_t *)status_rec)[0xd] == 0);

    static uint32_t t38_obj[0x44 / 4];
    t38_obj[0x40 / 4] = 7;
    clear_triple_38(t38_obj);
    assert(t38_obj[0x40 / 4] == 0);

    static uint32_t p85c_obj[0x60 / 4];
    set_pair_8_5c(p85c_obj, 0x11, 0x22);
    assert(p85c_obj[8 / 4] == 0x11);
    assert(p85c_obj[0x5c / 4] == 0x22);

    static uint32_t status_blk2[3];
    status_blk2[0] = 1;
    status_blk2[1] = 2;
    clear_status_block(status_blk2);
    assert(status_blk2[0] == 0);
    assert(status_blk2[1] == 0);

    static uint32_t nested_obj[0x138 / 4];
    static uint32_t nested_inner[8];
    nested_inner[6] = 0x999;
    nested_obj[0x12c / 4] = (uint32_t)(uintptr_t)nested_inner;
    nested_obj[0x134 / 4] = 1;
    assert(get_nested_field_18(nested_obj) == 0x999);
    nested_obj[0x134 / 4] = 0;
    assert(get_nested_field_18(nested_obj) == 0);

    static uint32_t f14_obj[6];
    f14_obj[0x14 / 4] = 100;
    assert(get_field_14_offset_658(f14_obj) == 100 + 0x658);

    static uint32_t pointed_target[1];
    pointed_target[0] = 7;
    static uint32_t cp_obj[0x24 / 4];
    cp_obj[0x20 / 4] = 5;
    cp_obj[2] = (uint32_t)(uintptr_t)pointed_target;
    clear_word_20_and_pointed(cp_obj);
    assert(cp_obj[0x20 / 4] == 0);
    assert(pointed_target[0] == 0);

    static uint32_t idxpt_obj[8];
    idxpt_obj[0x14 / 4] = 1;
    idxpt_obj[2] = 0x4000;
    assert(get_indexed_pointed_field(idxpt_obj, 0x40) == 0x4040);

    static uint32_t p48_inner[0x4c / 4];
    p48_inner[0x48 / 4] = 0x777;
    static uint32_t p48_obj[6];
    p48_obj[0x14 / 4] = (uint32_t)(uintptr_t)p48_inner;
    assert(get_pointed_field_48(p48_obj) == 0x777);

    static uint8_t b4c[0x4d];
    b4c[0x4c] = 7; clear_byte_4c(b4c); assert(b4c[0x4c] == 0);

    static uint8_t rec10[0x11];
    *(uint32_t *)(rec10 + 8) = 5; clear_record_10(rec10);
    assert(rec10[0x10] == 0 && *(uint32_t *)(rec10 + 8) == 0);

    static uint32_t w14[6]; w14[0x14/4] = 9; clear_word_14(w14); assert(w14[0x14/4] == 0);

    static uint8_t b190[401]; b190[400] = 3; clear_byte_190(b190); assert(b190[400] == 0);

    static uint32_t pw20[1]; static uint32_t pw20t[1];
    pw20t[0] = 5; pw20[0] = (uint32_t)(uintptr_t)pw20t;
    clear_pointed_word_20(pw20); assert(pw20t[0] == 0);

    static uint8_t b98[0x99]; set_byte_98(b98); assert(b98[0x98] == 1);

    static uint8_t dirty[0x500c / 4 * 4];
    *(uint32_t *)(dirty + 0x5008) = 0;
    set_byte_and_mark_dirty(dirty, 0x42);
    assert(dirty[0] == 0x42);
    assert((*(uint32_t *)(dirty + 0x5008) & 0x21) == 0x21);

    static uint32_t dm[0x68 / 4];
    dm[0x64 / 4] = 5; dm[0xc / 4] = 6;
    assert(is_double_match(dm, 6, 5) == 1);
    assert(is_double_match(dm, 6, 4) == 0);

    static uint32_t inv[0x28 / 4];
    invalidate_range_fields(inv);
    assert(inv[0xc / 4] == 0xffffffffu && inv[0x14 / 4] == 0 && inv[0x24 / 4] == 0);

    static uint32_t pc8[4]; pc8[0xc / 4] = 1; pc8[8 / 4] = 2;
    clear_pair_c_8(pc8); assert(pc8[0xc / 4] == 0 && pc8[8 / 4] == 0);

    static uint32_t r4c[0x60 / 4];
    r4c[0x4c / 4] = 1; r4c[0x40 / 4] = 2; ((uint8_t *)r4c)[0x5c] = 3;
    clear_record_4c(r4c);
    assert(r4c[0x4c / 4] == 0 && r4c[0x40 / 4] == 0);

    static uint32_t sub_parent[1]; static uint16_t sub_rec[12];
    sub_rec[2] = 9; sub_parent[0] = 1;
    clear_sub_record(sub_parent, sub_rec);
    assert(sub_rec[2] == 0 && sub_parent[0] == 0);

    static uint32_t cf21c[0x220 / 4];
    ((int8_t *)cf21c)[0x9c] = 0; assert(get_conditional_field_21c(cf21c) == 0);
    ((int8_t *)cf21c)[0x9c] = 1; cf21c[0x21c / 4] = 0xabc;
    assert(get_conditional_field_21c(cf21c) == 0xabc);

    static uint32_t pf44_inner[0x48 / 4];
    pf44_inner[0x44 / 4] = 3;
    static uint32_t pf44_obj[2];
    pf44_obj[1] = (uint32_t)(uintptr_t)pf44_inner;
    assert(has_pointed_field_44(pf44_obj) == 1);
    pf44_inner[0x44 / 4] = 0;
    assert(has_pointed_field_44(pf44_obj) == 0);

    static uint32_t dp8_mid[3];
    dp8_mid[2] = 0x55;
    static uint32_t dp8_outer[1];
    dp8_outer[0] = (uint32_t)(uintptr_t)dp8_mid;
    static uint32_t dp8_obj[7];
    dp8_obj[6] = (uint32_t)(uintptr_t)dp8_outer;
    assert(get_double_pointed_field_8(dp8_obj) == 0x55);

    assert(passthrough_word(0x1234) == 0x1234);

    static uint32_t t102_obj[0x20 / 4];
    *(int16_t *)((uint8_t *)t102_obj + 0x1c) = 0x102;
    assert(mark_if_type_102(t102_obj) == 1);
    assert(*(uint16_t *)((uint8_t *)t102_obj + 0xc) == 6);
    *(int16_t *)((uint8_t *)t102_obj + 0x1c) = 0x100;
    *(uint16_t *)((uint8_t *)t102_obj + 0xc) = 0;
    mark_if_type_102(t102_obj);
    assert(*(uint16_t *)((uint8_t *)t102_obj + 0xc) == 0);

    static uint8_t ff_dest[4];
    set_bytes_ff(ff_dest);
    assert(ff_dest[0] == 0xff && ff_dest[3] == 0xff);

    static uint32_t c21c_obj[0x220 / 4];
    c21c_obj[0x21c / 4] = 9;
    assert(clear_word_21c_and_confirm(c21c_obj) == 1);
    assert(c21c_obj[0x21c / 4] == 0);

    static uint8_t b2c_obj[0x30];
    b2c_obj[0x2c] = 5;
    *(uint32_t *)(b2c_obj + 0x20) = 6;
    clear_byte_2c_and_word_20(b2c_obj);
    assert(b2c_obj[0x2c] == 0);
    assert(*(uint32_t *)(b2c_obj + 0x20) == 0);

    noop_b();
    noop_c();
    noop_d();

    uint64_t ma = multiply_accumulate_64(2, 0, 3, 0);
    assert((uint32_t)ma == 6);

    static uint8_t f7_target[0xf8];
    static uint32_t f7_mid_block[0xb10 / 4];
    static uint32_t f7_obj[2];
    f7_mid_block[0xb08 / 4] = (uint32_t)(uintptr_t)f7_target;
    f7_obj[1] = (uint32_t)(uintptr_t)f7_mid_block;
    ((uint32_t *)f7_target)[0x48 / 4] = 0xffffffff;
    clear_byte_f7_and_mask(f7_obj);
    assert(f7_target[0xf7] == 0xff);
    assert((((uint32_t *)f7_target)[0x48 / 4] & 0xc000) == 0);
    f7_target[0xf7] = 0xff;
    clear_byte_f7(f7_obj);
    assert(f7_target[0xf7] == 0);

    ((uint32_t *)f7_target)[0x48 / 4] = 0x60000;
    static uint32_t sm_obj[4];
    sm_obj[1] = (uint32_t)(uintptr_t)f7_mid_block;
    *(uint16_t *)((uint8_t *)sm_obj + 0xc) = 0;
    assert(set_field_if_mask_60000(sm_obj) == 1);
    assert(*(uint16_t *)((uint8_t *)sm_obj + 0xc) == 1);

    static uint32_t chan_rec[5];
    assert(initialize_channel_record(chan_rec, 0, 0, 0) == 0);
    assert(initialize_channel_record(chan_rec, 1, 0x55, 0x66) == 1);
    assert(chan_rec[2] == 0x55);
    assert(chan_rec[3] == 0x66);

    static uint32_t f4_obj[2];
    set_field_4(f4_obj, 0x42);
    assert(f4_obj[1] == 0x42);

    static uint8_t hc_obj[0xe];
    set_halfword_c_100(hc_obj);
    assert(*(uint16_t *)(hc_obj + 0xc) == 0x100);

    static uint32_t cq_obj[4];
    cq_obj[0] = 1; cq_obj[3] = 2;
    clear_quad_words(cq_obj);
    assert(cq_obj[0] == 0 && cq_obj[3] == 0);

    static uint32_t s1814_obj[0x124 / 4];
    set_fields_18_14_with_null_flag(s1814_obj, 5, 6);
    assert(s1814_obj[0x18 / 4] == 5);
    assert(s1814_obj[0x14 / 4] == 6);
    assert(((uint8_t *)s1814_obj)[0x121] == 0);
    set_fields_18_14_with_null_flag(s1814_obj, 0, 6);
    assert(((uint8_t *)s1814_obj)[0x121] == 1);

    static uint32_t f138_obj[0x13c / 4];
    set_field_138_if_nonzero(f138_obj, 0);
    assert(f138_obj[0x138 / 4] == 0);
    set_field_138_if_nonzero(f138_obj, 0x77);
    assert(f138_obj[0x138 / 4] == 0x77);

    static uint32_t pop244_obj[0x250 / 4];
    static uint32_t pop244_out[1];
    pop244_obj[0x244 / 4] = 0x99;
    pop244_obj[0x24c / 4] = 3;
    pop_field_244(pop244_obj, pop244_out);
    assert(pop244_out[0] == 0x99);
    assert(pop244_obj[0x24c / 4] == 2);

    static uint32_t pop278_obj[0x284 / 4];
    static uint32_t pop278_out[1];
    pop278_obj[0x278 / 4] = 0x88;
    pop278_obj[0x280 / 4] = 4;
    pop_field_278(pop278_obj, pop278_out);
    assert(pop278_out[0] == 0x88);
    assert(pop278_obj[0x280 / 4] == 3);

    static uint32_t f110_obj[0x118 / 4];
    set_field_110_and_clear(f110_obj, 0x55);
    assert(f110_obj[0x110 / 4] == 0x55);
    assert(((uint8_t *)f110_obj)[0x116] == 0);

    static const uint32_t sp_val[1] = { 0x33 };
    static uint32_t sp100_obj[0x108 / 4];
    store_pointed_100(sp100_obj, sp_val);
    assert(sp100_obj[0x100 / 4] == 0x33);
    static uint32_t sp104_obj[0x108 / 4];
    store_pointed_104(sp104_obj, sp_val);
    assert(sp104_obj[0x104 / 4] == 0x33);

    noop_e();

    static float scale_obj[4];
    static float scale_tgt[0x48 / 4];
    scale_obj[0xc / 4] = 2.0f;
    scale_tgt[0x24 / 4] = 3.0f;
    scale_tgt[0x28 / 4] = 4.0f;
    scale_pair_by_field_c(scale_obj, scale_tgt);
    assert(scale_tgt[0x40 / 4] == 6.0f);
    assert(scale_tgt[0x44 / 4] == 8.0f);

    static uint32_t f1c_leaf[1];
    static uint32_t *f1c_inner[1];
    static uint32_t f1c_obj[0x20 / 4];
    f1c_leaf[0] = 0x66;
    f1c_inner[0] = f1c_leaf;
    f1c_obj[0x1c / 4] = 0;
    f1c_obj[1] = (uint32_t)(uintptr_t)f1c_inner;
    assert(get_field_1c_or_pointed(f1c_obj) == 0x66);
    f1c_obj[0x1c / 4] = 0x77;
    assert(get_field_1c_or_pointed(f1c_obj) == 0x77);

    static uint8_t sb_obj[0x24];
    initialize_state_block(sb_obj);
    assert(sb_obj[0x14] == 6);
    assert(*(uint32_t *)(sb_obj + 4) == 0x29);
    assert(*(uint32_t *)(sb_obj + 0x20) == 0);

    static uint32_t s68_inner[0x28 / 4];
    static uint32_t s68_obj[0x6c / 4];
    s68_obj[0x68 / 4] = (uint32_t)(uintptr_t)s68_inner;
    static const uint32_t s68_val[1] = { 0x44 };
    store_pointed_68_24(s68_obj, s68_val);
    assert(s68_inner[0x24 / 4] == 0x44);

    static uint8_t a19_obj[0x1a];
    a19_obj[0x19] = 0;
    assert(advance_state_byte_19(a19_obj) == 1);
    a19_obj[0x19] = 2;
    assert(advance_state_byte_19(a19_obj) == 2);

    static uint8_t a4d_obj[0x4e];
    a4d_obj[0x4d] = 0;
    assert(advance_state_byte_4d(a4d_obj) == 2);
    a4d_obj[0x4d] = 3;
    assert(advance_state_byte_4d(a4d_obj) == 4);
    a4d_obj[0x4d] = 1;
    assert(advance_state_byte_4d(a4d_obj) == 0);

    static uint8_t sw34_obj[0x36];
    *(uint16_t *)(sw34_obj + 0x34) = 0x11;
    assert(swap_halfword_34(sw34_obj, 0x22) == 0x11);
    assert(*(uint16_t *)(sw34_obj + 0x34) == 0x22);

    static uint8_t sw36_obj[0x38];
    *(uint16_t *)(sw36_obj + 0x36) = 0xfffe;
    assert(swap_halfword_36_bit0(sw36_obj, 1) == 0);
    assert(*(uint16_t *)(sw36_obj + 0x36) == 0xffff);

    static uint8_t sw38_obj[0x39];
    sw38_obj[0x38] = 0x55;
    assert(swap_byte_38(sw38_obj, 0xaa) == 0x55);
    assert(sw38_obj[0x38] == 0xaa);

    static uint8_t cb4_obj[5];
    cb4_obj[4] = 7;
    clear_byte_4(cb4_obj);
    assert(cb4_obj[4] == 0);

    static uint32_t cw0_obj[1];
    static uint16_t cw0_tgt[7];
    cw0_obj[0] = 9;
    clear_word_0_and_set_c(cw0_obj, cw0_tgt, 0x88);
    assert(cw0_obj[0] == 0);
    assert(cw0_tgt[6] == 0x88);

    static uint32_t crb3_obj[4];
    crb3_obj[0] = 1;
    clear_record_with_byte_3(crb3_obj);
    assert(crb3_obj[0] == 0);
    assert(((uint8_t *)crb3_obj)[0xc] == 0);

    static uint32_t bA[0x1440 / 4];
    clear_word_field_4(bA); assert(bA[1] == 0);
    static uint8_t bB[6]; clear_byte_pair_4_5(bB); assert(bB[4] == 0 && bB[5] == 0);
    static uint8_t bC[0x1439]; set_byte_field_1438(bC, 0x42); assert(bC[0x1438] == 0x42);
    static uint32_t bD[0x274 / 4]; set_word_fields_26c_270(bD, 1, 2); assert(bD[0x26c / 4] == 1 && bD[0x270 / 4] == 2);
    static uint32_t bE[0xb4 / 4]; bE[0xb0 / 4] = 9; clear_word_b0(bE); assert(bE[0xb0 / 4] == 0);
    static uint32_t bF[0x48 / 4]; bF[0x44 / 4] = 0xff; clear_flag_bits(bF, 3); assert((bF[0x44 / 4] & 8) == 0);
    static uint32_t bG[0x48 / 4]; clear_fields_40_44(bG); assert(bG[0x40 / 4] == 0 && bG[0x44 / 4] == 0);
    static uint32_t bH[3]; set_word_and_halfword(bH, 0x11, 0x22); assert((bH[0] & 0xffff00ffu) != 0 || bH[0] == 0x11); assert(*(uint16_t *)((uint8_t *)bH + 1) == 0x22);
    static uint8_t bI[0xb]; set_halfword_8_and_byte_10(bI, 0x33); assert(*(uint16_t *)(bI + 8) == 0x33 && bI[10] == 1);
    static uint32_t bJ[0x68 / 4]; clear_word_60_64(bJ); assert(bJ[0x60 / 4] == 0);
    static uint32_t bK[0x74 / 4]; clear_fields_6c_70(bK); assert(bK[0x6c / 4] == 0);
    static uint32_t bL[0xac / 4]; clear_word_a8(bL); assert(bL[0xa8 / 4] == 0);
    static uint32_t bM[0x40 / 4]; clear_word_3c(bM); assert(bM[0x3c / 4] == 0);
    static uint32_t bN[0x44 / 4]; clear_word_40(bN); assert(bN[0x40 / 4] == 0);
    static uint8_t bO[0x100]; bO[0xb8] = 1; set_indexed_byte_d4(bO, 0x99); assert(bO[1 + 0xd4] == 0x99);
    static uint32_t bP[4]; bP[2] = 5; bP[3] = 6; copy_fields_8_c(bP); assert(bP[1] == 5 && bP[2] == 6);
    static uint32_t bQ[1]; set_word_1000_and_byte_1(bQ); assert(((uint8_t *)bQ)[0] == 0xe8 && ((uint8_t *)bQ)[1] == 1);
    static uint32_t bR[1]; set_first_word_1(bR); assert(bR[0] == 1);
    static uint8_t bS[2]; store_bytes_split(bS, 0x1234); assert(bS[0] == 0x12 && bS[1] == 0x34);

    static uint32_t si184[0x18c / 4]; store_indexed_184(si184, 1, 0x99); assert(si184[0x184 / 4 + 1] == 0x99);
    static uint32_t cw4[2]; cw4[1] = 5; clear_word_field_4_b(cw4); assert(cw4[1] == 0);
    static uint32_t cpw[2]; cpw[0] = 1; clear_pair_words(cpw); assert(cpw[0] == 0 && cpw[1] == 0);
    static uint32_t sfw[1]; set_first_word_1_b(sfw); assert(sfw[0] == 1);
    static uint8_t tb2[1]; tb2[0] = 2; assert(test_bit_2(tb2) == 1); tb2[0] = 0; assert(test_bit_2(tb2) == 0);
    static uint8_t c179[0x17a]; c179[0x179] = 5; clear_byte_179(c179); assert(c179[0x179] == 0);
    static uint8_t tog1[2]; tog1[1] = 0; toggle_byte_1(tog1); assert(tog1[1] == 1); toggle_byte_1(tog1); assert(tog1[1] == 0);
    static uint8_t c7880[0x81]; c7880[0x80] = 1; clear_bytes_78_80(c7880); assert(c7880[0x80] == 0 && c7880[0x78] == 0);
    static uint32_t sp1c[0x24 / 4]; set_pair_1c_20(sp1c, 0x11, 0x22); assert(sp1c[0x1c / 4] == 0x11 && sp1c[0x20 / 4] == 0x22);
    static uint32_t aln_next[1]; static uint32_t aln_node[1];
    aln_next[0] = 0; aln_node[0] = (uint32_t)(uintptr_t)aln_next;
    advance_list_node(aln_node); assert(aln_node[0] == 0);
    static uint32_t shp_obj[1]; static uint32_t shp_node[1];
    shp_obj[0] = 0x777; swap_head_pointer(shp_obj, shp_node);
    assert(shp_node[0] == 0x777 && shp_obj[0] == (uint32_t)(uintptr_t)shp_node);
    static uint8_t sb17[0x18]; sb17[0x17] = 5; set_byte_17_if_different(sb17, 5); assert(sb17[0x17] == 5); set_byte_17_if_different(sb17, 7); assert(sb17[0x17] == 7);
    static uint32_t cf1a0[0x1a8 / 4]; cf1a0[0x1a0 / 4] = 1; clear_fields_1a0(cf1a0); assert(cf1a0[0x1a0 / 4] == 0);
    static uint32_t csw[6]; csw[5] = 9; clear_six_words_and_byte(csw); assert(csw[5] == 0 && ((uint8_t *)csw)[0x11] == 0);

    assert(compute_stride_1b8(0) == 0x1b8);
    assert(compute_stride_1b8(2) == 3 * 0x1b8);
    assert(compute_stride_60(3) == 3 * 0x60);

    static uint32_t pb14_blk[0x18 / 4];
    ((uint8_t *)pb14_blk)[0x14] = 0x77;
    static uint32_t pb14_obj[2];
    pb14_obj[1] = (uint32_t)(uintptr_t)pb14_blk;
    assert(get_pointed_byte_14(pb14_obj, 0) == 0x77);

    assert(get_constant_23() == 0x23);

    static uint32_t hw38_obj[0x3c / 4];
    hw38_obj[0x38 / 4] = 0xffff0000;
    assert(get_halfword_38_masked(hw38_obj) == 0);
    hw38_obj[0x38 / 4] = 0xabcd;
    assert(get_halfword_38_masked(hw38_obj) == 0xabcd);

    assert(byte_swap_halfword(0x1234) == 0x3412);

    static uint32_t cf84_obj[4];
    cf84_obj[2] = 0x99;
    copy_field_8_to_4(cf84_obj);
    assert(cf84_obj[1] == 0x99 && cf84_obj[3] == 0);

    static const uint32_t sp1014_val[2] = { 0x11, 0x22 };
    static uint32_t sp1014_obj[0x18 / 4];
    store_pair_10_14(sp1014_obj, sp1014_val);
    assert(sp1014_obj[0x10 / 4] == 0x11 && sp1014_obj[0x14 / 4] == 0x22);

    static uint8_t cbw_obj[0x11];
    cbw_obj[0] = 1;
    *(uint32_t *)(cbw_obj + 1) = 2;
    clear_byte_and_words(cbw_obj);
    assert(cbw_obj[0] == 0);
    assert(*(uint32_t *)(cbw_obj + 1) == 0);

    static uint8_t cbf4_obj[5];
    cbf4_obj[4] = 9;
    clear_byte_field_4(cbf4_obj);
    assert(cbf4_obj[4] == 0);

    assert(get_indexed_halfword_address(0x1000, 5) == 0x1000 + 10 + 0x10c);
    assert(get_indexed_halfword_address(0x1000, 0x10) == 0);

    static uint32_t hfs_obj[0x318 / 4];
    ((int8_t *)hfs_obj)[0x316] = 0;
    assert(has_flag_and_subobject(hfs_obj) == 0);
    static uint32_t hfs_inner[1];
    hfs_obj[0x310 / 4] = (uint32_t)(uintptr_t)hfs_inner;
    ((int8_t *)hfs_obj)[0x316] = 1;
    assert(has_flag_and_subobject(hfs_obj) == 1);

    noop_l();
    noop_m();
    static uint8_t b358_obj[0x359];
    b358_obj[0x358] = 5;
    clear_byte_358(b358_obj);
    assert(b358_obj[0x358] == 0);

    static uint8_t cr48_obj[0xc];
    *(uint16_t *)(cr48_obj + 4) = 5;
    clear_record_4_8(cr48_obj);
    assert(*(uint16_t *)(cr48_obj + 4) == 0 && *(uint32_t *)(cr48_obj + 8) == 0);

    static uint32_t cw18_obj[7]; cw18_obj[0x18 / 4] = 9; clear_word_18(cw18_obj); assert(cw18_obj[0x18 / 4] == 0);
    static uint32_t cw8_obj[3]; cw8_obj[8 / 4] = 9; clear_word_8(cw8_obj); assert(cw8_obj[8 / 4] == 0);
    static uint32_t cw4_obj[2]; cw4_obj[1] = 9; clear_word_4(cw4_obj); assert(cw4_obj[1] == 0);
    static uint32_t cw250_obj[0x254 / 4]; cw250_obj[0x250 / 4] = 9; clear_word_250(cw250_obj); assert(cw250_obj[0x250 / 4] == 0);

    static uint32_t sb14_sub[6];
    assert(set_byte_14_if_nonzero(0, sb14_sub) == 1);
    assert(((uint8_t *)sb14_sub)[0x14] == 3);
    assert(set_byte_14_if_nonzero(0, 0) == 0);

    static uint8_t f7t_target[0xf8];
    static uint32_t f7t_mid[0xb10 / 4];
    static uint32_t f7t_obj[2];
    f7t_mid[0xb08 / 4] = (uint32_t)(uintptr_t)f7t_target;
    f7t_obj[1] = (uint32_t)(uintptr_t)f7t_mid;
    set_byte_f7_to_1(f7t_obj);
    assert(f7t_target[0xf7] == 1);
    set_byte_f7_to_fa(f7t_obj);
    assert(f7t_target[0xf7] == 0xfa);

    static uint8_t b9091_obj[0x92];
    set_byte_90_and_91(b9091_obj, 0x11, 0x22);
    assert(b9091_obj[0x90] == 0x11 && b9091_obj[0x91] == 0x22);

    static uint8_t abt_obj[2];
    abt_obj[0] = 5;
    advance_byte_by_two(abt_obj);
    assert(abt_obj[1] == 7);

    static uint8_t sb48_obj[0xc];
    set_byte_4_and_word_8(sb48_obj, 0x42, 0x1234);
    assert(sb48_obj[4] == 0x42 && *(uint32_t *)(sb48_obj + 8) == 0x1234);

    static uint8_t cb4w_obj[0x11];
    cb4w_obj[0] = 1;
    *(uint32_t *)(cb4w_obj + 1) = 2;
    clear_byte_and_four_words(cb4w_obj);
    assert(cb4w_obj[0] == 0 && *(uint32_t *)(cb4w_obj + 0xd) == 0);

    static uint8_t ipr_obj[0xc];
    assert(initialize_pair_record(ipr_obj, 0x99) == 1);
    assert(ipr_obj[0] == 0 && *(uint32_t *)(ipr_obj + 8) == 0x99);

    static uint32_t b08_obj[0xb0c / 4];
    b08_obj[0xb08 / 4] = 0x100;
    assert(get_word_b08_offset_4c(b08_obj) == 0x100 + 0x4c);

    noop_o();

    static uint32_t cw20[9]; cw20[0x20 / 4] = 5; clear_word_20(cw20); assert(cw20[0x20 / 4] == 0);
    static uint32_t sw1d0[0x1d4 / 4]; static uint32_t sw1d0n[1];
    set_word_1d0_and_link(sw1d0, sw1d0n); assert(sw1d0[0x1d0 / 4] == (uint32_t)(uintptr_t)sw1d0n && sw1d0n[0] == (uint32_t)(uintptr_t)sw1d0);
    static uint8_t sb481[0x483]; set_byte_pair_481_482(sb481, 0x11, 0x22); assert(sb481[0x481] == 0x11 && sb481[0x482] == 0x22);
    static uint8_t oh8[0xea]; *(uint16_t *)(oh8 + 0xe8) = 0; or_halfword_e8_10(oh8); assert(*(uint16_t *)(oh8 + 0xe8) == 0x10);
    static uint32_t ow8[0x4c / 4]; ow8[0x48 / 4] = 0; or_word_48_8(ow8); assert((ow8[0x48 / 4] & 8) == 8);
    static uint32_t ow2[0x4c / 4]; assert(or_word_48_2_if_nonzero(ow2, 1) == 1 && (ow2[0x48 / 4] & 2) == 2); assert(or_word_48_2_if_nonzero(ow2, 0) == 0);
    static uint32_t ow1[0x4c / 4]; assert(or_word_48_1_if_nonzero(ow1, 1) == 1 && (ow1[0x48 / 4] & 1) == 1);
    static uint8_t chc[0xe]; *(uint16_t *)(chc + 0xc) = 9; clear_halfword_c(chc); assert(*(uint16_t *)(chc + 0xc) == 0);
    static const uint32_t sp244[2] = { 1, 2 }; static uint32_t sp244o[0x24c / 4]; store_pointed_244_248(sp244o, sp244); assert(sp244o[0x244 / 4] == 1 && sp244o[0x248 / 4] == 2);
    static uint32_t sp250o[0x258 / 4]; store_pointed_250_254(sp250o, sp244); assert(sp250o[0x250 / 4] == 1 && sp250o[0x254 / 4] == 2);
    static uint32_t sp25co[0x264 / 4]; store_pointed_25c_260(sp25co, sp244); assert(sp25co[0x25c / 4] == 1 && sp25co[0x260 / 4] == 2);
    static uint32_t sid80_inner[0xd0 / 4]; static uint32_t sid80_obj[5]; sid80_obj[0x10 / 4] = (uint32_t)(uintptr_t)sid80_inner;
    store_indexed_d0_80(sid80_obj, 0, 0x77); assert(sid80_inner[0x80 / 4] == 0x77);
    static uint8_t chb[0xa]; *(uint16_t *)(chb + 8) = 0xff; clear_halfword_bit(chb, 3); assert((*(uint16_t *)(chb + 8) & 8) == 0);
    static uint8_t shb[0xa]; *(uint16_t *)(shb + 8) = 0; set_halfword_bit(shb, 5); assert((*(uint16_t *)(shb + 8) & 0x20) == 0x20);
    static uint8_t sb6[0x4fb]; sb6[6] = 5; set_byte_6_and_mark(sb6, 5); assert(sb6[0x4fa] == 0); set_byte_6_and_mark(sb6, 7); assert(sb6[6] == 7 && sb6[0x4fa] == 1);
    static uint8_t srp_obj[0x17c]; set_sub_record_pointer((uint32_t *)srp_obj, 2); assert(*(uint32_t *)(srp_obj + 0x178) == (uint32_t)(uintptr_t)(srp_obj + 2 * 0x2c + 0x120));
    static uint32_t acv_obj[0x138 / 4 + 2]; acv_obj[0x134 / 4] = 0; append_counted_value(acv_obj, 0x55); assert(acv_obj[0x134 / 4] == 1 && acv_obj[1] == 0x55);
    noop_q();

    static uint32_t gph22_inner[0x24 / 4];
    *(uint16_t *)((uint8_t *)gph22_inner + 0x22) = 0x777;
    static uint32_t gph22_obj[2];
    gph22_obj[1] = (uint32_t)(uintptr_t)gph22_inner;
    assert(get_pointed_halfword_22(gph22_obj) == 0x777);
    gph22_obj[1] = 0;
    assert(get_pointed_halfword_22(gph22_obj) == 0);

    static uint32_t gfi8c_obj[0x90 / 4];
    gfi8c_obj[0x8c / 4] = 0x42;
    assert(get_float_as_int_8c(gfi8c_obj) == 0x42);

    static const uint32_t triple_val[3] = { 1, 2, 3 };
    static uint32_t st5c_obj[0x68 / 4];
    store_triple_5c(st5c_obj, triple_val);
    assert(st5c_obj[0x5c / 4] == 1 && st5c_obj[0x64 / 4] == 3);
    static uint32_t st50_obj[0x5c / 4];
    store_triple_50(st50_obj, triple_val);
    assert(st50_obj[0x50 / 4] == 1 && st50_obj[0x58 / 4] == 3);
    static uint32_t st44_obj[0x50 / 4];
    store_triple_44(st44_obj, triple_val);
    assert(st44_obj[0x44 / 4] == 1 && st44_obj[0x4c / 4] == 3);

    static uint8_t tlb_obj[1];
    tlb_obj[0] = 1;
    assert(test_low_bit(tlb_obj) == 1);
    tlb_obj[0] = 0;
    assert(test_low_bit(tlb_obj) == 0);

    static uint32_t gieb_tbl[3];
    static uint32_t gieb_data[8];
    gieb_data[3] = 0x99;
    gieb_tbl[2] = (uint32_t)(uintptr_t)gieb_data;
    static uint32_t gieb_obj[0x114 / 4];
    gieb_obj[0x110 / 4] = (uint32_t)(uintptr_t)gieb_tbl;
    assert(get_indexed_entry_by_byte(gieb_obj, 3) == 0x99);
    assert(get_indexed_entry_by_byte(gieb_obj, 0xff) == 0);

    static uint32_t hbs[2];
    set_high_bitset_bit(hbs, 3);
    assert((hbs[0] & 0x10000000u) == 0x10000000u);
    set_high_bitset_bit(hbs, 33);
    assert((hbs[1] & 0x40000000u) == 0x40000000u);
    clear_high_bitset_bit(hbs, 3);
    assert((hbs[0] & 0x10000000u) == 0);

    static uint32_t sq2e0_obj[0x2f0 / 4];
    set_quad_2e0(sq2e0_obj, 1, 2, 3, 4);
    assert(sq2e0_obj[0x2e0 / 4] == 1 && sq2e0_obj[0x2ec / 4] == 4);

    static uint8_t gsb148_obj[0x149];
    gsb148_obj[0x148] = 0xfe;
    assert(get_signed_byte_148(gsb148_obj) == -2);

    static uint32_t gira0_obj[0x2c / 4];
    gira0_obj[0x28 / 4] = 0x1000;
    assert(get_indexed_record_a0(gira0_obj, 2) == 0x1000 + 2 * 0xa0);

    noop_s();

    static uint32_t gif10c_obj[0x110 / 4];
    gif10c_obj[0x10c / 4] = 0x1000;
    assert(get_indexed_field_10c(gif10c_obj, 2) == 0x1000 + 2 * 0x1c);

    static uint8_t glb3c_obj[0x3d];
    glb3c_obj[0x3c] = 5;
    assert(get_low_bit_3c(glb3c_obj) == 1);
    glb3c_obj[0x3c] = 4;
    assert(get_low_bit_3c(glb3c_obj) == 0);

    static uint32_t gntw_inner[0x34 / 4];
    gntw_inner[0x30 / 4] = 0;
    static uint32_t gntw_leaf[3];
    gntw_leaf[2] = 0x55;
    gntw_inner[0] = (uint32_t)(uintptr_t)gntw_leaf;
    static uint32_t gntw_obj[2];
    gntw_obj[1] = (uint32_t)(uintptr_t)gntw_inner;
    assert(get_nested_table_word(gntw_obj) == 0x55);

    noop_t();

    static uint8_t arena_obj[0x5d4];
    ((uint32_t *)arena_obj)[0x5d0 / 4] = 0;
    uint32_t arena_slot = allocate_from_arena((uint32_t *)arena_obj, 0x20);
    assert(arena_slot == (uint32_t)(uintptr_t)(arena_obj + 0x10));
    assert(((uint32_t *)arena_obj)[0x5d0 / 4] == 0x20);
    ((uint32_t *)arena_obj)[0x5d0 / 4] = 0x5c0;
    assert(allocate_from_arena((uint32_t *)arena_obj, 2) == 0);

    static uint32_t bc8_obj[0xbd0 / 4];
    set_pair_bc8(bc8_obj, 0x11, 0x22);
    assert(bc8_obj[0xbc8 / 4] == 0x11 && bc8_obj[0xbcc / 4] == 0x22);

    static const uint32_t cpw_src[2] = { 0x1122, 0x3344 };
    static uint32_t cpw_dest[2];
    copy_pair_with_halfword(cpw_dest, cpw_src);
    assert(cpw_dest[0] == 0x1122);

    static uint32_t cpb_dest[2];
    copy_pair_with_byte(cpb_dest, cpw_src);
    assert(cpb_dest[0] == 0x1122);

    static uint32_t cw18b[7];
    cw18b[0x18 / 4] = 5; clear_word_18_b(cw18b); assert(cw18b[0x18 / 4] == 0);

    static uint32_t cew_obj[0x24 / 4];
    cew_obj[0x20 / 4] = 9; clear_eight_words(cew_obj); assert(cew_obj[0x20 / 4] == 0);

    static uint32_t cwh8_obj[3];
    cwh8_obj[1] = 1; *(uint16_t *)((uint8_t *)cwh8_obj + 8) = 2;
    clear_word_4_and_halfword_8(cwh8_obj);
    assert(cwh8_obj[1] == 0);

    static uint32_t cwh1_obj[2];
    cwh1_obj[0] = 1; *(uint16_t *)((uint8_t *)cwh1_obj + 4) = 2;
    clear_word_and_halfword_1(cwh1_obj);
    assert(cwh1_obj[0] == 0);

    static uint8_t sb10_obj[0x11];
    set_byte_10_1(sb10_obj); assert(sb10_obj[0x10] == 1);

    static uint8_t cbp12_obj[3];
    cbp12_obj[1] = 1; cbp12_obj[2] = 2; clear_byte_pair_1_2(cbp12_obj);
    assert(cbp12_obj[1] == 0 && cbp12_obj[2] == 0);

    static uint32_t cfwc_obj[1];
    cfwc_obj[0] = 7; clear_first_word_c(cfwc_obj); assert(cfwc_obj[0] == 0);

    static uint32_t sw1b8_obj[0x1bc / 4];
    sw1b8_obj[0x1b8 / 4] = 5; set_word_1b8_if_different(sw1b8_obj, 5); assert(sw1b8_obj[0x1b8 / 4] == 5);
    set_word_1b8_if_different(sw1b8_obj, 9); assert(sw1b8_obj[0x1b8 / 4] == 9);

    static uint32_t spw10_obj[1]; static uint32_t spw10_sub[5];
    set_pointed_word_10_and_clear(spw10_obj, spw10_sub, 0x88);
    assert(spw10_sub[0x10 / 4] == 0x88 && spw10_obj[0] == 0);

    static uint32_t cwb1_obj[1];
    cwb1_obj[0] = 3; clear_word_and_byte_1(cwb1_obj); assert(cwb1_obj[0] == 0 && ((uint8_t *)cwb1_obj)[1] == 0);

    static uint32_t ssl4_obj[4];
    set_self_link_4(ssl4_obj);
    assert(ssl4_obj[1] == (uint32_t)(uintptr_t)(ssl4_obj + 1));
    assert(ssl4_obj[2] == (uint32_t)(uintptr_t)(ssl4_obj + 1));
    assert(ssl4_obj[3] == 0);

    static uint32_t a184_obj[0x188 / 4];
    a184_obj[0x184 / 4] = 100;
    add_to_word_184(a184_obj, 23);
    assert(a184_obj[0x184 / 4] == 123);

    static uint8_t sb1ac6_obj[0x1ac7];
    set_byte_1ac6_ff(sb1ac6_obj);
    assert(sb1ac6_obj[0x1ac6] == 0xff);

    static uint32_t cwph_obj[3];
    cwph_obj[0] = 1; cwph_obj[1] = 2; *(uint16_t *)(cwph_obj + 2) = 3;
    clear_word_pair_and_halfword(cwph_obj);
    assert(cwph_obj[0] == 0 && cwph_obj[1] == 0);

    static const uint32_t sq58_val[4] = { 1, 2, 3, 4 };
    static uint32_t sq58_obj[0x68 / 4];
    store_quad_58(sq58_obj, sq58_val);
    assert(sq58_obj[0x58 / 4] == 1 && sq58_obj[0x64 / 4] == 4);

    static uint8_t cp480_obj[0x483];
    ((int8_t *)cp480_obj)[0x480] = 5;
    ((int8_t *)cp480_obj)[0x481] = 5;
    cp480_obj[0x482] = 0;
    assert(check_pair_480_481(cp480_obj) == 0);
    cp480_obj[0x482] = 7;
    assert(check_pair_480_481(cp480_obj) == 1);
    ((int8_t *)cp480_obj)[0x481] = 6;
    assert(check_pair_480_481(cp480_obj) == 1);

    static uint8_t ci1fd_obj[0x202];
    ((int8_t *)ci1fd_obj)[0x1fd] = 0;
    ci1fd_obj[0x201] = 0;
    assert(check_idle_1fd_201(ci1fd_obj) == 1);
    ci1fd_obj[0x201] = 5;
    assert(check_idle_1fd_201(ci1fd_obj) == 0);

    static uint32_t crlh_obj[7];
    crlh_obj[5] = 9; crlh_obj[6] = 9;
    clear_record_with_list_head(crlh_obj);
    assert(crlh_obj[5] == 0 && crlh_obj[6] == 0);

    static uint32_t gipw_inner[4];
    gipw_inner[2] = 0x66;
    static uint32_t *gipw_tbl[1];
    gipw_tbl[0] = gipw_inner;
    static uint32_t gipw_obj[3];
    gipw_obj[2] = (uint32_t)(uintptr_t)gipw_tbl;
    assert(get_indexed_pointed_word(gipw_obj, 2) == 0x66);

    noop_w();
    noop_x();
    noop_y();
    noop_z();

    assert(is_decimal_digit(0x30) == 1);
    assert(is_decimal_digit(0x39) == 1);
    assert(is_decimal_digit(0x2f) == 0);
    assert(is_decimal_digit(0x3a) == 0);

    static uint32_t cfc14_obj[6];
    cfc14_obj[0xc / 4] = 0x55;
    copy_field_c_to_14(cfc14_obj);
    assert(cfc14_obj[0x14 / 4] == 0x55);

    static uint32_t cp01_obj[2];
    cp01_obj[0] = 1; cp01_obj[1] = 2;
    clear_pair_0_1(cp01_obj);
    assert(cp01_obj[0] == 0 && cp01_obj[1] == 0);

    static uint32_t sw3c_obj[0x40 / 4];
    set_word_3c_offset_8(sw3c_obj, 0x100);
    assert(sw3c_obj[0x3c / 4] == 0x108);
    static uint32_t sw38w_obj[0x3c / 4];
    set_word_38_offset_8(sw38w_obj, 0x200);
    assert(sw38w_obj[0x38 / 4] == 0x208);

    static uint32_t ct0_obj[3];
    ct0_obj[0] = 1; ct0_obj[2] = 3;
    clear_triple_0(ct0_obj);
    assert(ct0_obj[0] == 0 && ct0_obj[2] == 0);

    static uint8_t sb2c_obj[0x30];
    sb2c_obj[0x2c] = 5;
    set_byte_2c_if_different(sb2c_obj, 5);
    assert((*(uint16_t *)(sb2c_obj + 0x20) & 8) == 0);
    set_byte_2c_if_different(sb2c_obj, 7);
    assert(sb2c_obj[0x2c] == 7 && (*(uint16_t *)(sb2c_obj + 0x20) & 8) == 8);

    static uint8_t sb2d_obj[0x2e];
    sb2d_obj[0x2d] = 1;
    set_byte_2d_if_different(sb2d_obj, 1);
    assert(sb2d_obj[0x2d] == 1);

    static uint8_t sb15_obj[0x18];
    set_byte_15_1_and_clear_17(sb15_obj);
    assert(sb15_obj[0x15] == 1 && sb15_obj[0x17] == 0);

    static uint8_t sb83_obj[0x84];
    set_byte_83(sb83_obj, 0x99);
    assert(sb83_obj[0x83] == 0x99);

    static uint8_t sbf4_obj[0xf5];
    set_byte_f4(sbf4_obj, 0xab);
    assert(sbf4_obj[0xf4] == 0xab);

    static uint8_t sih10c_obj[0x114];
    set_indexed_halfword_10c(sih10c_obj, 2, 0x1234);
    assert(*(uint16_t *)(sih10c_obj + 2 * 2 + 0x10c) == 0x1234);

    static uint8_t sbf0_obj[0xf1];
    set_byte_f0(sbf0_obj, 0xcd);
    assert(sbf0_obj[0xf0] == 0xcd);

    static uint32_t sp8c90_obj[0x94 / 4];
    set_pair_8c_90(sp8c90_obj, 0x11, 0x22);
    assert(sp8c90_obj[0x8c / 4] == 0x11 && sp8c90_obj[0x90 / 4] == 0x22);

    static uint32_t a16c_obj[0x170 / 4];
    a16c_obj[0x16c / 4] = 50;
    add_to_word_16c(a16c_obj, 25);
    assert(a16c_obj[0x16c / 4] == 75);

    static uint32_t ow48c_obj[0x4c / 4];
    ow48c_obj[0x48 / 4] = 0;
    or_word_48_c400(ow48c_obj);
    assert((ow48c_obj[0x48 / 4] & 0xc400) == 0xc400);

    static uint32_t sw4_obj[2];
    set_word_4(sw4_obj, 0x77);
    assert(sw4_obj[1] == 0x77);

    static uint32_t iw1c_obj[8];
    iw1c_obj[0x1c / 4] = 41;
    increment_word_1c(iw1c_obj);
    assert(iw1c_obj[0x1c / 4] == 42);

    static uint32_t sp146c_obj[0x70 / 4];
    set_pair_14_6c(sp146c_obj, 0x33, 0x44);
    assert(sp146c_obj[0x14 / 4] == 0x33 && sp146c_obj[0x6c / 4] == 0x44);

    static uint8_t cha0_obj[0xa4];
    *(uint16_t *)(cha0_obj + 0xa0) = 9;
    *(uint16_t *)(cha0_obj + 0xa2) = 9;
    clear_halfwords_a0_a2(cha0_obj);
    assert(*(uint16_t *)(cha0_obj + 0xa0) == 0);

    static uint32_t cfwd_obj[1];
    cfwd_obj[0] = 8;
    clear_first_word_d(cfwd_obj);
    assert(cfwd_obj[0] == 0);

    noop_aa();
    noop_ab();
    noop_ac();
    noop_ad();

    static uint32_t cw0e_obj[1]; cw0e_obj[0] = 5; clear_word_0_e(cw0e_obj); assert(cw0e_obj[0] == 0);
    static uint32_t cw0f_obj[1]; cw0f_obj[0] = 5; clear_word_0_f(cw0f_obj); assert(cw0f_obj[0] == 0);

    static uint8_t sb1621_obj[0x1622]; set_byte_1621_1(sb1621_obj); assert(sb1621_obj[0x1621] == 1);

    static uint8_t sthp_obj[0x9e];
    set_triple_halfword_pairs(sthp_obj, 1, 2, 3);
    assert(*(uint16_t *)(sthp_obj + 0x94) == 1 && *(uint16_t *)(sthp_obj + 0x9a) == 3);

    static uint8_t cb1d08_obj[0x1d09]; cb1d08_obj[0x1d08] = 5; clear_byte_1d08(cb1d08_obj); assert(cb1d08_obj[0x1d08] == 0);
    static uint8_t cb2e05_obj[0x2e06]; cb2e05_obj[0x2e05] = 5; clear_byte_2e05(cb2e05_obj); assert(cb2e05_obj[0x2e05] == 0);

    static uint32_t cp48_obj[3]; cp48_obj[1] = 1; cp48_obj[2] = 2;
    clear_pair_4_8(cp48_obj); assert(cp48_obj[1] == 0 && cp48_obj[2] == 0);

    static uint32_t aw4_obj[2]; aw4_obj[1] = 0xff; and_word_4_fffd(aw4_obj); assert((aw4_obj[1] & 2) == 0);

    static uint8_t sb14_obj[0x15]; set_byte_14_10(sb14_obj); assert(sb14_obj[0x14] == 10);
    static uint8_t sb970_obj[0x971]; set_byte_970_1(sb970_obj); assert(sb970_obj[0x970] == 1);
    static uint8_t cbf88_obj[0xf89]; cbf88_obj[0xf88] = 1; clear_byte_f88(cbf88_obj); assert(cbf88_obj[0xf88] == 0);
    static uint8_t sbf88_obj[0xf89]; set_byte_f88_1(sbf88_obj); assert(sbf88_obj[0xf88] == 1);
    static uint8_t sb150e_obj[0x150f]; set_byte_150e(sb150e_obj, 0x42); assert(sb150e_obj[0x150e] == 0x42);
    static uint8_t sb150d_obj[0x150e]; set_byte_150d(sb150d_obj, 0x43); assert(sb150d_obj[0x150d] == 0x43);
    static uint8_t cb428_obj[0x429]; cb428_obj[0x428] = 5; clear_byte_428(cb428_obj); assert(cb428_obj[0x428] == 0);
    static uint32_t cw3e4_obj[0x3e8 / 4]; cw3e4_obj[0x3e4 / 4] = 9; clear_word_3e4(cw3e4_obj); assert(cw3e4_obj[0x3e4 / 4] == 0);
    static uint8_t sb200_obj[0x201]; set_byte_200_1(sb200_obj); assert(sb200_obj[0x200] == 1);

    assert(get_constant_10() == 0x10);
    assert(get_constant_4() == 4);
    assert(get_constant_8() == 8);
    noop_bd();
    noop_be();
    noop_bf();
    noop_c0();

    static uint32_t gif10c_b_obj[0x110 / 4];
    gif10c_b_obj[0x10c / 4] = 0x2000;
    assert(get_indexed_field_10c_b(gif10c_b_obj, 3) == 0x2000 + 3 * 0x1c);

    static uint8_t glb3c_b_obj[0x3d];
    glb3c_b_obj[0x3c] = 7;
    assert(get_low_bit_3c_b(glb3c_b_obj) == 1);
    glb3c_b_obj[0x3c] = 6;
    assert(get_low_bit_3c_b(glb3c_b_obj) == 0);

    static uint32_t gntw8_inner[0x34 / 4];
    gntw8_inner[0x30 / 4] = 0;
    static uint32_t gntw8_leaf[3];
    gntw8_leaf[2] = 0x99;
    gntw8_inner[0] = (uint32_t)(uintptr_t)gntw8_leaf;
    static uint32_t gntw8_obj[2];
    gntw8_obj[1] = (uint32_t)(uintptr_t)gntw8_inner;
    assert(get_nested_word_8(gntw8_obj) == 0x99);

    noop_c1();

    static uint32_t af3c_obj[0x40 / 4];
    af3c_obj[0x3c / 4] = 0x100;
    assert(add_field_3c(af3c_obj) == (uint32_t)(uintptr_t)af3c_obj + 0x100);

    static uint32_t af2c_obj[0x30 / 4];
    af2c_obj[0x2c / 4] = 0x200;
    assert(add_field_2c(af2c_obj) == (uint32_t)(uintptr_t)af2c_obj + 0x200);

    static uint32_t afc_obj[4];
    afc_obj[0xc / 4] = 0x10;
    assert(add_field_c(afc_obj) == (uint32_t)(uintptr_t)afc_obj + 0x10);

    static uint32_t af1c_obj[8];
    af1c_obj[0x1c / 4] = 0x20;
    assert(add_field_1c(af1c_obj) == (uint32_t)(uintptr_t)af1c_obj + 0x20);

    static uint32_t af14_obj[6];
    af14_obj[0x14 / 4] = 0x30;
    assert(add_field_14(af14_obj) == (uint32_t)(uintptr_t)af14_obj + 0x30);

    static uint32_t af10_obj[5];
    af10_obj[0x10 / 4] = 0x40;
    assert(add_field_10(af10_obj) == (uint32_t)(uintptr_t)af10_obj + 0x40);

    static uint32_t af4_obj[2];
    af4_obj[4 / 4] = 0x50;
    assert(add_field_4(af4_obj) == (uint32_t)(uintptr_t)af4_obj + 0x50);

    static uint32_t af8_obj[3];
    af8_obj[8 / 4] = 0x60;
    assert(add_field_8(af8_obj) == (uint32_t)(uintptr_t)af8_obj + 0x60);

    noop_c3();
    noop_c4();
    noop_c5();
    noop_c6();

    static uint8_t cb24d_obj[0x24e];
    cb24d_obj[0x24d] = 5;
    assert(clear_byte_24d_and_confirm(cb24d_obj) == 1);
    assert(cb24d_obj[0x24d] == 0);

    static uint32_t cp5458_obj[0x5c / 4];
    cp5458_obj[0x54 / 4] = 1; cp5458_obj[0x58 / 4] = 2;
    clear_pair_54_58(cp5458_obj);
    assert(cp5458_obj[0x54 / 4] == 0 && cp5458_obj[0x58 / 4] == 0);

    static uint8_t sb2a_obj[0x2b];
    set_byte_2a_1(sb2a_obj);
    assert(sb2a_obj[0x2a] == 1);

    static uint32_t cf48_obj[0x1a0 / 4];
    cf48_obj[4 / 4] = 0x11;
    cf48_obj[8 / 4] = 0x22;
    copy_fields_4_8_to_138(cf48_obj);
    assert(cf48_obj[0x138 / 4] == 0x11 && cf48_obj[0x13c / 4] == 0x22);

    static uint8_t ilr_obj[0x24];
    initialize_link_record(ilr_obj);
    assert(ilr_obj[0] == 1 && *(uint32_t *)(ilr_obj + 4) == 0xffffffffu);

    static uint8_t cb52_obj[6];
    clear_byte_5_to_2(cb52_obj);
    assert(cb52_obj[5] == 2);

    static uint32_t crid_dest[4];
    static const uint32_t crid_src[4] = { 0, 0, 0x99, 0 };
    assert(copy_record_if_different(crid_dest, crid_src) == (uint32_t)(uintptr_t)crid_dest);

    assert(is_not_type_8579(0x8578) == 1);
    assert(is_not_type_8579(0x8579) == 0);

    static uint32_t isr_obj[4];
    isr_obj[0] = 9;
    initialize_state_record(isr_obj);
    assert(isr_obj[0] == 0 && ((uint8_t *)isr_obj)[0xd] == 0xff);

    static uint32_t ssl2_obj[4];
    set_self_link_2(ssl2_obj);
    assert(ssl2_obj[2] == (uint32_t)(uintptr_t)(ssl2_obj + 2));
    assert(ssl2_obj[3] == (uint32_t)(uintptr_t)(ssl2_obj + 2));

    noop_c7();
    noop_c8();

    static uint32_t ilrf_obj[0xc0 / 4];
    initialize_link_record_full(ilrf_obj);
    assert(ilrf_obj[1] == 0xffffffffu && ilrf_obj[0x25] == 0);

    static uint32_t itr_obj[8];
    initialize_tagged_record(itr_obj, 0x99);
    assert(itr_obj[0] == 0x10000 && itr_obj[6] == 0x99 && itr_obj[5] == 0);

    static uint32_t itrb_obj[8];
    initialize_tagged_record_b(itrb_obj, 0x88);
    assert(itrb_obj[0] == 0x10000 && itrb_obj[7] == 0x88);

    static uint8_t sp1cc_obj[0x1ce];
    sp1cc_obj[0x1cc] = 1; sp1cc_obj[0x1cd] = 2;
    set_pair_1cc_1cd_if_different(sp1cc_obj, 1, 2);
    assert(sp1cc_obj[0x1cc] == 1 && sp1cc_obj[0x1cd] == 2);
    set_pair_1cc_1cd_if_different(sp1cc_obj, 3, 4);
    assert(sp1cc_obj[0x1cc] == 3 && sp1cc_obj[0x1cd] == 4);

    static uint8_t gs1a_obj[0x1b];
    ((int8_t *)gs1a_obj)[0x1a] = 0;
    assert(get_state_1a_mapped(gs1a_obj) == 1);
    ((int8_t *)gs1a_obj)[0x1a] = 3;
    assert(get_state_1a_mapped(gs1a_obj) == 0);
    ((int8_t *)gs1a_obj)[0x1a] = 4;
    assert(get_state_1a_mapped(gs1a_obj) == 2);

    static uint8_t gs4e_obj[0x4f];
    ((int8_t *)gs4e_obj)[0x4e] = 0;
    assert(get_state_4e_mapped(gs4e_obj) == 2);
    ((int8_t *)gs4e_obj)[0x4e] = 3;
    assert(get_state_4e_mapped(gs4e_obj) == 1);

    noop_c9();
    noop_ca();

    static uint8_t cb5c_obj[0x5d];
    cb5c_obj[0x5c] = 5;
    clear_byte_5c(cb5c_obj);
    assert(cb5c_obj[0x5c] == 0);

    static uint32_t cw034_obj[4];
    clear_word_0_and_byte_3_4(cw034_obj);
    assert(cw034_obj[0] == 0x10000 && ((uint8_t *)cw034_obj)[0xd] == 0);

    static uint32_t cw1011_obj[5];
    clear_word_0_and_byte_10_11(cw1011_obj);
    assert(cw1011_obj[0] == 0x10000 && ((uint8_t *)cw1011_obj)[0x11] == 0);

    static uint32_t cw012_obj[3];
    clear_word_0_1_and_halfword_2(cw012_obj);
    assert(cw012_obj[0] == 0 && cw012_obj[1] == 0);

    static uint8_t sb290_obj[0x291];
    *(int16_t *)(sb290_obj + 0x1c) = 0x102;
    set_byte_290_if_0x102(sb290_obj);
    assert(sb290_obj[0x290] == 1);

    static uint32_t pt818_obj[0x81c / 4];
    static uint32_t pt818_buf[8];
    pt818_obj[0x818 / 4] = (uint32_t)(uintptr_t)pt818_buf;
    push_tagged_818(pt818_obj, 0x77);
    assert(pt818_buf[0] == 0x77 && pt818_buf[1] == 3);
    assert(pt818_obj[0x810 / 4] == 1);

    static uint32_t ptc_obj[0x10 / 4];
    static uint32_t ptc_buf[8];
    ptc_obj[0xc / 4] = (uint32_t)(uintptr_t)ptc_buf;
    push_tagged_c(ptc_obj, 0x88);
    assert(ptc_buf[0] == 0x88 && ptc_buf[1] == 3);
    assert(ptc_obj[4 / 4] == 1);

    noop_cb();

    static uint32_t cw14c_obj[6];
    cw14c_obj[0x14 / 4] = 5;
    clear_word_14_and_set_c(cw14c_obj, 0x99);
    assert(cw14c_obj[0x14 / 4] == 0 && cw14c_obj[0xc / 4] == 0x99);

    static uint32_t csr970c_obj[0x18];
    csr970c_obj[3] = 1; ((uint8_t *)csr970c_obj)[0x16] = 2;
    clear_state_record_970c(csr970c_obj);
    assert(csr970c_obj[3] == 0 && ((uint8_t *)csr970c_obj)[0x16] == 0);

    static uint32_t isr788c_obj[8];
    initialize_state_record_788c(isr788c_obj);
    assert(isr788c_obj[0] == 0 && isr788c_obj[2] == 2 && isr788c_obj[5] == 2);

    static uint8_t sb4ob_obj[5];
    sb4ob_obj[4] = 0;
    set_byte_4_or_bit(sb4ob_obj, 3);
    assert(sb4ob_obj[4] == 8);

    static uint32_t spw3c_inner[0x40 / 4];
    static uint32_t spw3c_obj[0x94 / 4];
    spw3c_obj[0x90 / 4] = (uint32_t)(uintptr_t)spw3c_inner;
    set_pointed_word_3c(spw3c_obj, 0x77);
    assert(spw3c_inner[0x3c / 4] == 0x77);

    static uint8_t sb2f_obj[0x58];
    sb2f_obj[2] = 0;
    set_byte_2_and_flag(sb2f_obj, 1);
    assert(sb2f_obj[2] == 2);

    static uint8_t cb49a_obj[0x49b];
    cb49a_obj[0x49a] = 1;
    *(uint16_t *)(cb49a_obj + 0x234) = 0;
    clear_byte_49a_and_set_234(cb49a_obj);
    assert((*(uint16_t *)(cb49a_obj + 0x234) & 1) == 1);

    static uint8_t csac_dest[0x24];
    static const uint8_t csac_src[1] = { 0x55 };
    copy_state_and_clear(csac_dest, csac_src);
    assert(csac_dest[0] == 0x55 && *(uint32_t *)(csac_dest + 4) == 0);

    static uint32_t cw14wc_obj[6];
    cw14wc_obj[0x14 / 4] = 5;
    clear_word_14_and_set_word_c(cw14wc_obj, 0x88);
    assert(cw14wc_obj[0x14 / 4] == 0 && cw14wc_obj[0xc / 4] == 0x88);

    static uint8_t ft6800_obj[0x28];
    ft6800_obj[0x14] = 0; ft6800_obj[0x15] = 0x68;
    *(uint32_t *)(ft6800_obj + 0x18) = 0x100;
    assert(find_offset_for_type_6800(ft6800_obj) == (uint32_t)(uintptr_t)ft6800_obj + 0x100);
    ft6800_obj[0x14] = 0; ft6800_obj[0x15] = 0;
    ft6800_obj[0x20] = 0; ft6800_obj[0x21] = 0x68;
    *(uint32_t *)(ft6800_obj + 0x24) = 0x200;
    assert(find_offset_for_type_6800(ft6800_obj) == (uint32_t)(uintptr_t)ft6800_obj + 0x200);
    ft6800_obj[0x20] = 0; ft6800_obj[0x21] = 0;
    assert(find_offset_for_type_6800(ft6800_obj) == (uint32_t)(uintptr_t)ft6800_obj + *(uint32_t *)(ft6800_obj + 4));

    static uint8_t gf6800_obj[0x28];
    gf6800_obj[0x14] = 0; gf6800_obj[0x15] = 0x68;
    *(uint32_t *)(gf6800_obj + 0x18) = 0x1234;
    assert(get_field_after_type_6800(gf6800_obj) == 0x1234);
    gf6800_obj[0x14] = 0; gf6800_obj[0x15] = 0;
    gf6800_obj[0x20] = 0; gf6800_obj[0x21] = 0x68;
    *(uint32_t *)(gf6800_obj + 0x24) = 0x5678;
    assert(get_field_after_type_6800(gf6800_obj) == 0x5678);

    static uint32_t gref_rec[4];
    static uint8_t gref_tab[0x30];
    gref_rec[1] = (uint32_t)(uintptr_t)gref_tab;
    gref_rec[3] = 1;
    *(uint32_t *)(gref_tab + 0xc) = 0xaaaa;
    *(uint32_t *)(gref_tab + 0x18) = 0xbbbb;
    assert(get_record_entry_field(gref_rec, 0) == 0xaaaa);
    assert(get_record_entry_field(gref_rec, 1) == 0xbbbb);
    gref_rec[3] = 0;
    assert(get_record_entry_field(gref_rec, 0) == 0);

    static uint32_t siep_out;
    static uint32_t siep_obj[2];
    static uint8_t siep_tab[0x20];
    siep_obj[0] = 0;
    *(uint32_t *)(siep_tab + 4) = 2;
    *(uint32_t *)(siep_tab + 8) = 0x10;
    *(uint32_t *)(siep_tab + 0xc) = 0x20;
    siep_obj[1] = 0;
    *(uint32_t *)((uint8_t *)siep_obj + 4) = (uint32_t)(uintptr_t)siep_tab;
    store_indexed_entry_pointer(&siep_out, siep_obj, 0);
    assert(siep_out == (uint32_t)(uintptr_t)siep_tab + 0x10);
    store_indexed_entry_pointer(&siep_out, siep_obj, 1);
    assert(siep_out == (uint32_t)(uintptr_t)siep_tab + 0x20);
    store_indexed_entry_pointer(&siep_out, siep_obj, 2);
    assert(siep_out == 0);

    static uint8_t mms_obj[0x20];
    mms_obj[0x14] = 2;
    assert(map_mode_to_state((uint32_t)(uintptr_t)mms_obj) == 3);
    mms_obj[0x14] = 3;
    assert(map_mode_to_state((uint32_t)(uintptr_t)mms_obj) == 1);
    mms_obj[0x14] = 4;
    assert(map_mode_to_state((uint32_t)(uintptr_t)mms_obj) == 2);
    mms_obj[0x14] = 0;
    assert(map_mode_to_state((uint32_t)(uintptr_t)mms_obj) == 0);

    static uint8_t cmf_obj[800];
    cmf_obj[0x31e] = 1;
    assert(check_mode_flag((uint32_t)(uintptr_t)cmf_obj) == 1);
    cmf_obj[0x31e] = 2;
    cmf_obj[799] = 0x1e;
    assert(check_mode_flag((uint32_t)(uintptr_t)cmf_obj) == 1);
    cmf_obj[0x31e] = 2;
    cmf_obj[799] = 0;
    assert(check_mode_flag((uint32_t)(uintptr_t)cmf_obj) == 0);
    cmf_obj[0x31e] = 0;
    assert(check_mode_flag((uint32_t)(uintptr_t)cmf_obj) == 0);

    run_batch_e_tests();
    run_batch_f_tests();
    run_batch_g_tests();
    run_batch_h_tests();
    run_batch_i_tests();
    run_batch_j_tests();
    run_batch_k_tests();
    run_batch_l_tests();
    run_batch_m_tests();
    run_batch_n_tests();
    run_batch_o_tests();
    run_batch_p_tests();
    run_batch_q_tests();
    run_batch_r_tests();
    run_batch_s_tests();
    run_batch_t_tests();
    run_batch_u_tests();
    run_batch_v_tests();
    run_batch_w_tests();
    run_batch_x_tests();
    run_batch_y_tests();
    run_batch_z_tests();
    run_batch_a2_tests();
    run_batch_b2_tests();
}

void run_batch_e_tests(void)
{
    static uint32_t rcc_obj[0xb4 / 4];
    rcc_obj[0x2a8 / 4] = 3;
    rcc_obj[0x2ac / 4] = 0x99;
    reset_counter_and_copy(rcc_obj);
    assert(rcc_obj[0x2a8 / 4] == 0 && rcc_obj[0x2b0 / 4] == 0x99);

    static uint32_t ir738_obj[0x8f0 / 4];
    ir738_obj[1] = 0x11; ir738_obj[2] = 0x22;
    init_record_738(ir738_obj);
    assert(ir738_obj[0x8ec / 4] == (uint32_t)(uintptr_t)ir738_obj + 0x738);
    assert(ir738_obj[0x73c / 4] == 0x11 && ir738_obj[0x740 / 4] == 0x22);
    assert(*(uint16_t *)((uint8_t *)ir738_obj + 0x744) == 0);

    static uint32_t cnc_obj[2];
    static uint32_t cnc_mid[0x94 / 4];
    static uint32_t cnc_next[0x94 / 4];
    static uint32_t cnc_leaf[0xc / 4];
    cnc_obj[1] = (uint32_t)(uintptr_t)cnc_mid;
    cnc_mid[0x10 / 4] = (uint32_t)(uintptr_t)cnc_next;
    cnc_next[0x90 / 4] = (uint32_t)(uintptr_t)cnc_leaf;
    cnc_leaf[8 / 4] = 1;
    assert(check_nested_chain_10_90_8(cnc_obj) == 1);
    cnc_leaf[8 / 4] = 0;
    assert(check_nested_chain_10_90_8(cnc_obj) == 0);
    assert(check_nested_chain_10_90_8_b(cnc_obj) == 0);
    assert(check_nested_chain_10_90_8_c(cnc_obj) == 0);

    static uint8_t sbc4d_obj[0xc50];
    static uint8_t sbc4d_tab[0x152];
    *(uint32_t *)(sbc4d_obj + 0xb08) = (uint32_t)(uintptr_t)sbc4d_tab;
    *(int16_t *)(sbc4d_tab + 0x150) = 1;
    *(uint32_t *)(sbc4d_obj + 0xc48) = 1;
    set_byte_c4d_if_valid(sbc4d_obj);
    assert(sbc4d_obj[0xc4d] == 1);
    *(int16_t *)(sbc4d_tab + 0x150) = 0;
    sbc4d_obj[0xc4d] = 0;
    set_byte_c4d_if_valid(sbc4d_obj);
    assert(sbc4d_obj[0xc4d] == 0);

    static uint32_t uln_node[2];
    static uint32_t uln_prev[2];
    static uint32_t uln_next[2];
    uln_node[0] = (uint32_t)(uintptr_t)uln_prev;
    uln_node[1] = (uint32_t)(uintptr_t)uln_next;
    unlink_list_node(uln_node);
    assert(uln_node[0] == 0 && uln_node[1] == 0);
    assert(uln_prev[1] == (uint32_t)(uintptr_t)uln_next);
    assert(uln_next[0] == (uint32_t)(uintptr_t)uln_prev);

    static uint32_t air_obj[0x38 / 4];
    assert(append_if_room(air_obj, 0xaa) == 1);
    assert(air_obj[0x34 / 4] == 1 && air_obj[1] == 0xaa);
    air_obj[0x34 / 4] = 0xc;
    assert(append_if_room(air_obj, 0xbb) == 0);

    static uint32_t mle_list[8];
    static uint32_t mle_entry[0x60 / 4];
    static uint32_t mle_node[2];
    mle_list[1] = 0;
    mle_list[4] = (uint32_t)(uintptr_t)mle_node;
    mle_list[5] = (uint32_t)(uintptr_t)mle_node;
    mle_list[6] = (uint32_t)(uintptr_t)mle_node;
    mle_entry[0x58 / 4] = (uint32_t)(uintptr_t)mle_node;
    mle_entry[0x5c / 4] = (uint32_t)(uintptr_t)mle_node;
    mle_node[0] = (uint32_t)(uintptr_t)mle_node;
    mle_node[1] = (uint32_t)(uintptr_t)mle_node;
    move_list_entry(mle_list, mle_entry);

    static uint8_t wbe_obj[0x20];
    static uint8_t wbe_buf[0x30];
    *(uint32_t *)(wbe_obj + 0x1c) = (uint32_t)(uintptr_t)wbe_buf;
    write_be32(wbe_obj, 0x12345678, 0);
    assert(wbe_buf[0x14] == 0x12 && wbe_buf[0x15] == 0x34 && wbe_buf[0x16] == 0x56 && wbe_buf[0x17] == 0x78);

    assert(shift_right_64(0x12345678, 0x9abcdef0, 8) == 0x9abcdef012345678ULL >> 8);
    assert(shift_right_64(0, 0x9abcdef0, 0x28) == 0x9abcdef0ULL >> 8);

    static uint8_t ac_arena[0x20];
    allocate_and_clear((uint32_t)(uintptr_t)ac_arena, 0x10);

    static uint32_t irf_rec[0x34 / 4];
    static uint32_t irf_src[1];
    irf_src[0] = 0xdead;
    init_record_fields(irf_rec, irf_src, 0xbeef, 1, 2);
    assert(irf_rec[0] == 0xbeef && irf_rec[3] == 0xdead);
    assert(((uint8_t *)irf_rec)[0x14] == 1 && ((uint8_t *)irf_rec)[0x15] == 2);
    assert(irf_rec[4] == 0 && ((uint8_t *)irf_rec)[0xcc] == 0 && irf_rec[0x32] == 0);

    static uint32_t cle_obj[4];
    cle_obj[3] = (uint32_t)(uintptr_t)cle_obj + 8;
    assert(count_list_entries(cle_obj) == 0);

    static int32_t wi_obj[0x688 / 4];
    wi_obj[0x668 / 4] = 10;
    wi_obj[0x684 / 4] = 5;
    wi_obj[0x674 / 4] = 2;
    assert(wrap_index(wi_obj, 2) == 5);
    wi_obj[0x684 / 4] = 0;
    assert(wrap_index(wi_obj, 2) == 0);
    wi_obj[0x684 / 4] = 9;
    assert(wrap_index(wi_obj, 2) == 9);
    wi_obj[0x684 / 4] = 0;
    wi_obj[0x674 / 4] = 5;
    assert(wrap_index(wi_obj, 2) == 10 - 3);
    wi_obj[0x684 / 4] = 9;
    assert(wrap_index(wi_obj, 2) == 9 - 3);
    wi_obj[0x684 / 4] = 9;
    wi_obj[0x674 / 4] = 0;
    assert(wrap_index(wi_obj, 2) == 9 + 2 - 10);

    static uint8_t sh6c_obj[0x70];
    *(int16_t *)(sh6c_obj + 0x6e) = 1;
    assert(set_halfword_6c_if_valid(sh6c_obj) == 1);
    assert(*(uint16_t *)(sh6c_obj + 0x6c) == 2);
    *(int16_t *)(sh6c_obj + 0x6e) = 0;
    assert(set_halfword_6c_if_valid(sh6c_obj) == 0);
    *(int16_t *)(sh6c_obj + 0x6e) = 2;
    assert(set_halfword_6c_if_valid(sh6c_obj) == 0);

    static uint32_t uce_obj[0x22c / 4];
    static uint8_t uce_tab[0x160];
    uce_obj[0x228 / 4] = (uint32_t)(uintptr_t)uce_tab;
    *(uint32_t *)(uce_tab + 0x154) = (uint32_t)(uintptr_t)uce_tab;
    unlink_circular_entry(uce_obj);

    assert(clamp_toward_target(10, 5, 3) == 7);
    assert(clamp_toward_target(10, 5, 10) == 5);
    assert(clamp_toward_target(5, 10, 3) == 8);
    assert(clamp_toward_target(5, 10, 10) == 10);

    static uint8_t cth_dest[0x30];
    static uint8_t cth_src[0x7c];
    *(uint16_t *)(cth_src + 0x78) = 0x1234;
    *(uint16_t *)(cth_src + 0x7a) = 0x5678;
    copy_two_halfwords(cth_dest, cth_src);
    assert(*(uint16_t *)(cth_dest + 0x2c) == 0x1234 && *(uint16_t *)(cth_dest + 0x2e) == 0x5678);

    assert(classify_value_bits(0) == 0);
    assert(classify_value_bits(1) == 4);
    assert(classify_value_bits(0x800000) == 5);
    assert(classify_value_bits(0x800001) == 5);

    static uint32_t gnte_obj[2];
    static uint8_t gnte_mid[0x94];
    static uint8_t gnte_next[0x94];
    static uint8_t gnte_tab[0x20];
    static uint8_t gnte_data[0x60];
    gnte_obj[1] = (uint32_t)(uintptr_t)gnte_mid;
    *(uint32_t *)(gnte_mid + 0x10) = (uint32_t)(uintptr_t)gnte_next;
    *(uint32_t *)(gnte_next + 0x90) = (uint32_t)(uintptr_t)gnte_tab;
    *(uint32_t *)(gnte_tab + 0x1c) = (uint32_t)(uintptr_t)gnte_data;
    assert(get_indexed_nested_table_entry(gnte_obj, 0) == (uint32_t)(uintptr_t)gnte_data);
    assert(get_indexed_nested_table_entry(gnte_obj, 1) == (uint32_t)(uintptr_t)gnte_data + 0x30);
}

void run_batch_f_tests(void)
{
    static uint8_t cm31d_obj[800];
    assert(check_mode_31d_10((uint32_t)(uintptr_t)cm31d_obj) == 0);
    cm31d_obj[0x31d] = 1;
    assert(check_mode_31d_10((uint32_t)(uintptr_t)cm31d_obj) == 1);
    cm31d_obj[0x31e] = 2;
    cm31d_obj[799] = 10;
    assert(check_mode_31d_10((uint32_t)(uintptr_t)cm31d_obj) == 0);
    cm31d_obj[799] = 5;
    assert(check_mode_31d_10((uint32_t)(uintptr_t)cm31d_obj) == 1);

    static float casv_dest[3];
    static const float casv_src[3] = {1.0f, 2.0f, 3.0f};
    static uint8_t casv_obj[0xd0];
    *(float *)(casv_obj + 0x24) = 4.0f;
    *(float *)(casv_obj + 0xcc) = 0.5f;
    copy_and_scale_vector(casv_dest, casv_src, casv_obj);
    assert(casv_dest[0] == 1.0f && casv_dest[1] == 4.0f && casv_dest[2] == 3.0f);

    static uint32_t rcl_owner[4];
    static uint32_t rcl_prev[2];
    static uint32_t rcl_next[2];
    static uint32_t rcl_node[2];
    rcl_owner[3] = 5;
    rcl_node[0] = (uint32_t)(uintptr_t)rcl_prev;
    rcl_node[1] = (uint32_t)(uintptr_t)rcl_next;
    remove_counted_list_entry(rcl_owner, rcl_node);
    assert(rcl_node[0] == 0 && rcl_node[1] == 0);
    assert(rcl_prev[1] == (uint32_t)(uintptr_t)rcl_next);
    assert(rcl_next[0] == (uint32_t)(uintptr_t)rcl_prev);
    assert(rcl_owner[3] == 4);

    static uint32_t icl_owner[4];
    static uint32_t icl_at[2];
    static uint32_t icl_after[2];
    static uint32_t icl_node[2];
    icl_owner[3] = 5;
    icl_at[1] = (uint32_t)(uintptr_t)icl_after;
    insert_counted_list_entry(icl_owner, icl_at, icl_node);
    assert(icl_node[0] == (uint32_t)(uintptr_t)icl_at);
    assert(icl_node[1] == (uint32_t)(uintptr_t)icl_after);
    assert(icl_at[1] == (uint32_t)(uintptr_t)icl_node);
    assert(icl_after[0] == (uint32_t)(uintptr_t)icl_node);
    assert(icl_owner[3] == 6);

    static uint8_t irbm_rec[8];
    init_record_by_mode(irbm_rec);
    assert(irbm_rec[1] == 1 && irbm_rec[2] == 0);
    static uint8_t irbm_rec2[8];
    irbm_rec2[3] = 1;
    init_record_by_mode(irbm_rec2);
    assert(irbm_rec2[2] == 1 && irbm_rec2[1] == 0);

    static uint8_t tfb_obj[0x20];
    tfb_obj[0xf] = 1;
    assert(test_flag_bit_array(tfb_obj, 0) == 1);
    assert(test_flag_bit_array(tfb_obj, 1) == 0);
    assert(test_flag_bit_array(tfb_obj, 0x3c) == 0);

    static uint8_t gfbc_obj[0x18];
    *(uint32_t *)(gfbc_obj + 0x10) = 0xaa;
    *(uint32_t *)(gfbc_obj + 0x14) = 0xbb;
    assert(get_field_by_code(gfbc_obj, 0x8ce0) == 0xaa);
    assert(get_field_by_code(gfbc_obj, 0x100) == 0xbb);
    assert(get_field_by_code(gfbc_obj, 0x821a) == 0xbb);
    assert(get_field_by_code(gfbc_obj, 0x1234) == 0);

    static char fs_hay[32];
    strcpy(fs_hay, "hello world");
    assert(find_substring(fs_hay, "world") == fs_hay + 6);
    assert(find_substring(fs_hay, "hello") == fs_hay);
    assert(find_substring(fs_hay, "xyz") == NULL);
    assert(find_substring(fs_hay, "") == fs_hay);

    static uint8_t fcf_obj[0x120];
    *(int32_t *)(fcf_obj + 0x10) = 100;
    *(int32_t *)(fcf_obj + 0xc) = 40;
    assert(finalize_counter_and_flag(fcf_obj) == 60);
    assert(fcf_obj[0x11d] == 1);
    assert(finalize_counter_and_flag(fcf_obj) == 60);

    uint32_t *singleton = get_or_init_singleton();
    assert(singleton != NULL);
    assert(get_or_init_singleton() == singleton);

    assert(shift_left_64(0x12345678, 0x9abcdef0, 8) == 0x9abcdef012345678ULL << 8);
    assert(shift_left_64(0x9abcdef0, 0, 0x28) == 0x9abcdef0ULL << 32 << 8);

    static uint32_t clgb_obj[10];
    static uint32_t clgb_node[2];
    clgb_obj[6] = 1;
    clgb_obj[7] = (uint32_t)(uintptr_t)clgb_node;
    clgb_node[0] = (uint32_t)(uintptr_t)&clgb_obj[7];
    clgb_node[1] = (uint32_t)(uintptr_t)&clgb_obj[7];
    assert(clear_list_and_get_base(clgb_obj) == (int32_t)((uint32_t)(uintptr_t)clgb_node - 0x1c));
    clgb_obj[6] = 0;
    assert(clear_list_and_get_base(clgb_obj) == 0);

    static uint32_t ira_obj[6];
    assert(init_range_aligned(ira_obj, 1, 0x40) == 1);
    assert(ira_obj[3] == 0x20 && ira_obj[4] == 0x41 && ira_obj[5] == 0x20);
    assert(init_range_aligned(ira_obj, 0x31, 0xe) == 0);

    static uint32_t iro_rec[8];
    init_record_offsets(iro_rec, 1, 2, 3, 0x100, 4);
    assert(iro_rec[0] == 1 && iro_rec[1] == 2 && iro_rec[2] == 3 && iro_rec[7] == 4);
    assert(iro_rec[3] == 0x100 && iro_rec[4] == 0x108 && iro_rec[5] == 0x110 && iro_rec[6] == 0x118);

    assert(map_type_code(5) == 1);
    assert(map_type_code(6) == 2);
    assert(map_type_code(4) == 3);
    assert(map_type_code(0x6010) == 3);
    assert(map_type_code(0) == 0);

    static uint32_t cfin_obj[8];
    call_flag_if_nested_nonzero(cfin_obj);
    static uint32_t cfin_tab[0x60 / 4];
    cfin_obj[6] = (uint32_t)(uintptr_t)cfin_tab;
    call_flag_if_nested_nonzero(cfin_obj);
    cfin_tab[0x5c / 4] = 1;
    call_flag_if_nested_nonzero(cfin_obj);
    assert(cfin_obj[0x48 / 4] == 1);

    static uint8_t pfc_obj[0x15cc];
    *(uint32_t *)(pfc_obj + 0xc4) = 0x12000000;
    *(uint32_t *)(pfc_obj + 0x15c4) = 0x11;
    propagate_flag_change(pfc_obj);
    assert(*(uint32_t *)(pfc_obj + 0x15c4) == 0x12);
    assert(pfc_obj[0x15c8] == 1 && pfc_obj[0x10f4] == 1);
    propagate_flag_change(pfc_obj);
    assert(pfc_obj[0x15c8] == 0 && pfc_obj[0x10f4] == 0);

    static uint32_t ciw_obj[2];
    static uint32_t ciw_mid[6];
    static uint8_t ciw_tab[0x54 * 2];
    ciw_obj[1] = (uint32_t)(uintptr_t)ciw_mid;
    ciw_mid[0x14 / 4] = (uint32_t)(uintptr_t)ciw_tab;
    *(uint32_t *)(ciw_tab + 0x54 + 0xc) = 5;
    clear_indexed_word_54(ciw_obj, 1);
    assert(*(uint32_t *)(ciw_tab + 0x54 + 0xc) == 0);
    ciw_mid[0x14 / 4] = 0;
    clear_indexed_word_54(ciw_obj, 1);

    static uint8_t rsf_obj[0x118];
    *(uint16_t *)(rsf_obj + 0x98) = 5;
    rsf_obj[0x108] = 1;
    rsf_obj[0x109] = 1;
    assert(reset_state_fields(rsf_obj) == 1);
    assert(*(uint16_t *)(rsf_obj + 0x98) == 0 && rsf_obj[0x108] == 0 && rsf_obj[0x109] == 0);

    static uint8_t shcr_obj[0x20];
    *(uint16_t *)(shcr_obj + 0x1c) = 0x102;
    assert(set_halfword_c_for_range(shcr_obj) == 1);
    assert(*(uint16_t *)(shcr_obj + 0xc) == 0xb);
    *(uint16_t *)(shcr_obj + 0x1c) = 0x100;
    *(uint16_t *)(shcr_obj + 0xc) = 0;
    assert(set_halfword_c_for_range(shcr_obj) == 1);
    assert(*(uint16_t *)(shcr_obj + 0xc) == 0);
}

void run_batch_g_tests(void)
{
    static const uint16_t cwsb_a[4] = {1, 2, 3, 0};
    static const uint16_t cwsb_b[4] = {1, 2, 3, 0};
    static const uint16_t cwsb_c[4] = {1, 2, 5, 0};
    assert(compare_wide_string_bounded(cwsb_a, cwsb_b, 4) == 0);
    assert(compare_wide_string_bounded(cwsb_a, cwsb_c, 4) == -2);
    assert(compare_wide_string_bounded(cwsb_c, cwsb_a, 4) == 2);
    assert(compare_wide_string_bounded(cwsb_a, cwsb_c, 0) == 0);
    assert(compare_wide_string_bounded(cwsb_a, cwsb_c, 2) == 0);

    static uint32_t giwb_obj[1];
    giwb_obj[0] = 0x1000;
    assert(get_indexed_word_base(giwb_obj, 3) == 0x100c);

    static uint32_t s38_obj[1];
    svc_38_store(s38_obj, 0xaa);
    assert(s38_obj[0] == 0xaa);

    static uint32_t s21_obj[1];
    svc_21_store(s21_obj, 0xbb);
    assert(s21_obj[0] == 0xbb);

    static uint32_t cfw_obj[4];
    cfw_obj[0] = 1; cfw_obj[3] = 2;
    clear_four_words_b(cfw_obj);
    assert(cfw_obj[0] == 0 && cfw_obj[1] == 0 && cfw_obj[2] == 0 && cfw_obj[3] == 0);

    static uint32_t cr13_obj[4];
    cr13_obj[0] = 1; cr13_obj[3] = 0xffffffff;
    clear_record_13(cr13_obj);
    assert(cr13_obj[0] == 0 && cr13_obj[1] == 0 && cr13_obj[2] == 0);
    assert(((uint8_t *)cr13_obj)[0xc] == 0);

    static uint8_t ctb_obj[2];
    ctb_obj[0] = 5; ctb_obj[1] = 6;
    clear_two_bytes(ctb_obj);
    assert(ctb_obj[0] == 0 && ctb_obj[1] == 0);

    static uint32_t ipp_obj[0x510 / 4];
    init_pointer_pairs_500(ipp_obj);
    assert(ipp_obj[0x500 / 4] == (uint32_t)(uintptr_t)ipp_obj + 0x184);
    assert(ipp_obj[0x504 / 4] == (uint32_t)(uintptr_t)ipp_obj + 0x14c);
    assert(ipp_obj[0x508 / 4] == 0 && ipp_obj[0x50c / 4] == 0);

    static uint32_t s2d_obj[1];
    svc_2d_store(s2d_obj, 0xcc);
    assert(s2d_obj[0] == 0xcc);

    static uint32_t s25_obj[1];
    assert(svc_25_store(s25_obj, 0xdd, 0, 0, 7) == 7);
    assert(s25_obj[0] == 0xdd);

    assert(return_minus_one() == 0xffffffff);
    assert(return_minus_one_b() == 0xffffffff);

    static uint32_t s29_obj[2];
    svc_29_store_pair(s29_obj, 0x11, 0x22);
    assert(s29_obj[0] == 0x11 && s29_obj[1] == 0x22);

    static uint32_t cwc_obj[4];
    assert(check_word_c_nonzero(cwc_obj) == 0);
    cwc_obj[3] = 9;
    assert(check_word_c_nonzero(cwc_obj) == 1);

    static uint32_t cwfd_obj[0x9c / 4];
    cwfd_obj[0x94 / 4] = 0xfd;
    assert(check_words_not_fd(cwfd_obj) == 0);
    cwfd_obj[0x94 / 4] = 1;
    cwfd_obj[0x98 / 4] = 0xfd;
    assert(check_words_not_fd(cwfd_obj) == 0);
    cwfd_obj[0x98 / 4] = 2;
    assert(check_words_not_fd(cwfd_obj) == 1);

    static uint32_t gpw_obj[3];
    static uint32_t gpw_tab[3];
    gpw_obj[2] = (uint32_t)(uintptr_t)gpw_tab;
    gpw_tab[2] = 0x77;
    assert(get_pointed_word_8(gpw_obj) == 0x77);

    static uint32_t gme_obj[8];
    gme_obj[7] = 0x2000;
    assert(get_masked_entry_5c(gme_obj, 0) == 0x2000);
    assert(get_masked_entry_5c(gme_obj, 2) == 0x2000 + 2 * 0x5c);

    static uint32_t cw14_obj[6];
    cw14_obj[5] = 9;
    clear_word_14_only(cw14_obj);
    assert(cw14_obj[5] == 0);

    static uint32_t gso_obj[4];
    assert(get_self_offset_10d(gso_obj) == (uint32_t)(uintptr_t)gso_obj + 0x10d);

    static uint8_t gih_obj[0xdc];
    *(int16_t *)(gih_obj + 0xd4) = -5;
    *(int16_t *)(gih_obj + 0xd6) = 7;
    assert(get_indexed_halfword_d4(gih_obj, 0) == -5);
    assert(get_indexed_halfword_d4(gih_obj, 1) == 7);

    noop_g();

    static uint32_t cnw_dest[9];
    static const uint32_t cnw_src[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    copy_nine_words(cnw_dest, cnw_src);
    assert(cnw_dest[0] == 1 && cnw_dest[4] == 5 && cnw_dest[8] == 9);

    static float caov_dest[12];
    static const float caov_src[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    static const float caov_off[3] = {0.5f, 1.5f, 2.5f};
    copy_and_offset_vector(caov_dest, caov_off, caov_src);
    assert(caov_dest[0] == 0 && caov_dest[3] == 3.5f && caov_dest[7] == 8.5f && caov_dest[0xb] == 13.5f);

    static uint32_t sb_obj[1];
    svc_b_store(sb_obj, 0xee);
    assert(sb_obj[0] == 0xee);

    static uint32_t cwb04_obj[0xb08 / 4];
    assert(check_word_b04_zero(cwb04_obj) == 1);
    cwb04_obj[0xb04 / 4] = 3;
    assert(check_word_b04_zero(cwb04_obj) == 0);

    static uint32_t gnw_obj[0x8ec / 4];
    static uint32_t gnw_tab[6];
    gnw_obj[0x8e8 / 4] = (uint32_t)(uintptr_t)gnw_tab;
    gnw_tab[5] = 0x55;
    assert(get_nested_word_8e8_14(gnw_obj) == 0x55);

    static uint32_t mnw_obj[2];
    static uint32_t mnw_mid[0xb0c / 4];
    static uint32_t mnw_tab[0x4c / 4];
    mnw_obj[1] = (uint32_t)(uintptr_t)mnw_mid;
    mnw_mid[0xb08 / 4] = (uint32_t)(uintptr_t)mnw_tab;
    mnw_tab[0x48 / 4] = 0xffffffff;
    mask_nested_word_48(mnw_obj);
    assert(mnw_tab[0x48 / 4] == 0xffff7eff);

    static uint8_t ir1b34_obj[0x1b40];
    *(uint32_t *)(ir1b34_obj + 0x1b34) = 9;
    ir1b34_obj[0x1b3a] = 1; ir1b34_obj[0x1b3c] = 1; ir1b34_obj[0x1b3d] = 1;
    init_record_1b34(ir1b34_obj);
    assert(*(uint32_t *)(ir1b34_obj + 0x1b34) == 0);
    assert(ir1b34_obj[0x1b3a] == 0 && ir1b34_obj[0x1b3c] == 0 && ir1b34_obj[0x1b3d] == 0);

    static uint32_t cw8_obj[3];
    assert(check_word_8_nonzero(cw8_obj) == 0);
    cw8_obj[2] = 4;
    assert(check_word_8_nonzero(cw8_obj) == 1);
}

static uint8_t joy_sub[0x100];
static uint32_t joy_obj[6];

static void check_joy(void (*fn)(uint32_t *, uint8_t), uint32_t off, uint16_t mask)
{
    memset(joy_sub, 0, sizeof joy_sub);
    joy_obj[5] = (uint32_t)(uintptr_t)joy_sub;
    fn(joy_obj, 0x5a);
    assert(joy_sub[off] == 0x5a);
    assert((*(uint16_t *)(joy_sub + 0xe8) & mask) == mask);
}

void run_batch_h_tests(void)
{
    check_joy(store_joy_and_flag_db, 0xdb, 0x280);
    check_joy(store_joy_and_flag_da, 0xda, 0x280);
    check_joy(store_joy_and_flag_d9, 0xd9, 0x280);
    check_joy(store_joy_and_flag_d8, 0xd8, 0x280);
    check_joy(store_joy_and_flag_e3, 0xe3, 0x280);
    check_joy(store_joy_and_flag_e2, 0xe2, 0x280);
    check_joy(store_joy_and_flag_e1, 0xe1, 0x280);
    check_joy(store_joy_and_flag_e0, 0xe0, 0x280);
    check_joy(store_joy_and_flag_df, 0xdf, 0x280);
    check_joy(store_joy_and_flag_de, 0xde, 0x280);
    check_joy(store_joy_and_flag_dd, 0xdd, 0x280);
    check_joy(store_joy_and_flag_dc, 0xdc, 0x280);
    check_joy(store_joy_and_flag_d3, 0xd3, 0x80);
    check_joy(store_joy_and_flag_d2, 0xd2, 0x80);
    check_joy(store_joy_and_flag_d1, 0xd1, 0x80);
    check_joy(store_joy_and_flag_d0, 0xd0, 0x80);
    check_joy(store_joy_and_flag_d6, 0xd6, 0x80);
    check_joy(store_joy_and_flag_d5, 0xd5, 0x80);
    check_joy(store_joy_and_flag_d4, 0xd4, 0x80);

    assert(map_code_to_value(1) == 0x12);
    assert(map_code_to_value(2) == 0x2b);
    assert(map_code_to_value(0) == 0xff);
    assert(map_code_to_value(99) == 0xff);

    static uint32_t mcc_obj[0x34 / 4];
    static uint16_t mcc_a[0xce / 2];
    static uint16_t mcc_b[0xce / 2];
    mcc_obj[0x2c / 4] = (uint32_t)(uintptr_t)mcc_a;
    mcc_obj[0x30 / 4] = (uint32_t)(uintptr_t)mcc_b;
    mcc_a[0xcc / 2] = 0xffff;
    mcc_b[0xcc / 2] = 0xffff;
    mask_cc_fields(mcc_obj);
    assert(mcc_a[0xcc / 2] == 0xfffd && mcc_b[0xcc / 2] == 0xfffd);
    or_cc_fields(mcc_obj);
    assert((mcc_a[0xcc / 2] & 2) == 2 && (mcc_b[0xcc / 2] & 2) == 2);

    static uint32_t cv200_obj[0x234 / 4];
    static const uint32_t cv200_src[3] = {0x11, 0x22, 0x33};
    copy_vector_200(cv200_obj, cv200_src, 0x44);
    assert(cv200_obj[0x200 / 4] == 0x11 && cv200_obj[0x204 / 4] == 0x22 && cv200_obj[0x208 / 4] == 0x33);
    assert(cv200_obj[0x230 / 4] == 0x44);

    static uint32_t cwc38_obj[0x3c / 4];
    cwc38_obj[3] = 5;
    cwc38_obj[0x38 / 4] = 6;
    clear_word_c_and_38(cwc38_obj);
    assert(cwc38_obj[3] == 0 && cwc38_obj[0x38 / 4] == 0);

    static uint8_t ire14_obj[0x24];
    init_record_e_14(ire14_obj);
    assert(*(uint32_t *)(ire14_obj + 4) == 0xe && ire14_obj[0x14] == 6);
    assert(*(uint32_t *)(ire14_obj + 0x1c) == 0 && *(uint32_t *)(ire14_obj + 0x20) == 0);

    static uint8_t ir22_obj[0x28];
    init_record_22_24(ir22_obj);
    assert(*(uint32_t *)(ir22_obj + 4) == 0x22 && ir22_obj[0x14] == 6);
    assert(*(uint32_t *)(ir22_obj + 0x1c) == 0 && *(uint32_t *)(ir22_obj + 0x20) == 0 && *(uint32_t *)(ir22_obj + 0x24) == 0);

    static uint8_t stw_obj[0x118];
    static const uint32_t stw_src[2] = {0xaa, 0xbb};
    stw_obj[0x116] = 1;
    store_two_words_108(stw_obj, stw_src);
    assert(*(uint32_t *)(stw_obj + 0x108) == 0xaa && *(uint32_t *)(stw_obj + 0x10c) == 0xbb);
    assert(stw_obj[0x116] == 0);

    static uint32_t iw18_obj[7];
    iw18_obj[6] = 5;
    increment_word_18(iw18_obj);
    assert(iw18_obj[6] == 6);
}

void run_batch_i_tests(void)
{
    static uint32_t sba_obj[0xa30 / 4];
    set_byte_a28(sba_obj, 1);
    assert(((uint8_t *)sba_obj)[0xa28] == 1);
    assert(sba_obj[0x8c / 4] == (uint32_t)(uintptr_t)sba_obj + 0x90);
    sba_obj[0x8c / 4] = 0;
    set_byte_a28(sba_obj, 2);
    assert(((uint8_t *)sba_obj)[0xa28] == 2 && sba_obj[0x8c / 4] == 0);

    static uint32_t gib45_obj[3];
    static uint8_t gib45_sub[8];
    gib45_obj[2] = (uint32_t)(uintptr_t)gib45_sub;
    gib45_sub[4] = 5;
    assert(get_if_byte_4_is_5(gib45_obj) == (uint32_t)(uintptr_t)gib45_sub);
    gib45_sub[4] = 3;
    assert(get_if_byte_4_is_5(gib45_obj) == 0);

    static uint32_t swa18_obj[0xa1c / 4];
    swa18_obj[0xa18 / 4] = 9;
    set_word_a18(swa18_obj);
    assert(swa18_obj[0xa18 / 4] == 0);

    static uint32_t sr0_obj[2];
    sr0_obj[1] = 5;
    assert(svc_23_release_0(sr0_obj) == (uint32_t)(uintptr_t)sr0_obj);
    assert(sr0_obj[1] == 0);
    assert(svc_23_release_0(sr0_obj) == (uint32_t)(uintptr_t)sr0_obj);

    static uint32_t sr1_obj[1];
    sr1_obj[0] = 7;
    assert(svc_23_release_1(sr1_obj) == (uint32_t)(uintptr_t)sr1_obj);
    assert(sr1_obj[0] == 0);
    assert(svc_23_release_1(sr1_obj) == (uint32_t)(uintptr_t)sr1_obj);

    static uint32_t sr2_obj[1];
    sr2_obj[0] = 8;
    assert(svc_23_release_2(sr2_obj) == (uint32_t)(uintptr_t)sr2_obj);
    assert(sr2_obj[0] == 0);

    static uint32_t sr3_obj[1];
    sr3_obj[0] = 9;
    assert(svc_23_release_3(sr3_obj) == (uint32_t)(uintptr_t)sr3_obj);
    assert(sr3_obj[0] == 0);

    assert(normalize_index(0) == 0);
    assert(normalize_index(0x17) == 0x17);
    assert(normalize_index(0x18) == 0);
    assert(normalize_index(0x1f) == 7);
    assert(normalize_index(0x20) == 0);
    assert(normalize_index(0x25) == 5);

    static uint8_t mb1ea_obj[0x1ec];
    mb1ea_obj[0x1ea] = 0xff;
    mask_byte_1ea(mb1ea_obj, 0x0f);
    assert(mb1ea_obj[0x1e9] == 0x0f && mb1ea_obj[0x1ea] == 0x0f);

    static uint32_t pw1c_obj[8];
    static uint32_t pw1c_buf[4];
    pw1c_obj[7] = (uint32_t)(uintptr_t)pw1c_buf;
    push_word_1c(pw1c_obj, 0xaa);
    assert(pw1c_buf[0] == 0xaa);
    assert(pw1c_obj[7] == (uint32_t)(uintptr_t)pw1c_buf + 4);
    assert(pw1c_obj[5] == 1);
    push_word_1c(pw1c_obj, 0xbb);
    assert(pw1c_buf[1] == 0xbb && pw1c_obj[5] == 2);
    pw1c_obj[7] = 0;
    push_word_1c(pw1c_obj, 0xcc);
    assert(pw1c_obj[5] == 3);

    static uint8_t sb1b5_obj[0x1d0];
    sb1b5_obj[0x1b5] = 1;
    set_byte_1b5_if_different(sb1b5_obj, 1);
    assert(sb1b5_obj[0x1cf] == 0);
    set_byte_1b5_if_different(sb1b5_obj, 2);
    assert(sb1b5_obj[0x1b5] == 2 && (sb1b5_obj[0x1cf] & 2) == 2);

    static uint8_t gw114_obj[0x118];
    *(float *)(gw114_obj + 0x114) = 2.5f;
    assert(get_word_114_as_float(gw114_obj) == 2.5f);

    static uint8_t gba8_obj[0x14];
    gba8_obj[8] = 0x7f;
    gba8_obj[8 + 0xb] = 0x80;
    assert(get_byte_at_8_bounded(gba8_obj, 0) == 0x7f);
    assert(get_byte_at_8_bounded(gba8_obj, 0xb) == -128);
    assert(get_byte_at_8_bounded(gba8_obj, 0xc) == 0);
}

void run_batch_j_tests(void)
{
    static uint8_t cb1508_obj[0x150c];
    cb1508_obj[0x1508] = 2;
    assert(check_byte_1508_is_2(cb1508_obj) == 1);
    assert(check_byte_1508_is_2_b(cb1508_obj) == 1);
    cb1508_obj[0x1508] = 1;
    assert(check_byte_1508_is_2(cb1508_obj) == 0);
    assert(check_byte_1508_is_2_b(cb1508_obj) == 0);

    static uint8_t cb2367_obj[0x2368];
    cb2367_obj[0x2367] = 9;
    clear_byte_2367(cb2367_obj);
    assert(cb2367_obj[0x2367] == 0);

    static uint8_t cb45b0_obj[0x45b4];
    cb45b0_obj[0x45b0] = 5;
    assert(check_byte_45b0_is_5(cb45b0_obj) == 1);
    cb45b0_obj[0x45b0] = 4;
    assert(check_byte_45b0_is_5(cb45b0_obj) == 0);

    assert(identity_word_b(0) == 0);
    assert(identity_word_b(0xdeadbeef) == 0xdeadbeef);

    static uint32_t rc30_obj[0x3c / 4];
    rc30_obj[0x34 / 4] = 7;
    rc30_obj[0x30 / 4] = 3;
    rc30_obj[1] = 5;
    rc30_obj[2] = 0x99;
    reset_counters_30(rc30_obj);
    assert(rc30_obj[0x38 / 4] == 7 && rc30_obj[0x30 / 4] == 0);
    assert(rc30_obj[1] == 0 && rc30_obj[3] == 0x99);

    static uint32_t pbm_obj[0x5e4 / 4];
    static uint32_t pbm_buf_a[4];
    static uint32_t pbm_buf_b[4];
    ((uint8_t *)pbm_obj)[0x5e0] = 1;
    pbm_obj[0x38 / 4] = (uint32_t)(uintptr_t)pbm_buf_a;
    push_by_mode(pbm_obj);
    assert(pbm_buf_a[0] == (uint32_t)(uintptr_t)pbm_obj + 0x60);
    assert(pbm_obj[0x30 / 4] == 1);
    assert(pbm_obj[0x38 / 4] == (uint32_t)(uintptr_t)pbm_buf_a + 4);
    ((uint8_t *)pbm_obj)[0x5e0] = 0;
    pbm_obj[3] = (uint32_t)(uintptr_t)pbm_buf_b;
    push_by_mode(pbm_obj);
    assert(pbm_buf_b[0] == (uint32_t)(uintptr_t)pbm_obj + 0x60);
    assert(pbm_obj[1] == 1);
}

void run_batch_k_tests(void)
{
    static uint32_t cvb_obj[0x2d8 / 4];
    static const uint32_t cvb_src[3] = {0x11, 0x22, 0x33};
    copy_vector_200_b(cvb_obj, cvb_src, 0x44, 0x55);
    assert(cvb_obj[0x200 / 4] == 0x11 && cvb_obj[0x204 / 4] == 0x22 && cvb_obj[0x208 / 4] == 0x33);
    assert(cvb_obj[0x230 / 4] == 0x44 && cvb_obj[0x2d4 / 4] == 0x55);

    assert(identity_word_c(0) == 0);
    assert(identity_word_c(0xcafebabe) == 0xcafebabe);

    static uint32_t pfn_head;
    static uint32_t pfn_node_a[2];
    static uint32_t pfn_node_b[2];
    pfn_head = 0;
    push_front_node(&pfn_head, pfn_node_a);
    assert(pfn_head == (uint32_t)(uintptr_t)pfn_node_a);
    assert(pfn_node_a[0] == 0 && pfn_node_a[1] == (uint32_t)(uintptr_t)&pfn_head);
    push_front_node(&pfn_head, pfn_node_b);
    assert(pfn_head == (uint32_t)(uintptr_t)pfn_node_b);
    assert(pfn_node_b[0] == (uint32_t)(uintptr_t)pfn_node_a);
    assert(pfn_node_a[1] == (uint32_t)(uintptr_t)pfn_node_b);
}

void run_batch_l_tests(void)
{
    static uint8_t cb1aa2_obj[0x1aa4];
    cb1aa2_obj[0x1aa2] = 1;
    assert(check_byte_1aa2_under_2(cb1aa2_obj) == 1);
    cb1aa2_obj[0x1aa2] = 2;
    assert(check_byte_1aa2_under_2(cb1aa2_obj) == 0);

    static uint8_t iw258_obj[0x25c];
    *(int32_t *)(iw258_obj + 600) = 5;
    increment_word_258(iw258_obj);
    assert(*(int32_t *)(iw258_obj + 600) == 6);
    *(int32_t *)(iw258_obj + 600) = 0x7fffffff;
    increment_word_258(iw258_obj);
    assert(*(int32_t *)(iw258_obj + 600) == 0x7fffffff);

    static uint8_t ir010_obj[0x14];
    memset(ir010_obj, 0xff, sizeof ir010_obj);
    init_record_0_10(ir010_obj);
    assert(ir010_obj[0] == 0 && ir010_obj[1] == 0 && ir010_obj[2] == 0);
    assert(*(uint32_t *)(ir010_obj + 4) == 0 && *(uint32_t *)(ir010_obj + 0x10) == 0);

    static uint8_t gb11d1_obj[0x11d4];
    gb11d1_obj[0x11d1] = 0x80;
    assert(get_byte_11d1(gb11d1_obj) == -128);

    static uint32_t ad4_obj[3];
    static uint32_t ad4_tab[0xd8 / 4];
    ad4_obj[2] = (uint32_t)(uintptr_t)ad4_tab;
    ad4_tab[0xd4 / 4] = 0x1000;
    assert(add_d4_entry(ad4_obj, 0) == 0x1090);
    assert(add_d4_entry(ad4_obj, 1) == 0x1090 + 0x30);

    static uint32_t awc_obj[5];
    static uint8_t awc_tab[0x10];
    awc_obj[3] = (uint32_t)(uintptr_t)awc_tab;
    awc_obj[4] = 0x2000;
    *(uint16_t *)(awc_tab + 2) = 7;
    assert(add_word_c_indexed(awc_obj, 1) == 0x2007);

    static uint32_t aw4h_obj[4];
    static uint8_t aw4h_tab[0x14];
    aw4h_obj[1] = 0x3000;
    aw4h_obj[3] = (uint32_t)(uintptr_t)aw4h_tab;
    *(uint16_t *)(aw4h_tab + 8 + 4) = 5;
    assert(add_word_4_by_halfword(aw4h_obj, 1) == 0x3000 + 20);

    static uint32_t gch_obj[5];
    static uint8_t gch_idx[0x10];
    static uint8_t gch_base[0x20];
    gch_obj[4] = (uint32_t)(uintptr_t)gch_idx;
    gch_obj[1] = (uint32_t)(uintptr_t)gch_base;
    *(uint16_t *)(gch_idx + 4 + 2) = 3;
    *(uint16_t *)(gch_base + 3 * 4 + 1 * 2) = 0xabcd;
    assert(get_chained_halfword_2(gch_obj, 1, 1) == 0xabcd);

    static uint32_t aw8_obj[3];
    aw8_obj[2] = 0x4000;
    assert(add_word_8_indexed(aw8_obj, 2) == 0x4010);

    static uint32_t gpw0_obj[2];
    static uint32_t gpw0_tab[3];
    assert(get_pointed_word_0(gpw0_obj) == 0);
    gpw0_obj[1] = (uint32_t)(uintptr_t)gpw0_tab;
    gpw0_tab[2] = 0x66;
    assert(get_pointed_word_0(gpw0_obj) == 0x66);

    static uint32_t gpb5_obj[2];
    static uint8_t gpb5_tab[8];
    assert(get_pointed_byte_5(gpb5_obj) == 0);
    gpb5_obj[1] = (uint32_t)(uintptr_t)gpb5_tab;
    gpb5_tab[5] = 0x42;
    assert(get_pointed_byte_5(gpb5_obj) == 0x42);

    static uint32_t gph6_obj[2];
    static uint8_t gph6_tab[8];
    assert(get_pointed_halfword_6(gph6_obj) == 0);
    gph6_obj[1] = (uint32_t)(uintptr_t)gph6_tab;
    *(int16_t *)(gph6_tab + 6) = -7;
    assert(get_pointed_halfword_6(gph6_obj) == -7);

    static uint8_t cp1819_obj[0x1c];
    cp1819_obj[0x18] = 0xfd;
    cp1819_obj[0x19] = 3;
    assert(check_pair_18_19(cp1819_obj) == 0);
    cp1819_obj[0x18] = 1;
    cp1819_obj[0x19] = 3;
    assert(check_pair_18_19(cp1819_obj) == 1);
    cp1819_obj[0x19] = 2;
    assert(check_pair_18_19(cp1819_obj) == 0);

    assert(map_to_012(0) == 0);
    assert(map_to_012(1) == 1);
    assert(map_to_012(5) == 2);

    static uint8_t cb254_obj[0x258];
    cb254_obj[0x254] = 1;
    assert(check_byte_254_is_1(cb254_obj) == 1);
    cb254_obj[0x254] = 2;
    assert(check_byte_254_is_1(cb254_obj) == 0);

    static uint32_t cnw44_obj[0x1fc / 4];
    static uint32_t cnw44_tab[0x48 / 4];
    cnw44_obj[0x1f8 / 4] = (uint32_t)(uintptr_t)cnw44_tab;
    assert(check_nested_word_44(cnw44_obj) == 0);
    cnw44_tab[0x44 / 4] = 1;
    assert(check_nested_word_44(cnw44_obj) == 1);

    assert(add_offset_1c(0x1000, 4) == 0x1020);
    assert(return_ten() == 10);

    static uint32_t gb6f_obj[9];
    static uint8_t gb6f_sub[0x70];
    assert(get_byte_6f_flag(gb6f_obj) == 0);
    gb6f_obj[8] = (uint32_t)(uintptr_t)gb6f_sub;
    assert(get_byte_6f_flag(gb6f_obj) == 0);
    gb6f_sub[0x6f] = 5;
    assert(get_byte_6f_flag(gb6f_obj) == 1);

    static uint32_t gwe4_obj[0xe8 / 4];
    gwe4_obj[0xe4 / 4] = 0xffff0000;
    assert(get_word_e4_low(gwe4_obj) == 0);
    gwe4_obj[0xe4 / 4] = 0x12345678;
    assert(get_word_e4_low(gwe4_obj) == 0x5678);

    noop_h();

    static uint32_t swm13_out;
    static uint8_t swm13_obj[0x64];
    swm13_obj[0x58] = 1;
    *(uint32_t *)(swm13_obj + 0x60) = 0x999;
    store_word_60_if_mode_1_3(&swm13_out, swm13_obj);
    assert(swm13_out == 0x999);
    swm13_obj[0x58] = 3;
    store_word_60_if_mode_1_3(&swm13_out, swm13_obj);
    assert(swm13_out == 0x999);
    swm13_obj[0x58] = 2;
    store_word_60_if_mode_1_3(&swm13_out, swm13_obj);
    assert(swm13_out == 0);

    static uint8_t cm20_obj[0x58];
    cm20_obj[0x20] = 5;
    cm20_obj[0x55] = 1;
    assert(check_mode_20_byte_55_1(cm20_obj) == 1);
    cm20_obj[0x55] = 2;
    assert(check_mode_20_byte_55_1(cm20_obj) == 0);
    cm20_obj[0x20] = 4;
    cm20_obj[0x55] = 1;
    assert(check_mode_20_byte_55_1(cm20_obj) == 0);

    static uint32_t aw4_obj[2];
    aw4_obj[1] = 0x10;
    assert(add_word_4(aw4_obj) == (uint32_t)(uintptr_t)aw4_obj + 0x10);
    assert(add_word_4_b(aw4_obj) == (uint32_t)(uintptr_t)aw4_obj + 0x10);

    static uint32_t gpw0b_obj[3];
    static uint32_t gpw0b_ptr[2];
    static uint32_t gpw0b_val[2];
    assert(get_pointed_word_0_b(gpw0b_obj) == 0);
    gpw0b_obj[2] = (uint32_t)(uintptr_t)gpw0b_ptr;
    gpw0b_ptr[0] = (uint32_t)(uintptr_t)gpw0b_val;
    gpw0b_val[0] = 0x77;
    assert(get_pointed_word_0_b(gpw0b_obj) == 0x77);

    static uint16_t gh300_obj[4];
    assert(get_if_halfword_4_is_300(gh300_obj) == 0);
    gh300_obj[0] = 0x300;
    *(uint32_t *)(gh300_obj + 2) = 0x20;
    assert(get_if_halfword_4_is_300(gh300_obj) == (uint32_t)(uintptr_t)gh300_obj + 0x20);

    static uint32_t aw34_obj[0x38 / 4];
    aw34_obj[0x34 / 4] = 0x18;
    assert(add_word_34(aw34_obj) == (uint32_t)(uintptr_t)aw34_obj + 0x18);

    static uint32_t gh101_obj[3];
    assert(get_if_halfword_4_is_101(gh101_obj) == 0);
    assert(get_if_halfword_4_is_101_b(gh101_obj) == 0);
    *(int16_t *)((uint8_t *)gh101_obj + 4) = 0x101;
    gh101_obj[2] = 0x30;
    assert(get_if_halfword_4_is_101(gh101_obj) == (uint32_t)(uintptr_t)gh101_obj + 0x30);
    assert(get_if_halfword_4_is_101_b(gh101_obj) == (uint32_t)(uintptr_t)gh101_obj + 0x30);

    static uint32_t gp181c_obj[8];
    assert(get_if_pair_18_1c(gp181c_obj) == 0);
    *(int16_t *)((uint8_t *)gp181c_obj + 0x18) = 0x2210;
    gp181c_obj[7] = 0x40;
    assert(get_if_pair_18_1c(gp181c_obj) == (uint32_t)(uintptr_t)gp181c_obj + 0x40);
    gp181c_obj[7] = 0xffffffff;
    assert(get_if_pair_18_1c(gp181c_obj) == 0);

    static uint16_t gh220c_obj[4];
    assert(get_if_halfword_0_is_220c(gh220c_obj) == 0);
    gh220c_obj[0] = 0x220c;
    *(uint32_t *)(gh220c_obj + 2) = 0x50;
    assert(get_if_halfword_0_is_220c(gh220c_obj) == (uint32_t)(uintptr_t)gh220c_obj + 0x50);

    static uint16_t mh220c_obj[2];
    mh220c_obj[0] = 0;
    assert(map_halfword_220c(mh220c_obj) == 2);
    mh220c_obj[0] = 0x220c;
    assert(map_halfword_220c(mh220c_obj) == 0);
    mh220c_obj[0] = 0x220d;
    assert(map_halfword_220c(mh220c_obj) == 1);
    mh220c_obj[0] = 0x220e;
    assert(map_halfword_220c(mh220c_obj) == 2);

    static uint8_t gpw0c_obj[16];
    static uint32_t gpw0c_tab[2];
    assert(get_pointed_word_0_c(gpw0c_obj) == 0);
    gpw0c_obj[0xc] = 1;
    *(uint32_t *)(gpw0c_obj + 4) = (uint32_t)(uintptr_t)gpw0c_tab;
    gpw0c_tab[0] = 0x88;
    assert(get_pointed_word_0_c(gpw0c_obj) == 0x88);
}

void run_batch_m_tests(void)
{
    static uint32_t gn68_obj[1];
    static uint32_t gn68_mid[0x6c / 4];
    static uint32_t gn68_tab[3];
    assert(get_nested_68_8(gn68_obj) == 0);
    gn68_obj[0] = (uint32_t)(uintptr_t)gn68_mid;
    gn68_mid[0x68 / 4] = (uint32_t)(uintptr_t)gn68_tab;
    gn68_tab[2] = 0x99;
    assert(get_nested_68_8(gn68_obj) == 0x99);

    static uint32_t cpb4_obj[1];
    static uint8_t cpb4_sub[8];
    assert(check_pointed_byte_4_zero(cpb4_obj) == 0);
    cpb4_obj[0] = (uint32_t)(uintptr_t)cpb4_sub;
    assert(check_pointed_byte_4_zero(cpb4_obj) == 1);
    cpb4_sub[4] = 1;
    assert(check_pointed_byte_4_zero(cpb4_obj) == 0);

    static uint32_t gb50_obj[0x54 / 4];
    assert(get_byte_50_or_1(gb50_obj) == 1);
    gb50_obj[0] = 1;
    gb50_obj[0x14] = 0x42;
    assert(get_byte_50_or_1(gb50_obj) == 0x42);

    static uint8_t cb51_obj[0x88];
    assert(check_byte_51_word_84(cb51_obj) == 0);
    *(uint32_t *)(cb51_obj + 0x84) = 1;
    assert(check_byte_51_word_84(cb51_obj) == 1);
    cb51_obj[0x51] = 1;
    assert(check_byte_51_word_84(cb51_obj) == 0);

    static uint32_t gw21f_obj[3];
    gw21f_obj[1] = 0x21f;
    assert(get_if_word_4_is_21f(gw21f_obj) == (uint32_t)(uintptr_t)gw21f_obj + 8);
    gw21f_obj[1] = 0;
    assert(get_if_word_4_is_21f(gw21f_obj) == 0);

    static uint32_t awc_obj[4];
    awc_obj[3] = 0x20;
    assert(add_word_c(awc_obj) == (uint32_t)(uintptr_t)awc_obj + 0x20);

    static uint32_t aw4o_obj[2];
    aw4o_obj[1] = 0x1000;
    assert(add_word_4_offset(aw4o_obj, 0x30) == 0x1030);

    static uint32_t gie_obj[9];
    gie_obj[5] = 1;
    gie_obj[6] = 0;
    gie_obj[7] = 0x20;
    assert(get_indexed_entry_14(gie_obj, 0) == (uint32_t)(uintptr_t)gie_obj + 0x14 + 0x20);
    assert(get_indexed_entry_14(gie_obj, 1) == 0);

    static uint32_t an8_obj[2];
    static uint32_t an8_tab[3];
    an8_obj[0] = (uint32_t)(uintptr_t)an8_tab;
    an8_obj[1] = 0x5000;
    an8_tab[2] = 2;
    assert(add_nested_8_16c(an8_obj) == 0x5000 + 2 * 0x16c);

    static uint32_t sdo10_out[2];
    static uint32_t sdo10_obj[1];
    static uint8_t sdo10_tab[0x20];
    sdo10_obj[0] = (uint32_t)(uintptr_t)sdo10_tab;
    *(uint32_t *)(sdo10_tab + 0x10) = 0x40;
    store_deref_offset_10(sdo10_out, sdo10_obj, 0);
    assert(sdo10_out[0] == (uint32_t)(uintptr_t)sdo10_tab + 0x40);
    assert(sdo10_out[1] == 0);

    static uint32_t a818_obj[3];
    a818_obj[2] = 0x10000;
    assert(add_8_180_10(a818_obj, 1, 2) == 0x10000 + 0x180 + 0x20 + 0x54);

    static uint32_t s818_out;
    static uint32_t s818_obj[3];
    s818_obj[2] = 0x20000;
    store_8_180_18_130(&s818_out, s818_obj, 1, 2);
    assert(s818_out == 0x20000 + 0x180 + 0x30 + 0x130);

    static uint32_t gn817_obj[3];
    static uint8_t gn817_tab[0x180 + 0x180];
    static uint32_t gn817_sub[4];
    gn817_obj[2] = (uint32_t)(uintptr_t)gn817_tab;
    *(uint32_t *)(gn817_tab + 0x180 + 0x17c) = (uint32_t)(uintptr_t)gn817_sub;
    gn817_sub[1] = 0x777;
    assert(get_nested_8_180_17c(gn817_obj, 1, 1) == 0x777);

    static uint8_t c4c_dest[0x4c];
    static uint32_t c4c_obj[2];
    static uint8_t c4c_src[0x4c];
    memset(c4c_src, 0x5a, sizeof c4c_src);
    c4c_obj[1] = (uint32_t)(uintptr_t)c4c_src;
    assert(copy_4c_from_pointed(c4c_dest, c4c_obj) == 1);
    assert(c4c_dest[0] == 0x5a && c4c_dest[0x4b] == 0x5a);

    static uint32_t cpw68_obj[1];
    static uint32_t cpw68_tab[0x6c / 4];
    assert(check_pointed_word_68(cpw68_obj) == 0);
    cpw68_obj[0] = (uint32_t)(uintptr_t)cpw68_tab;
    cpw68_tab[0x68 / 4] = 0x123;
    assert(check_pointed_word_68(cpw68_obj) == 0x123);

    static uint32_t gpb4_obj[1];
    static uint8_t gpb4_sub[8];
    assert(get_pointed_byte_4_zero(gpb4_obj) == 1);
    gpb4_obj[0] = (uint32_t)(uintptr_t)gpb4_sub;
    assert(get_pointed_byte_4_zero(gpb4_obj) == 1);
    gpb4_sub[4] = 1;
    assert(get_pointed_byte_4_zero(gpb4_obj) == 0);
}

void run_batch_n_tests(void)
{
    static uint32_t cbe_obj[3];
    static uint8_t cbe_buf[8];
    cbe_obj[2] = (uint32_t)(uintptr_t)cbe_buf;
    cbe_obj[1] = 4;
    cbe_buf[3] = 9;
    clear_byte_end(cbe_obj);
    assert(cbe_buf[3] == 0);

    static uint8_t gb15bc_obj[0x15c0];
    gb15bc_obj[0x15bc] = 0x80;
    assert(get_byte_15bc(gb15bc_obj) == -128);

    static uint8_t gb15b8_obj[0x15c0];
    *(int32_t *)(gb15b8_obj + 0x15b8) = 2;
    gb15b8_obj[0x1597 + 2 - 1] = 0x7f;
    assert(get_byte_15b8_indexed(gb15b8_obj, 1) == 0x7f);

    static uint8_t c31328_obj[0x32c];
    c31328_obj[0x31e] = 1;
    assert(check_31e_328(c31328_obj) == 1);
    c31328_obj[0x328] = 6;
    assert(check_31e_328(c31328_obj) == 0);
    c31328_obj[0x328] = 5;
    c31328_obj[0x31e] = 2;
    assert(check_31e_328(c31328_obj) == 0);

    static uint8_t c315314_obj[0x318];
    assert(check_315_314(c315314_obj) == 0);
    c315314_obj[0x314] = 1;
    assert(check_315_314(c315314_obj) == 1);
    c315314_obj[0x315] = 1;
    assert(check_315_314(c315314_obj) == 0);

    static uint32_t mf18_obj[7];
    static uint32_t mf18_tab[2];
    mf18_obj[6] = (uint32_t)(uintptr_t)mf18_tab;
    mf18_tab[1] = 0;
    assert(map_flags_18(mf18_obj) == 0);
    mf18_tab[1] = 1;
    assert(map_flags_18(mf18_obj) == 2);
    mf18_tab[1] = 2;
    assert(map_flags_18(mf18_obj) == 1);
    mf18_tab[1] = 3;
    assert(map_flags_18(mf18_obj) == 2);

    static uint8_t gb6_obj[8];
    gb6_obj[6] = 0x7f;
    assert(get_byte_6_low(gb6_obj) == 0x7f);
    assert(get_byte_6_high(gb6_obj) == 0);
    gb6_obj[6] = 0xff;
    assert(get_byte_6_low(gb6_obj) == 0x7f);
    assert(get_byte_6_high(gb6_obj) == 0x80);

    static uint8_t gb49f0_obj[0x4a00];
    gb49f0_obj[0x49f0 + 3] = 0x55;
    assert(get_byte_49f0(gb49f0_obj, 3) == 0x55);

    static uint8_t gw18_obj[0x1c];
    assert(get_word_18_if_byte_1(gw18_obj) == 0);
    gw18_obj[1] = 1;
    *(uint32_t *)(gw18_obj + 0x18) = 0x999;
    assert(get_word_18_if_byte_1(gw18_obj) == 0x999);

    static uint8_t gb118_obj[0x11c];
    gb118_obj[0x118] = 0xfe;
    assert(get_byte_118(gb118_obj) == -2);

    static uint32_t gw4_obj[2];
    gw4_obj[1] = 0x77;
    assert(get_word_4(gw4_obj) == 0x77);

    static uint32_t gh2_obj[2];
    static uint8_t gh2_tab[4];
    gh2_obj[1] = (uint32_t)(uintptr_t)gh2_tab;
    *(uint16_t *)(gh2_tab + 2) = 0xabcd;
    assert(get_halfword_2_chained(gh2_obj) == 0xabcd);

    static uint32_t gh28_obj[2];
    static uint8_t gh28_tab[0x2c];
    assert(get_halfword_28_chained(gh28_obj) == 0);
    gh28_obj[1] = (uint32_t)(uintptr_t)gh28_tab;
    *(uint16_t *)(gh28_tab + 0x28) = 0x1234;
    assert(get_halfword_28_chained(gh28_obj) == 0x1234);

    static uint32_t gw8_obj[2];
    static uint32_t gw8_tab[3];
    gw8_obj[1] = (uint32_t)(uintptr_t)gw8_tab;
    gw8_tab[2] = 0;
    assert(get_word_8_chained(gw8_obj) == 0);
    gw8_tab[2] = 0x10;
    assert(get_word_8_chained(gw8_obj) == (uint32_t)(uintptr_t)gw8_tab + 0x10);

    static uint32_t gwc_obj[2];
    static uint32_t gwc_tab[4];
    gwc_obj[1] = (uint32_t)(uintptr_t)gwc_tab;
    gwc_tab[3] = 0;
    assert(get_word_c_chained(gwc_obj) == 0);
    gwc_tab[3] = 0x20;
    assert(get_word_c_chained(gwc_obj) == (uint32_t)(uintptr_t)gwc_tab + 0x20);

    static uint32_t gw14_obj[2];
    static uint32_t gw14_tab[6];
    gw14_obj[1] = (uint32_t)(uintptr_t)gw14_tab;
    gw14_tab[5] = 0;
    assert(get_word_14_chained(gw14_obj) == 0);
    gw14_tab[5] = 0x30;
    assert(get_word_14_chained(gw14_obj) == (uint32_t)(uintptr_t)gw14_tab + 0x30);

    static uint32_t a38110_obj[0x3c / 4];
    a38110_obj[0x38 / 4] = 0x10000;
    assert(add_38_110(a38110_obj, 1) == 0x10000 + 0x110 + 0x90);

    static uint8_t gb1b3c_obj[0x1b40];
    gb1b3c_obj[0x1b3c] = 0x81;
    assert(get_byte_1b3c(gb1b3c_obj) == -127);

    static uint32_t ctw_obj[2];
    ctw_obj[0] = 1; ctw_obj[1] = 2;
    clear_two_words(ctw_obj);
    assert(ctw_obj[0] == 0 && ctw_obj[1] == 0);

    static uint32_t fpff_obj[2];
    fill_pair_ff(fpff_obj, 0xab);
    assert(fpff_obj[0] == 0xabababab && fpff_obj[1] == 0xabababab);

    static uint32_t iw1c_obj[8];
    iw1c_obj[7] = 5;
    increment_word_1c_b(iw1c_obj);
    assert(iw1c_obj[7] == 6);

    static uint32_t pw1c_obj2[8];
    static uint32_t pw1c_buf2[4];
    pw1c_obj2[7] = (uint32_t)(uintptr_t)pw1c_buf2;
    push_word_1c_b(pw1c_obj2, 0xaa);
    assert(pw1c_buf2[0] == 0xaa);
    assert(pw1c_obj2[7] == (uint32_t)(uintptr_t)pw1c_buf2 + 4);
    assert(pw1c_obj2[5] == 1);

    assert(return_16() == 0x10);

    assert(check_mask_18400(0) == 0);
    assert(check_mask_18400(0x18400 | 600) == 1);
    assert(check_mask_18400(0x18400 | 599) == 0);
    assert(check_mask_18400(0x18800 | 600) == 0);

    static uint8_t lg10_obj[0x40];
    lg10_obj[0x10] = 0x7f;
    assert(locked_get_byte_10(lg10_obj) == 0x7f);

    static uint8_t lg11_obj[0x40];
    lg11_obj[0x11] = 0x80;
    assert(locked_get_byte_11(lg11_obj) == -128);

    static uint8_t lg1c_obj[0x50];
    lg1c_obj[0x1c] = 0x42;
    assert(locked_get_byte_1c(lg1c_obj) == 0x42);

    static uint8_t lg14_obj[0x40];
    lg14_obj[0x14] = 0x55;
    assert(locked_get_byte_14(lg14_obj) == 0x55);
}

void run_batch_o_tests(void)
{
    static uint32_t rc4_obj[4];
    rc4_obj[1] = 5;
    rc4_obj[2] = 7;
    rc4_obj[3] = 9;
    reset_counters_4(rc4_obj);
    assert(rc4_obj[1] == 0 && rc4_obj[3] == 7);

    static uint8_t ir41c_obj[0x20];
    memset(ir41c_obj, 0xff, sizeof ir41c_obj);
    init_record_4_1c(ir41c_obj);
    assert(*(uint32_t *)(ir41c_obj + 8) == 0 && *(uint32_t *)(ir41c_obj + 4) == 0);
    assert(*(uint32_t *)(ir41c_obj + 0xc) == 0 && *(uint16_t *)(ir41c_obj + 0x1c) == 0);

    static uint32_t sb94_obj[0x9c / 4];
    static uint8_t sb94_sub[0x1c];
    static uint8_t sb98_sub[0x18];
    set_bytes_94_98(sb94_obj, 0x42);
    assert(sb94_sub[0x1b] == 0 && sb98_sub[0x17] == 0);
    sb94_obj[0x94 / 4] = (uint32_t)(uintptr_t)sb94_sub;
    sb94_obj[0x98 / 4] = (uint32_t)(uintptr_t)sb98_sub;
    set_bytes_94_98(sb94_obj, 0x42);
    assert(sb94_sub[0x1b] == 0x42 && sb98_sub[0x17] == 0x42);

    static uint8_t apbd_obj[0x10];
    apbd_obj[0xd] = 5;
    add_pointed_byte_d(apbd_obj, 3);
    assert(apbd_obj[0xd] == 8);

    static uint8_t spb17_obj[0x18];
    set_pointed_byte_17(spb17_obj, 0x99);
    assert(spb17_obj[0x17] == 0x99);

    static uint8_t sw8c_obj[0x90];
    *(float *)(sw8c_obj + 0x8c) = 3.0f;
    scale_word_8c(sw8c_obj);
    assert(*(float *)(sw8c_obj + 0x8c) == 6.0f);

    static uint32_t cw40_obj[0x44 / 4];
    assert(check_word_40_is_1(cw40_obj) == 0);
    cw40_obj[0x40 / 4] = 1;
    assert(check_word_40_is_1(cw40_obj) == 1);
    assert(get_word_40(cw40_obj) == 1);
}

void run_batch_p_tests(void)
{
    static uint8_t tb6c_obj[0x70];
    tb6c_obj[0x6c] = 5;
    assert(test_byte_6c_bit(tb6c_obj, 0) == 1);
    assert(test_byte_6c_bit(tb6c_obj, 2) == 1);
    assert(test_byte_6c_bit(tb6c_obj, 1) == 0);

    static uint32_t swp_obj[2];
    static uint32_t swp_tab[4];
    swp_tab[3] = 0x10;
    set_word_pair(swp_obj, (uint32_t)(uintptr_t)swp_tab);
    assert(swp_obj[0] == (uint32_t)(uintptr_t)swp_tab);
    assert(swp_obj[1] == (uint32_t)(uintptr_t)swp_tab + 0x10);

    static uint32_t cew_dest[9];
    static const uint32_t cew_src[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    copy_eleven_words(cew_dest, cew_src);
    assert(cew_dest[0] == 1 && cew_dest[1] == 2 && cew_dest[2] == 3);
    assert(cew_dest[3] == 5 && cew_dest[4] == 6 && cew_dest[5] == 7);
    assert(cew_dest[6] == 9 && cew_dest[7] == 10 && cew_dest[8] == 11);

    static uint32_t a8184_obj[3];
    a8184_obj[2] = 0x20000;
    assert(add_8_180_4(a8184_obj, 1, 2) == 0x20000 + 0x180 + 0x20 + 4);

    static uint8_t sw30_obj[0x34];
    *(float *)(sw30_obj + 0x30) = 1.0f;
    *(uint16_t *)(sw30_obj + 0x20) = 0;
    set_word_30_if_diff(sw30_obj, 1.0f);
    assert((*(uint16_t *)(sw30_obj + 0x20) & 8) == 0);
    set_word_30_if_diff(sw30_obj, 2.0f);
    assert(*(float *)(sw30_obj + 0x30) == 2.0f);
    assert((*(uint16_t *)(sw30_obj + 0x20) & 8) == 8);

    static uint32_t gh101_obj2[6];
    assert(get_if_halfword_10_is_101(gh101_obj2) == 0);
    *(int16_t *)((uint8_t *)gh101_obj2 + 0x10) = 0x101;
    gh101_obj2[5] = 0x40;
    assert(get_if_halfword_10_is_101(gh101_obj2) == (uint32_t)(uintptr_t)gh101_obj2 + 0x40);

    assert(clamp_to_3(0) == 0);
    assert(clamp_to_3(1) == 1);
    assert(clamp_to_3(2) == 3);
    assert(clamp_to_3(99) == 3);

    static uint32_t caf4_obj[3];
    static uint32_t caf4_sub[2];
    caf4_obj[1] = (uint32_t)(uintptr_t)caf4_sub;
    call_add_field_4_if_set(caf4_obj);
    ((uint8_t *)caf4_obj)[8] = 1;
    call_add_field_4_if_set(caf4_obj);

    static uint32_t rle_obj[8];
    static uint32_t rle_prev[2];
    static uint32_t rle_next[2];
    rle_obj[0] = 3;
    rle_obj[5] = (uint32_t)(uintptr_t)rle_prev;
    rle_obj[6] = (uint32_t)(uintptr_t)rle_next;
    rle_prev[1] = (uint32_t)(uintptr_t)rle_next;
    rle_next[0] = (uint32_t)(uintptr_t)rle_prev;
    remove_list_entry_b(rle_obj, rle_obj + 4);
    assert(rle_obj[0] == 2);
    assert(rle_obj[5] == 0 && rle_obj[6] == 0);

    static uint32_t ila_obj[8];
    static uint32_t ila_node2[3];
    ila_obj[0] = 1;
    ila_obj[1] = (uint32_t)(uintptr_t)&ila_obj[1];
    ila_obj[2] = (uint32_t)(uintptr_t)&ila_obj[1];
    insert_list_after_b(ila_obj, ila_node2 - 1);
    assert(ila_obj[0] == 2);
    assert(ila_obj[1] == (uint32_t)(uintptr_t)&ila_node2[0]);

    static uint8_t sw509d_obj[0xa0];
    set_word_50_byte_9d(sw509d_obj, 0x42, 0x999);
    assert(*(uint32_t *)(sw509d_obj + 0x50) == 0x999);
    assert(sw509d_obj[0x9d] == 0x42);
}

void run_batch_q_tests(void)
{
    static uint8_t sb60_obj[0x70];
    *(uint16_t *)(sb60_obj + 0x6c) = 5;
    sb60_obj[0x60] = 3;
    set_byte_60_ff_if_lower(sb60_obj, 0);
    assert(sb60_obj[0x60] == 0xff);
    sb60_obj[0x61] = 9;
    set_byte_60_ff_if_lower(sb60_obj, 1);
    assert(sb60_obj[0x61] == 9);
    set_byte_60_ff_if_lower(sb60_obj, 0xc);
    assert(sb60_obj[0x6c] == 5);

    static uint8_t sb77_obj[0x78];
    sb77_obj[0x74] = 3;
    set_byte_77_if_match(sb77_obj, 3);
    assert(sb77_obj[0x77] == 1);
    sb77_obj[0x77] = 0;
    set_byte_77_if_match(sb77_obj, 4);
    assert(sb77_obj[0x77] == 0);

    static uint32_t sp48_obj[3];
    sp48_obj[0] = 9;
    store_pair_4_8(sp48_obj, 1, 2);
    assert(sp48_obj[0] == 0 && sp48_obj[1] == 1 && sp48_obj[2] == 2);

    static uint8_t crc_dest[0x10];
    static const uint8_t crc_src[0x10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    copy_record_c(crc_dest, crc_src);
    assert(crc_dest[0xc] == 12);
    assert(*(uint32_t *)(crc_dest + 4) == 0x07060504);
    assert(*(uint32_t *)(crc_dest + 8) == 0x0b0a0908);

    static uint32_t sp8084_obj[0x8c / 4];
    static const uint32_t sp8084_src[2] = {0x11, 0x22};
    store_pair_80_84(sp8084_obj, sp8084_src);
    assert(sp8084_obj[0x80 / 4] == 0x11 && sp8084_obj[0x84 / 4] == 0x22);
    assert(((uint8_t *)sp8084_obj)[0x88] == 1);

    static uint32_t sp5458_obj[0x5c / 4];
    store_pair_54_58(sp5458_obj, 0x33, 0x44);
    assert(sp5458_obj[0x54 / 4] == 0x33 && sp5458_obj[0x58 / 4] == 0x44);

    static uint32_t sp8c_obj[5];
    static const uint32_t sp8c_src[2] = {0xaa, 0xbb};
    store_pair_8_c(sp8c_obj, sp8c_src);
    assert(sp8c_obj[2] == 0xaa && sp8c_obj[3] == 0xbb);
    assert(((uint8_t *)sp8c_obj)[0x10] == 1);

    static uint8_t cr810_obj[0x14];
    memset(cr810_obj, 0xff, sizeof cr810_obj);
    clear_record_8_10(cr810_obj);
    assert(*(uint32_t *)(cr810_obj + 8) == 0 && *(uint32_t *)(cr810_obj + 0xc) == 0);
    assert(cr810_obj[0x10] == 0);

    static uint32_t sw41c_obj[0x20 / 4];
    store_word_4_byte_1c(sw41c_obj, 0x77);
    assert(sw41c_obj[1] == 0x77 && ((uint8_t *)sw41c_obj)[0x1c] == 0);

    static uint32_t sw14_obj[6];
    sw14_obj[5] = 9;
    store_word_14_if_valid(sw14_obj, 0x50000);
    assert(sw14_obj[5] == 9);
    store_word_14_if_valid(sw14_obj, 0x100000);
    assert(sw14_obj[5] == 0x100000);
    store_word_14_if_valid(sw14_obj, 0x200000);
    assert(sw14_obj[5] == 0x100000);

    static uint8_t sh1e_obj[0x20];
    set_halfword_1e_mask(sh1e_obj, 0xffff);
    assert(*(uint16_t *)(sh1e_obj + 0x1e) == 0xfffe);

    static uint8_t sh1c_obj[0x1e];
    set_halfword_1c(sh1c_obj, 0x1234);
    assert(*(uint16_t *)(sh1c_obj + 0x1c) == 0x1234);

    static uint8_t sb1b7_obj[0x1d0];
    sb1b7_obj[0x1b7] = 1;
    set_byte_1b7_if_diff(sb1b7_obj, 1);
    assert(sb1b7_obj[0x1cf] == 0);
    set_byte_1b7_if_diff(sb1b7_obj, 2);
    assert(sb1b7_obj[0x1b7] == 2 && (sb1b7_obj[0x1cf] & 2) == 2);

    static uint8_t ir1c28_obj[0x2c];
    init_record_1c_28(ir1c28_obj);
    assert(ir1c28_obj[0x14] == 6);
    assert(*(uint32_t *)(ir1c28_obj + 0x1c) == 0 && *(uint32_t *)(ir1c28_obj + 0x28) == 0);
    assert(*(uint32_t *)(ir1c28_obj + 0x24) == 0 && *(uint32_t *)(ir1c28_obj + 4) == 10);

    static uint8_t ir90_obj[0x94];
    *(uint32_t *)(ir90_obj + 0x90) = 9;
    init_record_90(ir90_obj);
    assert(*(uint32_t *)(ir90_obj + 0x90) == 0);
}

void run_batch_r_tests(void)
{
    static uint32_t cw4_obj[2];
    assert(check_word_4_nonzero(cw4_obj) == 0);
    cw4_obj[1] = 5;
    assert(check_word_4_nonzero(cw4_obj) == 1);

    static uint8_t cb8_obj[0xc];
    cb8_obj[8] = 0;
    assert(check_byte_8_is_0_or_7(cb8_obj) == 1);
    cb8_obj[8] = 7;
    assert(check_byte_8_is_0_or_7(cb8_obj) == 1);
    cb8_obj[8] = 5;
    assert(check_byte_8_is_0_or_7(cb8_obj) == 0);

    static uint8_t cb28_obj[0x2c];
    cb28_obj[0x28] = 0;
    assert(check_byte_28_is_0_or_8(cb28_obj) == 1);
    cb28_obj[0x28] = 8;
    assert(check_byte_28_is_0_or_8(cb28_obj) == 1);
    cb28_obj[0x28] = 3;
    assert(check_byte_28_is_0_or_8(cb28_obj) == 0);

    static uint8_t coc80_dest[0x88];
    static uint8_t coc80_src[0x88];
    memset(coc80_dest, 0, sizeof coc80_dest);
    memset(coc80_src, 0x5a, sizeof coc80_src);
    copy_or_clear_80(coc80_dest, coc80_src);
    assert(*(uint32_t *)(coc80_dest + 0x80) == 0x5a5a5a5a);
    assert(*(uint16_t *)(coc80_dest + 0x84) == 0x5a5a);
    copy_or_clear_80(coc80_dest, NULL);
    assert(*(uint32_t *)(coc80_dest + 0x80) == 0);
    assert(*(uint16_t *)(coc80_dest + 0x84) == 0);

    static uint32_t pwfa8_obj[0xfb8 / 4];
    push_word_fa8(pwfa8_obj, 0xaa);
    assert(pwfa8_obj[0xfa8 / 4] == 1);
    assert(pwfa8_obj[0xfa8 / 4 + 1] == 0xaa);
    push_word_fa8(pwfa8_obj, 0xbb);
    assert(pwfa8_obj[0xfa8 / 4] == 2);

    static uint8_t sbd6_obj[0xd8];
    set_byte_d6_bit(sbd6_obj, 3);
    assert((sbd6_obj[0xd6] & 8) == 8);
    set_byte_d6_bit(sbd6_obj, 0);
    assert((sbd6_obj[0xd6] & 9) == 9);

    static uint8_t gbcff_obj[0xd00];
    assert(get_byte_cff_if_cfe(gbcff_obj) == 0);
    gbcff_obj[0xcfe] = 1;
    gbcff_obj[0xcff] = 0x80;
    assert(get_byte_cff_if_cfe(gbcff_obj) == -128);

    static uint8_t c1ff1a4_obj[0x200];
    c1ff1a4_obj[0x1ff] = 2;
    c1ff1a4_obj[0x1a4] = 2;
    assert(check_1ff_1a4(c1ff1a4_obj) == 1);
    c1ff1a4_obj[0x1a4] = 3;
    assert(check_1ff_1a4(c1ff1a4_obj) == 0);
    c1ff1a4_obj[0x1ff] = 1;
    c1ff1a4_obj[0x1a4] = 2;
    assert(check_1ff_1a4(c1ff1a4_obj) == 0);

    static uint8_t c1ff178_obj[0x200];
    c1ff178_obj[0x1ff] = 1;
    c1ff178_obj[0x178] = 2;
    assert(check_1ff_178(c1ff178_obj) == 1);
    c1ff178_obj[0x178] = 3;
    assert(check_1ff_178(c1ff178_obj) == 0);

    static uint8_t cb202_obj[0x204];
    cb202_obj[0x202] = 9;
    clear_byte_202(cb202_obj);
    assert(cb202_obj[0x202] == 0);

    static uint32_t a158_obj[0x160 / 4];
    a158_obj[0x158 / 4] = 5;
    a158_obj[0x15c / 4] = 3;
    add_158_15c(a158_obj);
    assert(a158_obj[0x158 / 4] == 8);

    static uint8_t ob9894_obj[0x9898];
    or_byte_9894(ob9894_obj);
    assert((ob9894_obj[0x9894] & 2) == 2);
}

void run_batch_s_tests(void)
{
    static uint8_t sfh_obj[0x11c];
    store_four_halfwords_114(sfh_obj, 1, 2, 3, 4);
    assert(*(uint16_t *)(sfh_obj + 0x114) == 1 && *(uint16_t *)(sfh_obj + 0x116) == 2);
    assert(*(uint16_t *)(sfh_obj + 0x118) == 3 && *(uint16_t *)(sfh_obj + 0x11a) == 4);

    static uint8_t tb5e8_obj[0x5ec];
    toggle_byte_5e8(tb5e8_obj);
    assert(tb5e8_obj[0x5e8] == 1);
    toggle_byte_5e8(tb5e8_obj);
    assert(tb5e8_obj[0x5e8] == 0);

    static uint32_t sp594_obj[0x1724 / 4];
    store_pair_594_1720(sp594_obj, 0x11, 0x22);
    assert(sp594_obj[0x594 / 4] == 0x11 && sp594_obj[0x1720 / 4] == 0x22);

    static uint8_t ss2_obj[0x10];
    static uint8_t ss2_mid[0xbdc];
    *(uint32_t *)(ss2_obj + 4) = (uint32_t)(uintptr_t)ss2_mid;
    ss2_mid[0xbd8] = 0;
    assert(set_state_2_if_flag(ss2_obj) == 1);
    assert(*(uint16_t *)(ss2_obj + 0xc) == 0);
    ss2_mid[0xbd8] = 1;
    assert(set_state_2_if_flag(ss2_obj) == 1);
    assert(*(uint16_t *)(ss2_obj + 0xc) == 2);

    static uint8_t ss10_obj[0x10];
    static uint8_t ss10_mid[0xbdc];
    *(uint32_t *)(ss10_obj + 4) = (uint32_t)(uintptr_t)ss10_mid;
    ss10_mid[0xbd8] = 1;
    assert(set_state_10_if_flag(ss10_obj) == 1);
    assert(*(uint16_t *)(ss10_obj + 0xc) == 10);

    static uint8_t ss2b_obj[0x10];
    static uint8_t ss2b_mid[0xbdc];
    *(uint32_t *)(ss2b_obj + 4) = (uint32_t)(uintptr_t)ss2b_mid;
    ss2b_mid[0xbd8] = 1;
    assert(set_state_2_if_flag_b(ss2b_obj) == 1);
    assert(*(uint16_t *)(ss2b_obj + 0xc) == 2);

    static uint8_t ss8_obj[0x10];
    static uint8_t ss8_mid[0xb0c];
    static uint8_t ss8_tab[0x98];
    *(uint32_t *)(ss8_obj + 4) = (uint32_t)(uintptr_t)ss8_mid;
    *(uint32_t *)(ss8_mid + 0xb08) = (uint32_t)(uintptr_t)ss8_tab;
    *(int16_t *)(ss8_tab + 0x96) = 0;
    assert(set_state_8_if_halfword_96_zero(ss8_obj) == 1);
    assert(*(uint16_t *)(ss8_obj + 0xc) == 8);
    *(int16_t *)(ss8_tab + 0x96) = 1;
    *(uint16_t *)(ss8_obj + 0xc) = 0;
    assert(set_state_8_if_halfword_96_zero(ss8_obj) == 1);
    assert(*(uint16_t *)(ss8_obj + 0xc) == 0);

    static uint8_t ob3eff_obj[0x3f08];
    or_byte_3eff_set_3f05_4(ob3eff_obj);
    assert((ob3eff_obj[0x3eff] & 1) == 1 && ob3eff_obj[0x3f05] == 4);

    ob3eff_obj[0x3eff] = 0xff;
    and_byte_3eff_set_3f05_2(ob3eff_obj);
    assert((ob3eff_obj[0x3eff] & 1) == 0 && ob3eff_obj[0x3f05] == 2);

    ob3eff_obj[0x3eff] = 0;
    or_byte_3eff_2_set_3f05_4(ob3eff_obj);
    assert((ob3eff_obj[0x3eff] & 2) == 2 && ob3eff_obj[0x3f05] == 4);

    ob3eff_obj[0x3eff] = 0xff;
    and_byte_3eff_fd_set_3f05_2(ob3eff_obj);
    assert((ob3eff_obj[0x3eff] & 2) == 0 && ob3eff_obj[0x3f05] == 2);

    static uint32_t sw4_obj[2];
    store_word_4(sw4_obj, 0x11);
    assert(sw4_obj[1] == 0x11);
    store_word_4_b(sw4_obj, 0x22);
    assert(sw4_obj[1] == 0x22);
    store_word_4_c(sw4_obj, 0x33);
    assert(sw4_obj[1] == 0x33);

    static uint8_t rr10_obj[0x18];
    memset(rr10_obj, 0xff, sizeof rr10_obj);
    *(uint32_t *)(rr10_obj + 4) = 0x77;
    reset_record_10(rr10_obj);
    assert(*(uint32_t *)(rr10_obj + 0xc) == 0 && rr10_obj[0x16] == 0);
    assert(*(uint16_t *)(rr10_obj + 0x12) == 0 && *(uint16_t *)(rr10_obj + 0x10) == 0);
    assert(*(uint32_t *)(rr10_obj + 8) == 0x77);

    static uint32_t swl_obj[3];
    static const uint16_t swl_str[4] = {0x41, 0x42, 0x43, 0};
    store_word_1_word_2_len(swl_obj, swl_str);
    assert(swl_obj[0] == 0 && swl_obj[1] == (uint32_t)(uintptr_t)swl_str);
    assert(swl_obj[2] == 6);
}

void run_batch_t_tests(void)
{
    static uint32_t cbi_tab[4];
    static uint32_t cbi_out;
    cbi_tab[0] = 5;
    cbi_tab[1] = 0xaa;
    cbi_tab[2] = 0xbb;
    assert(count_bits_and_index(cbi_tab, &cbi_out, 0) == 1);
    assert(cbi_out == 0xaa);
    assert(count_bits_and_index(cbi_tab, &cbi_out, 2) == 1);
    assert(cbi_out == 0xbb);
    assert(count_bits_and_index(cbi_tab, &cbi_out, 1) == 0);
    cbi_tab[0] = 0;
    assert(count_bits_and_index(cbi_tab, &cbi_out, 0xffffffff) == 0);
    cbi_tab[0] = 7;
    assert(count_bits_and_index(cbi_tab, &cbi_out, 0xffffffff) == 0);

    static uint8_t ss5_obj[0x10];
    static uint8_t ss5_mid[0xbdc];
    *(uint32_t *)(ss5_obj + 4) = (uint32_t)(uintptr_t)ss5_mid;
    ss5_mid[0xbd8] = 1;
    assert(set_state_5_if_flag(ss5_obj) == 1);
    assert(*(uint16_t *)(ss5_obj + 0xc) == 5);
    ss5_mid[0xbd8] = 0;
    *(uint16_t *)(ss5_obj + 0xc) = 0;
    assert(set_state_5_if_flag(ss5_obj) == 1);
    assert(*(uint16_t *)(ss5_obj + 0xc) == 0);

    static uint8_t ss15_obj[0x10];
    static uint8_t ss15_mid[0xbdc];
    *(uint32_t *)(ss15_obj + 4) = (uint32_t)(uintptr_t)ss15_mid;
    ss15_mid[0xbd8] = 1;
    assert(set_state_15_if_flag(ss15_obj) == 1);
    assert(*(uint16_t *)(ss15_obj + 0xc) == 0xf);

    static const uint32_t sfw_obj[4] = {0x11, 0x22, 0x33, 0x44};
    uint32_t sfw_a = 0, sfw_b = 0, sfw_c = 0, sfw_d = 0;
    split_four_words(sfw_obj, &sfw_a, &sfw_b, &sfw_c, &sfw_d);
    assert(sfw_a == 0x11 && sfw_b == 0x22 && sfw_c == 0x33 && sfw_d == 0x44);

    static uint32_t gcb_obj[0x24 / 4];
    gcb_obj[5] = 5;
    gcb_obj[6] = 0xaa;
    gcb_obj[7] = 0xbb;
    assert(get_config_byte_14_1(gcb_obj, 0) == 0x40);
    assert(get_config_byte_14_2(gcb_obj, 0) == 0xbb);
    gcb_obj[5] = 1;
    assert(get_config_byte_14_2(gcb_obj, 0) == 0x40);
    assert(get_config_byte_14_0(gcb_obj, 0) == 0xaa);
    gcb_obj[5] = 0;
    assert(get_config_byte_14_0(gcb_obj, 0) == 0x40);

    gcb_obj[5] = 5;
    gcb_obj[7] = 0x123456;
    assert(get_config_word_14_2(gcb_obj, 0) == 0x12);
    gcb_obj[5] = 0;
    assert(get_config_word_14_2(gcb_obj, 0) == 0);
}

void run_batch_u_tests(void)
{
    static uint32_t cfg_obj[0x2c / 4];
    cfg_obj[5] = 5;
    cfg_obj[6] = 0x12aa;
    cfg_obj[7] = 0x34bb;
    assert(get_config_word_14_2_high(cfg_obj, 0) == 0x34);
    cfg_obj[5] = 0;
    assert(get_config_word_14_2_high(cfg_obj, 0) == 0);

    cfg_obj[5] = 1;
    cfg_obj[6] = 0xff80;
    assert(get_config_signed_byte_14_0(cfg_obj, 0) == -1);
    cfg_obj[5] = 0;
    assert(get_config_signed_byte_14_0(cfg_obj, 0) == 0);

    cfg_obj[1] = 1;
    cfg_obj[2] = 0xcc;
    assert(get_config_byte_4_0(cfg_obj, 0) == 0xcc);
    cfg_obj[1] = 0;
    assert(get_config_byte_4_0(cfg_obj, 0) == 0x40);

    cfg_obj[1] = 5;
    cfg_obj[3] = 0xdd;
    assert(get_config_byte_4_2(cfg_obj, 0) == 0xdd);
    assert(get_config_byte_4_2_b(cfg_obj, 0) == 0xdd);
    cfg_obj[1] = 0;
    assert(get_config_byte_4_2(cfg_obj, 0) == 0x40);
    assert(get_config_byte_4_2_b(cfg_obj, 0) == 0x40);

    cfg_obj[1] = 3;
    cfg_obj[3] = 0xee;
    assert(get_config_byte_4_1_60(cfg_obj, 0) == 0xee);
    cfg_obj[1] = 0;
    assert(get_config_byte_4_1_60(cfg_obj, 0) == 0x60);

    cfg_obj[1] = 3;
    cfg_obj[3] = 0x12345;
    assert(get_config_word_4_1(cfg_obj, 0) == 0x12345);
    cfg_obj[1] = 0;
    assert(get_config_word_4_1(cfg_obj, 0) == 0);

    cfg_obj[2] = 1;
    cfg_obj[3] = 0x77;
    assert(get_config_byte_8_0(cfg_obj, 0) == 0x77);
    cfg_obj[2] = 0;
    assert(get_config_byte_8_0(cfg_obj, 0) == 0x40);

    cfg_obj[2] = 3;
    cfg_obj[4] = 0x999;
    assert(get_config_word_8_1(cfg_obj, 0) == 0x999);
    cfg_obj[2] = 0;
    assert(get_config_word_8_1(cfg_obj, 0) == 0);

    cfg_obj[3] = 1;
    cfg_obj[4] = 0x555;
    assert(get_config_word_c_0(cfg_obj, 0) == 0x555);
    cfg_obj[3] = 0;
    assert(get_config_word_c_0(cfg_obj, 0) == 0);

    cfg_obj[3] = 3;
    cfg_obj[5] = 0x66;
    assert(get_config_byte_c_1(cfg_obj, 0) == 0x66);
    cfg_obj[3] = 0;
    assert(get_config_byte_c_1(cfg_obj, 0) == 0x40);

    cfg_obj[6] = 5;
    cfg_obj[8] = 0x777;
    assert(get_config_word_18_2(cfg_obj, 0) == 0x777);
    cfg_obj[6] = 0;
    assert(get_config_word_18_2(cfg_obj, 0) == 0);

    cfg_obj[6] = 3;
    cfg_obj[8] = 0x888;
    assert(get_config_word_18_1(cfg_obj, 0) == 0x888);
    cfg_obj[6] = 0;
    assert(get_config_word_18_1(cfg_obj, 0) == 0);

    cfg_obj[6] = 1;
    cfg_obj[7] = 0x42;
    assert(get_config_byte_18_0(cfg_obj, 0) == 0x42);
    cfg_obj[6] = 0;
    assert(get_config_byte_18_0(cfg_obj, 0) == 1);

    cfg_obj[5] = 0x101;
    cfg_obj[7] = 0x40;
    assert(get_config_offset_14_8(cfg_obj, 0) == (uint32_t)(uintptr_t)cfg_obj + 0x40);
    cfg_obj[5] = 0;
    assert(get_config_offset_14_8(cfg_obj, 0) == 0);

    cfg_obj[1] = 1;
    cfg_obj[2] = 0x33;
    assert(get_config_byte_4_0_3c(cfg_obj, 0) == 0x33);
    cfg_obj[1] = 0;
    assert(get_config_byte_4_0_3c(cfg_obj, 0) == 0x3c);

    cfg_obj[1] = 3;
    cfg_obj[3] = 0x55;
    assert(get_config_byte_4_1_7f(cfg_obj, 0) == 0x55);
    cfg_obj[1] = 0;
    assert(get_config_byte_4_1_7f(cfg_obj, 0) == 0x7f);

    cfg_obj[5] = 3;
    cfg_obj[7] = 0x42;
    assert(get_config_byte_14_1_or_0(cfg_obj, 0) == 0x42);
    cfg_obj[5] = 0;
    assert(get_config_byte_14_1_or_0(cfg_obj, 0) == 0);

    cfg_obj[5] = 3;
    cfg_obj[7] = 0xab00;
    assert(get_config_word_14_1_high(cfg_obj, 0) == 0xab);
    cfg_obj[5] = 0;
    assert(get_config_word_14_1_high(cfg_obj, 0) == 0);

    cfg_obj[5] = 0x20001;
    cfg_obj[9] = 1;
    cfg_obj[9] = 0;
    assert(get_config_bit_14_17(cfg_obj, 0) == 0);

    cfg_obj[5] = 5;
    cfg_obj[7] = 0xcd00;
    assert(get_config_word_14_2_high_b(cfg_obj, 0) == 0xcd);
    cfg_obj[5] = 0;
    assert(get_config_word_14_2_high_b(cfg_obj, 0) == 0);

    cfg_obj[1] = 5;
    cfg_obj[3] = 0xef00;
    assert(get_config_word_4_2_high(cfg_obj, 0) == 0xef);
    cfg_obj[1] = 0;
    assert(get_config_word_4_2_high(cfg_obj, 0) == 0);

    cfg_obj[2] = 1;
    cfg_obj[3] = 0x1200;
    assert(get_config_word_8_0_high(cfg_obj, 0) == 0x12);
    cfg_obj[2] = 0;
    assert(get_config_word_8_0_high(cfg_obj, 0) == 0);

    cfg_obj[1] = 0x11;
    cfg_obj[3] = 0xab00;
    assert(get_config_word_4_4_high(cfg_obj, 0) == 0xab);
    cfg_obj[1] = 0;
    assert(get_config_word_4_4_high(cfg_obj, 0) == 0);

    cfg_obj[1] = 0x11;
    cfg_obj[3] = 0x42;
    assert(get_config_flag_4_4(cfg_obj, 0) == 1);
    cfg_obj[3] = 0;
    assert(get_config_flag_4_4(cfg_obj, 0) == 0);

    cfg_obj[1] = 0x11;
    cfg_obj[3] = 0x990000;
    assert(get_config_top_byte_4_4(cfg_obj, 0) == 0x99);
    cfg_obj[1] = 0;
    assert(get_config_top_byte_4_4(cfg_obj, 0) == 0);
}

void run_batch_v_tests(void)
{
    static uint32_t cib8_obj[3];
    clear_if_byte_8(cib8_obj);
    assert(cib8_obj[0] == 0);
    cib8_obj[0] = 1;
    cib8_obj[1] = 2;
    ((uint8_t *)cib8_obj)[8] = 1;
    clear_if_byte_8(cib8_obj);
    assert(cib8_obj[0] == 0 && cib8_obj[1] == 0);
    assert(((uint8_t *)cib8_obj)[8] == 0);

    static uint32_t cibc_obj[4];
    cibc_obj[0] = 1;
    cibc_obj[2] = 3;
    ((uint8_t *)cibc_obj)[0xc] = 1;
    clear_if_byte_c(cibc_obj);
    assert(cibc_obj[0] == 0 && cibc_obj[1] == 0 && cibc_obj[2] == 0);
    assert(((uint8_t *)cibc_obj)[0xc] == 0);

    static uint32_t ctwb_obj[2];
    ctwb_obj[0] = 1;
    ctwb_obj[1] = 2;
    clear_two_words_b(ctwb_obj);
    assert(ctwb_obj[0] == 0 && ctwb_obj[1] == 0);

    static uint32_t ir414_obj[8];
    memset(ir414_obj, 0xff, sizeof ir414_obj);
    init_record_4_14(ir414_obj, 0x11, 0x22);
    assert(((uint8_t *)ir414_obj)[4] == 0);
    assert(ir414_obj[3] == 0 && ir414_obj[5] == 0x11);
    assert(ir414_obj[4] == 0 && ir414_obj[0] == 0);
    assert(ir414_obj[6] == 0x22 && ir414_obj[7] == 0);

    static uint8_t sw38_obj[0x3c];
    *(float *)(sw38_obj + 0x38) = 1.0f;
    *(uint16_t *)(sw38_obj + 0x20) = 0;
    set_word_38_if_diff(sw38_obj, 1.0f);
    assert((*(uint16_t *)(sw38_obj + 0x20) & 0x10) == 0);
    set_word_38_if_diff(sw38_obj, 2.0f);
    assert((*(uint16_t *)(sw38_obj + 0x20) & 0x10) == 0x10);

    static uint8_t sw34_obj[0x38];
    *(float *)(sw34_obj + 0x34) = 1.0f;
    *(uint16_t *)(sw34_obj + 0x20) = 0;
    set_word_34_if_diff(sw34_obj, 2.0f);
    assert((*(uint16_t *)(sw34_obj + 0x20) & 8) == 8);

    static uint8_t sw28_obj[0x2c];
    *(float *)(sw28_obj + 0x28) = 1.0f;
    *(uint16_t *)(sw28_obj + 0x20) = 0;
    set_word_28_if_diff(sw28_obj, 2.0f);
    assert((*(uint16_t *)(sw28_obj + 0x20) & 4) == 4);

    static uint8_t sw108_obj[0x10c];
    store_word_108_byte_fe(sw108_obj, 0x99, 0x42);
    assert(*(uint32_t *)(sw108_obj + 0x108) == 0x99);
    assert(sw108_obj[0xfe] == 0x42);

    static uint8_t sw28b_obj[0x30];
    store_word_28_byte_2c(sw28b_obj, 0x88, 0x55);
    assert(*(uint32_t *)(sw28b_obj + 0x28) == 0x88);
    assert(sw28b_obj[0x2c] == 0x55);

    static uint32_t swi38_obj[0x44 / 4];
    store_word_indexed_38(swi38_obj, 2, 0x77);
    assert(swi38_obj[0x38 / 4 + 2] == 0x77);

    static uint32_t giw94_obj[0xa4 / 4];
    giw94_obj[0x94 / 4 + 3] = 0x66;
    assert(get_indexed_word_94(giw94_obj, 3) == 0x66);
    assert(get_indexed_word_94(giw94_obj, 0x10) == 0);

    static uint8_t shd4_obj[0xdc];
    set_halfword_d4(shd4_obj, 2, 0x1234);
    assert(*(uint16_t *)(shd4_obj + 4 + 0xd4) == 0x1234);
}

void run_batch_w_tests(void)
{
    static uint32_t gnb_obj[1];
    static uint8_t gnb_tab[0xb0c];
    assert(get_nested_b08_word(gnb_obj) == 0);
    gnb_obj[0] = (uint32_t)(uintptr_t)gnb_tab;
    *(uint32_t *)(gnb_tab + 0xb08) = 0x99;
    assert(get_nested_b08_word(gnb_obj) == 0x99);

    static uint8_t snf8_obj[0xb10];
    static uint8_t snf8_tab[0xfc];
    *(uint32_t *)(snf8_obj + 0xb08) = (uint32_t)(uintptr_t)snf8_tab;
    set_nested_f7_f8(snf8_obj, 0x66, 0);
    assert(snf8_tab[0xf7] == 0x66 && snf8_tab[0xf8] == 4);
    set_nested_f7_f8(snf8_obj, 0x77, 9);
    assert(snf8_tab[0xf7] == 0x77 && snf8_tab[0xf8] == 9);

    static uint32_t on48_obj[2];
    static uint8_t on48_mid[0xb0c];
    static uint32_t on48_tab[0x4c / 4];
    on48_obj[1] = (uint32_t)(uintptr_t)on48_mid;
    *(uint32_t *)(on48_mid + 0xb08) = (uint32_t)(uintptr_t)on48_tab;
    on48_tab[0x48 / 4] = 0xffffffff;
    and_nested_b08_word_48(on48_obj);
    assert(on48_tab[0x48 / 4] == 0xffff5fff);

    static uint32_t cnh96_obj[2];
    static uint8_t cnh96_mid[0xb0c];
    static uint8_t cnh96_tab[0x98];
    cnh96_obj[1] = (uint32_t)(uintptr_t)cnh96_mid;
    *(uint32_t *)(cnh96_mid + 0xb08) = (uint32_t)(uintptr_t)cnh96_tab;
    *(int16_t *)(cnh96_tab + 0x96) = 0;
    assert(check_nested_b08_halfword_96(cnh96_obj) == 1);
    *(int16_t *)(cnh96_tab + 0x96) = 1;
    assert(check_nested_b08_halfword_96(cnh96_obj) == 0);

    static uint8_t ssf3_obj[0x10];
    static uint8_t ssf3_mid[0xb0c];
    static uint8_t ssf3_tab[0xf4];
    *(uint32_t *)(ssf3_obj + 4) = (uint32_t)(uintptr_t)ssf3_mid;
    *(uint32_t *)(ssf3_mid + 0xb08) = (uint32_t)(uintptr_t)ssf3_tab;
    assert(set_state_1_if_nested_f3_zero(ssf3_obj) == 1);
    assert(*(uint16_t *)(ssf3_obj + 0xc) == 1);
    *(uint16_t *)(ssf3_obj + 0xc) = 0;
    ssf3_tab[0xf3] = 1;
    assert(set_state_1_if_nested_f3_zero(ssf3_obj) == 1);
    assert(*(uint16_t *)(ssf3_obj + 0xc) == 0);
}

void run_batch_x_tests(void)
{
    static uint8_t fte_obj[0x44];
    *(uint16_t *)(fte_obj + 0x10) = 0;
    assert(find_tagged_entry(fte_obj, 0x4000) == 0);
    *(uint16_t *)(fte_obj + 0x10) = 3;
    *(uint16_t *)(fte_obj + 0x14) = 0x4000;
    *(uint16_t *)(fte_obj + 0x20) = 0x4001;
    *(uint16_t *)(fte_obj + 0x2c) = 0x4002;
    assert(find_tagged_entry(fte_obj, 0x4000) == (uint32_t)(uintptr_t)(fte_obj + 0x14));
    assert(find_tagged_entry(fte_obj, 0x4001) == (uint32_t)(uintptr_t)(fte_obj + 0x20));
    assert(find_tagged_entry(fte_obj, 0x4002) == (uint32_t)(uintptr_t)(fte_obj + 0x2c));
    assert(find_tagged_entry(fte_obj, 0x4004) == 0);

    static uint32_t s8e4_out;
    static uint32_t s8e4_obj[3];
    s8e4_obj[2] = 0x30000;
    store_8_180_18_e4(&s8e4_out, s8e4_obj, 1, 2);
    assert(s8e4_out == 0x30000 + 0x180 + 0x30 + 0xe4);

    static uint32_t snf8_out;
    static uint32_t snf8_obj[3];
    static uint8_t snf8_tab[0x180 + 0x18 + 0xfc];
    snf8_obj[2] = (uint32_t)(uintptr_t)snf8_tab;
    *(uint32_t *)(snf8_tab + 0x180 + 0x18 + 0xf8) = 0x777;
    store_nested_8_180_18_f8(snf8_obj, 1, 1, &snf8_out);
    assert(snf8_out == 0x777);

    static uint8_t gn984_obj[0x94];
    static uint8_t gn984_mid[0xc];
    static uint8_t gn984_tab[8];
    *(uint32_t *)(gn984_obj + 0x90) = (uint32_t)(uintptr_t)gn984_mid;
    *(uint32_t *)(gn984_mid + 8) = (uint32_t)(uintptr_t)gn984_tab;
    *(int8_t *)(gn984_tab + 4) = -5;
    assert(get_nested_90_8_4((uint32_t)(uintptr_t)gn984_obj) == -5);

    static uint32_t gh101_obj3[4];
    assert(get_if_halfword_8_is_101(gh101_obj3) == 0);
    *(int16_t *)((uint8_t *)gh101_obj3 + 8) = 0x101;
    gh101_obj3[3] = 0x50;
    assert(get_if_halfword_8_is_101(gh101_obj3) == (uint32_t)(uintptr_t)gh101_obj3 + 0x50);

    *(uint16_t *)(fte_obj + 0x14) = 0x4000;
    *(uint32_t *)(fte_obj + 0x14 + 4) = 0x111;
    *(uint32_t *)(fte_obj + 0x14 + 8) = 0x222;
    assert(check_tag_4001_exists((uint32_t *)fte_obj) == 1);
    assert(check_tag_4003_exists((uint32_t *)fte_obj) == 0);
    assert(get_tag_4000_word_8((uint32_t *)fte_obj) == 0x222);
    assert(get_tag_4000_word_4((uint32_t *)fte_obj) == 0x111);

    *(uint16_t *)(fte_obj + 0x20) = 0x4001;
    *(uint32_t *)(fte_obj + 0x20 + 4) = 0x333;
    assert(get_tag_4001_word_4((uint32_t *)fte_obj) == 0x333);
    *(uint16_t *)(fte_obj + 0x2c) = 0x4002;
    *(uint32_t *)(fte_obj + 0x2c + 4) = 0x444;
    assert(get_tag_4002_word_4((uint32_t *)fte_obj) == 0x444);
}

void run_batch_y_tests(void)
{
    assert(abs_diff_within_wrap(10, 5, 6) == 1);
    assert(abs_diff_within_wrap(5, 10, 4) == 0);
    assert(abs_diff_within_wrap(-5, 5, 10) == 1);
    assert(abs_diff_within_wrap(0, 0xf000, 0x1000) == 1);
    assert(abs_diff_within_wrap(0, 0xf000, 0x0fff) == 0);

    static uint8_t ss3_obj[0x10];
    assert(set_state_3_if_halfword_e_is_2(ss3_obj) == 0);
    *(int16_t *)(ss3_obj + 0xe) = 2;
    assert(set_state_3_if_halfword_e_is_2(ss3_obj) == 1);
    assert(*(uint16_t *)(ss3_obj + 0xc) == 3);

    static uint8_t sh41e_obj[0x420];
    set_halfword_41e_4(sh41e_obj);
    assert(*(uint16_t *)(sh41e_obj + 0x41e) == 4);

    static uint8_t ss2n_obj[0x10];
    assert(set_state_2_if_halfword_e_not_2(ss2n_obj) == 1);
    assert(*(uint16_t *)(ss2n_obj + 0xc) == 2);
    *(int16_t *)(ss2n_obj + 0xe) = 2;
    *(uint16_t *)(ss2n_obj + 0xc) = 0;
    assert(set_state_2_if_halfword_e_not_2(ss2n_obj) == 0);
    assert(*(uint16_t *)(ss2n_obj + 0xc) == 0);

    static uint32_t sw24_obj[0x2c / 4];
    set_word_24_flag_2b(sw24_obj, 0);
    assert(sw24_obj[0x24 / 4] == 0 && ((uint8_t *)sw24_obj)[0x2b] == 0);
    set_word_24_flag_2b(sw24_obj, 0x55);
    assert(sw24_obj[0x24 / 4] == 0x55 && ((uint8_t *)sw24_obj)[0x2b] == 1);

    static uint8_t chwe_obj[0x10];
    assert(check_halfword_e_is_2(chwe_obj) == 0);
    *(int16_t *)(chwe_obj + 0xe) = 2;
    assert(check_halfword_e_is_2(chwe_obj) == 1);

    static uint8_t ir70_obj[0x7c];
    memset(ir70_obj, 0xff, sizeof ir70_obj);
    init_record_70(ir70_obj);
    assert(ir70_obj[0x70] == 0 && ir70_obj[0x71] == 0 && ir70_obj[0x72] == 0);
    assert(ir70_obj[0x73] == 0 && ir70_obj[0x75] == 0);
    assert(*(uint32_t *)(ir70_obj + 0x78) == 0);

    static uint32_t cpb08_dest[2];
    static uint8_t cpb08_src[0xb10];
    *(uint32_t *)(cpb08_src + 0xb08) = 0x1111;
    *(uint32_t *)(cpb08_src + 0xb0c) = 0x2222;
    copy_pair_b08(cpb08_dest, cpb08_src);
    assert(cpb08_dest[0] == 0x1111 && cpb08_dest[1] == 0x2222);

    static uint32_t gnc48_obj[0xc4c / 4];
    static uint32_t gnc48_tab[6];
    static uint32_t gnc48_val[1];
    gnc48_obj[0xc48 / 4] = (uint32_t)(uintptr_t)gnc48_tab;
    gnc48_tab[5] = (uint32_t)(uintptr_t)gnc48_val;
    gnc48_val[0] = 0x888;
    assert(get_nested_c48_14(gnc48_obj) == 0x888);

    static uint32_t sw254_obj[7];
    static uint32_t sw254_a[0x258 / 4];
    static uint32_t sw254_b[0x258 / 4];
    static const uint32_t sw254_val[1] = {0x999};
    sw254_obj[4] = (uint32_t)(uintptr_t)sw254_a;
    sw254_obj[6] = (uint32_t)(uintptr_t)sw254_b;
    store_word_254_pair(sw254_obj, sw254_val);
    assert(sw254_a[0x254 / 4] == 0x999 && sw254_b[0x254 / 4] == 0x999);

    static uint8_t am179_obj[0x1c8];
    advance_and_mark_179(am179_obj);
    assert(am179_obj[0x179] == 1);
    assert(am179_obj[0x1c5] == 2);

    static uint32_t gn34_obj[2];
    static uint8_t gn34_mid[0x40];
    static uint32_t gn34_tab[0x38 / 4];
    gn34_obj[1] = (uint32_t)(uintptr_t)gn34_mid;
    *(uint32_t *)(gn34_mid + 0x3c) = (uint32_t)(uintptr_t)gn34_tab;
    gn34_tab[0x34 / 4] = 0;
    gn34_tab[0] = 0x555;
    assert(get_nested_3c_34_deref(gn34_obj) == 0x555);
    assert(get_nested_word_4_plus_4(gn34_obj) == 0x555 * 4 + 4);
}

void run_batch_z_tests(void)
{
    static uint8_t gw14c_obj[0x150];
    *(uint32_t *)(gw14c_obj + 0x14c) = 0x42;
    assert(get_word_14c_as_float(gw14c_obj) == 0x42);

    static uint8_t c149_obj[0x154];
    assert(check_149_150(c149_obj) == 0);
    c149_obj[0x149] = 1;
    assert(check_149_150(c149_obj) == 0);
    c149_obj[0x150] = 5;
    assert(check_149_150(c149_obj) == 1);

    static uint8_t gb121_obj[0x124];
    gb121_obj[0x121] = 0xfe;
    assert(get_byte_121(gb121_obj) == -2);

    static uint32_t awcb_obj[4];
    awcb_obj[3] = 0x8000;
    assert(add_word_c_indexed_b(awcb_obj, 2) == 0x8010);

    static uint8_t gib5e8_obj[0x5ec];
    gib5e8_obj[0x5e8] = 1;
    *(uint32_t *)(gib5e8_obj + 4 + 0x5a8) = 0x999;
    assert(get_indexed_byte_5e8_word_5a8(gib5e8_obj) == 0x999);

    static uint32_t cpb8c_obj[2];
    static uint8_t cpb8c_sub[0x90];
    assert(check_pointed_byte_8c_bit0(cpb8c_obj) == 0);
    cpb8c_obj[0] = (uint32_t)(uintptr_t)cpb8c_sub;
    cpb8c_sub[0x8c] = 3;
    assert(check_pointed_byte_8c_bit0(cpb8c_obj) == 1);
    cpb8c_sub[0x8c] = 2;
    assert(check_pointed_byte_8c_bit0(cpb8c_obj) == 0);

    static uint32_t gn2c_obj[2];
    static uint8_t gn2c_mid[0x40];
    static uint32_t gn2c_tab[0x30 / 4];
    gn2c_obj[1] = (uint32_t)(uintptr_t)gn2c_mid;
    *(uint32_t *)(gn2c_mid + 0x3c) = (uint32_t)(uintptr_t)gn2c_tab;
    gn2c_tab[0x2c / 4] = 0;
    gn2c_tab[0] = 0x666;
    assert(get_nested_3c_2c_deref(gn2c_obj) == 0x666);

    static uint32_t gn1c_obj[2];
    static uint8_t gn1c_mid[0x40];
    static uint32_t gn1c_tab[0x20 / 4];
    gn1c_obj[1] = (uint32_t)(uintptr_t)gn1c_mid;
    *(uint32_t *)(gn1c_mid + 0x3c) = (uint32_t)(uintptr_t)gn1c_tab;
    gn1c_tab[0x1c / 4] = 0;
    gn1c_tab[0] = 0x777;
    assert(get_nested_3c_1c_deref(gn1c_obj) == 0x777);
}

void run_batch_a2_tests(void)
{
    static float rfm_val;
    rfm_val = 5.0f;
    raise_float_to_min(&rfm_val, 3.0f);
    assert(rfm_val == 5.0f);
    raise_float_to_min(&rfm_val, 9.0f);
    assert(rfm_val == 9.0f);

    static float lfm_val;
    lfm_val = 5.0f;
    lower_float_to_max(&lfm_val, 9.0f);
    assert(lfm_val == 5.0f);
    lower_float_to_max(&lfm_val, 3.0f);
    assert(lfm_val == 3.0f);

    static uint32_t thb_obj[2];
    thb_obj[0] = 0x80000000;
    thb_obj[1] = 0x80000000;
    assert(test_high_bit(thb_obj, 0) == 0x80000000);
    assert(test_high_bit(thb_obj, 31) == 0);
    assert(test_high_bit(thb_obj, 32) == 0x80000000);
    assert(test_high_bit(thb_obj, 63) == 0);

    noop_i();
    noop_j();
}

void run_batch_b2_tests(void)
{
    static uint32_t sw138_obj[0x13c / 4];
    store_word_138_indexed(sw138_obj, 0, 0x111);
    assert(sw138_obj[0x138 / 4] == 0x111);

    static uint32_t sw130_obj[0x134 / 4];
    store_word_130_indexed(sw130_obj, 0, 0x222);
    assert(sw130_obj[0x130 / 4] == 0x222);

    static const char fcf_str[8] = {'h', 'e', 'l', 'l', 'o', '\0', '\0', '\0'};
    assert(find_char_from(fcf_str, 'l') == (int32_t)(intptr_t)(fcf_str + 2));
    assert(find_char_from(fcf_str, 'z') == 0);
    assert(find_char_from(fcf_str, 'h') == (int32_t)(intptr_t)fcf_str);

    static uint32_t gph_obj[2];
    static uint16_t gph_val[4];
    gph_val[0] = 0xabcd;
    gph_obj[1] = (uint32_t)(uintptr_t)gph_val;
    assert(get_pointed_halfword_word(gph_obj) == 0xabcd);

    static uint8_t sta4_obj[0xb4];
    store_triple_a4_mark_b0(sta4_obj, 1, 2, 3);
    assert(*(uint32_t *)(sta4_obj + 0xa4) == 1);
    assert(*(uint32_t *)(sta4_obj + 0xa8) == 2);
    assert(*(uint32_t *)(sta4_obj + 0xac) == 3);
    assert(sta4_obj[0xb0] == 1);

    static uint32_t alt_obj[0x178 / 4];
    static uint32_t alt_node_a[1];
    static uint32_t alt_node_b[1];
    alt_obj[0x174 / 4] = 0x77;
    assert(append_list_tail_170(alt_obj, alt_node_a) == 0x77);
    assert(alt_obj[0x16c / 4] == (uint32_t)(uintptr_t)alt_node_a);
    assert(alt_obj[0x170 / 4] == (uint32_t)(uintptr_t)alt_node_a);
    assert(alt_node_a[0] == 0);
    append_list_tail_170(alt_obj, alt_node_b);
    assert(alt_obj[0x16c / 4] == (uint32_t)(uintptr_t)alt_node_a);
    assert(alt_node_a[0] == (uint32_t)(uintptr_t)alt_node_b);
    assert(alt_obj[0x170 / 4] == (uint32_t)(uintptr_t)alt_node_b);

    static uint8_t ce20_obj[0x60];
    assert(check_entry_20_empty((uint32_t *)ce20_obj, 0) == 1);
    *(uint32_t *)(ce20_obj + 4) = 1;
    assert(check_entry_20_empty((uint32_t *)ce20_obj, 0) == 1);
    ce20_obj[0x20] = 5;
    assert(check_entry_20_empty((uint32_t *)ce20_obj, 0) == 0);
    assert(check_entry_20_empty((uint32_t *)ce20_obj, 1) == 1);

    static uint8_t cb14s_obj[0x18];
    cb14s_obj[0x14] = 0;
    assert(check_byte_14_in_set(cb14s_obj) == 1);
    cb14s_obj[0x14] = 9;
    assert(check_byte_14_in_set(cb14s_obj) == 1);
    cb14s_obj[0x14] = 3;
    assert(check_byte_14_in_set(cb14s_obj) == 0);
    assert(check_byte_14_is_b(cb14s_obj) == 0);
    cb14s_obj[0x14] = 0xb;
    assert(check_byte_14_is_b(cb14s_obj) == 1);
    assert(check_byte_14_in_set(cb14s_obj) == 0);

    static uint8_t sb150b_obj[0x1510];
    set_byte_150b_if_1508_is_2(sb150b_obj);
    assert(sb150b_obj[0x150b] == 0);
    sb150b_obj[0x1508] = 2;
    set_byte_150b_if_1508_is_2(sb150b_obj);
    assert(sb150b_obj[0x150b] == 1);

    static uint8_t sb150a_obj[0x1510];
    set_byte_150a_if_1508_is_2(sb150a_obj);
    assert(sb150a_obj[0x150a] == 0);
    sb150a_obj[0x1508] = 2;
    set_byte_150a_if_1508_is_2(sb150a_obj);
    assert(sb150a_obj[0x150a] == 1);

    static uint8_t sh4b_obj[8];
    set_halfword_4_bit(sh4b_obj, 3, 1);
    assert(*(uint16_t *)(sh4b_obj + 4) == 8);
    set_halfword_4_bit(sh4b_obj, 0, 1);
    assert(*(uint16_t *)(sh4b_obj + 4) == 9);
    set_halfword_4_bit(sh4b_obj, 3, 0);
    assert(*(uint16_t *)(sh4b_obj + 4) == 1);

    static uint32_t gne8_obj[3];
    static uint8_t gne8_sub[0xec];
    assert(get_nested_byte_e8_high(gne8_obj) == 0);
    gne8_obj[2] = (uint32_t)(uintptr_t)gne8_sub;
    gne8_sub[0xe8] = 0x10;
    assert(get_nested_byte_e8_high(gne8_obj) == 1);
    gne8_sub[0xe8] = 0x0f;
    assert(get_nested_byte_e8_high(gne8_obj) == 0);

    static uint8_t ss2w10_obj[0x14];
    assert(set_state_2_if_word_10_high(ss2w10_obj) == 1);
    assert(*(uint16_t *)(ss2w10_obj + 0xc) == 0);
    *(int32_t *)(ss2w10_obj + 0x10) = 0x43160000;
    assert(set_state_2_if_word_10_high(ss2w10_obj) == 1);
    assert(*(uint16_t *)(ss2w10_obj + 0xc) == 2);

    static uint32_t mw8c_obj[4];
    mw8c_obj[2] = 0x55;
    move_word_8_to_c(mw8c_obj);
    assert(mw8c_obj[2] == 0 && mw8c_obj[3] == 0x55);

    static uint8_t cb1h2_obj[0x10];
    static uint8_t cb1h2_src[0x10];
    *(uint32_t *)(cb1h2_obj + 4) = (uint32_t)(uintptr_t)cb1h2_src;
    cb1h2_src[1] = 0x42;
    *(uint16_t *)(cb1h2_src + 2) = 0x1234;
    assert(copy_byte_1_halfword_2(cb1h2_obj) == 1);
    assert(cb1h2_obj[10] == 0x42);
    assert(*(uint16_t *)(cb1h2_obj + 0xe) == 0x1234);

    static uint8_t ctfp_obj[0x18];
    static uint8_t ctfp_src[0x10];
    *(uint32_t *)(ctfp_obj + 4) = (uint32_t)(uintptr_t)ctfp_src;
    ctfp_src[1] = 0x55;
    *(uint16_t *)(ctfp_src + 2) = 0x5678;
    *(uint32_t *)(ctfp_src + 0xc) = 0x999;
    assert(copy_triple_from_pointed(ctfp_obj) == 1);
    assert(ctfp_obj[10] == 0x55);
    assert(*(uint16_t *)(ctfp_obj + 0xe) == 0x5678);
    assert(*(uint32_t *)(ctfp_obj + 0x14) == 0x999);

    static uint32_t cpp_obj[4];
    static uint32_t cpp_sub[0x274 / 4];
    cpp_obj[3] = (uint32_t)(uintptr_t)cpp_sub;
    cpp_sub[0x26c / 4] = 1;
    cpp_sub[0x270 / 4] = 2;
    clear_pointed_pair_26c(cpp_obj);
    assert(cpp_sub[0x26c / 4] == 0 && cpp_sub[0x270 / 4] == 0);

    static uint32_t cw4o_obj[2];
    cw4o_obj[1] = 9;
    clear_word_4_only(cw4o_obj);
    assert(cw4o_obj[1] == 0);

    static uint32_t sbe_obj[0xec / 4];
    static uint32_t sbe_child[0xec / 4];
    static uint32_t sbe_list[1];
    set_byte_ea_recursive(sbe_obj, 0x42, 0);
    assert(((uint8_t *)sbe_obj)[0xea] == 0x42);
    sbe_list[0] = (uint32_t)(uintptr_t)sbe_child;
    sbe_obj[6] = 1;
    sbe_obj[8] = (uint32_t)(uintptr_t)sbe_list;
    set_byte_ea_recursive(sbe_obj, 0x55, 1);
    assert(((uint8_t *)sbe_obj)[0xea] == 0x55);
    assert(((uint8_t *)sbe_child)[0xea] == 0x55);
}
