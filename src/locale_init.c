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

uint32_t *get_locale_block(uint32_t *address)
{
    return address;
}

const char *find_active_locale(const char *requested, LocaleEntry *table)
{
    LocaleEntry *entry = table;
    if (requested != NULL) {
        for (;;) {
            if (entry->next_offset == 0) {
                return NULL;
            }
            entry = (LocaleEntry *)(entry->next_offset + (uintptr_t)entry);
            if (strcmp(requested, entry->name) == 0) {
                break;
            }
        }
        if (entry->next_offset == 0) {
            return NULL;
        }
    }
    return entry->name;
}

const void *resolve_locale_table(const char *name, const void *default_table,
    const char *default_name)
{
    if (name != NULL && *name != '\0' && strcmp(name, default_name) != 0) {
        return NULL;
    }
    return default_table;
}

void initialize_locale(LocaleBlock *block, const char *requested,
    LocaleEntry *locale_table, const void *default_table, const char *default_name)
{
    block->active_locale_name = find_active_locale(requested, locale_table);
    block->locale_table = resolve_locale_table(requested, default_table, default_name);
}
