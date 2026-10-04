#include <assert.h>
#include <stdint.h>
#include <string.h>

typedef struct LocaleEntry LocaleEntry;
struct LocaleEntry {
    uint32_t next_offset;
    const char *name;
};

typedef struct {
    uint32_t unused;
    const char *active_locale_name;
    uint32_t field_8;
    const void *locale_table;
} LocaleBlock;

const char *find_active_locale(const char *requested, LocaleEntry *table);
const void *resolve_locale_table(const char *name, const void *default_table,
    const char *default_name);
void initialize_locale(LocaleBlock *block, const char *requested,
    LocaleEntry *locale_table, const void *default_table, const char *default_name);

static LocaleEntry locale_entries[3];
static int fake_table_storage;

void run_locale_tests(void)
{
    locale_entries[0].next_offset = (uint32_t)((uintptr_t)&locale_entries[1] - (uintptr_t)&locale_entries[0]);
    locale_entries[0].name = "en";
    locale_entries[1].next_offset = (uint32_t)((uintptr_t)&locale_entries[2] - (uintptr_t)&locale_entries[1]);
    locale_entries[1].name = "C";
    locale_entries[2].next_offset = 0;
    locale_entries[2].name = "fr";

    const char *found = find_active_locale(NULL, locale_entries);
    assert(found != NULL && strcmp(found, "en") == 0);

    found = find_active_locale("C", locale_entries);
    assert(found != NULL && strcmp(found, "C") == 0);

    found = find_active_locale("en", locale_entries);
    assert(found == NULL);

    found = find_active_locale("fr", locale_entries);
    assert(found == NULL);

    found = find_active_locale("unknown", locale_entries);
    assert(found == NULL);

    const void *resolved = resolve_locale_table("C", &fake_table_storage, "C");
    assert(resolved == &fake_table_storage);

    resolved = resolve_locale_table("fr", &fake_table_storage, "C");
    assert(resolved == NULL);

    resolved = resolve_locale_table("", &fake_table_storage, "C");
    assert(resolved == &fake_table_storage);

    resolved = resolve_locale_table(NULL, &fake_table_storage, "C");
    assert(resolved == &fake_table_storage);

    LocaleBlock block;
    memset(&block, 0, sizeof(block));
    initialize_locale(&block, "C", locale_entries, &fake_table_storage, "C");
    assert(block.active_locale_name != NULL && strcmp(block.active_locale_name, "C") == 0);
    assert(block.locale_table == &fake_table_storage);
}
