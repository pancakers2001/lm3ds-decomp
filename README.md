# Luigi's Mansion (3DS) Decompilation

Work-in-progress decompilation of *Luigi's Mansion* (Nintendo 3DS, 2018, Grezzo).

This repository contains **no game assets or code**. You must supply your own legally dumped, **decrypted** copy.

## Requirements

- Python 3.10+
- [ctrtool](https://github.com/3DSGuy/Project_CTR) in `PATH` (supports `.cia`, `.3ds`, `.cci`, and `.cxi`)
- Recommended for analysis: Ghidra with the ARM:LE:32:v6 language

## Usage

```sh
make setup      # create .venv and install Python deps
cp /path/to/dump.3ds baserom/
make extract    # -> extracted/{exheader.bin,exefs/code.bin,romfs/}
make info       # print code segment layout
make disasm     # -> asm/text.s, asm/functions.txt
GHIDRA_HOME=/path/to/ghidra make analyze  # -> build/ghidra/exports
make test-decomp  # compile and run recovered formatter tests
make test-decomp-sanitize  # run tests with address/undefined-behavior sanitizers
```

`make analyze` runs Ghidra headlessly with ARM:LE:32:v6, exports its function
inventory, and decompiles the first discovered startup function at `0x00100024`.
Set `GHIDRA_FUNCTIONS="0x00100024 0x00100380"` to export additional addresses.
The Ghidra project and generated pseudocode stay under ignored `build/`.

CIA files that use seed-based encryption require a seed from your own console.
Pass a locally obtained seed database or the title seed to extraction:

```sh
make extract ROM=/path/to/dump.cia ARGS="--seeddb /path/to/seeddb.bin"
# or run the script directly with: --seed <hex-seed>
```

The extractor checks the decompressed code size against the exheader. A failed
check means the dump is still encrypted or extraction was incomplete; do not
use any previous assembly output as a valid disassembly.

The recovered formatter is now complete end to end: the narrow and wide entry
wrappers (`format_string_to_sink`, `format_wstring_to_sink`), the format-string
read callbacks, and the buffer-append writer are all decompiled in `src/`.
Conversions cover integer, pointer, string, character, `%n`, wide ASCII/direct
UTF-16, and hexadecimal floating point. Decimal `%f`, `%e`, and `%g` currently
use standard double arithmetic; the custom power-of-ten scaling table and dtoa
driver are identified in `config/symbols.txt` but their encoding requires
further analysis. Run `make test-decomp` for the regression suite, which
includes end-to-end wrapper tests.

Startup is partially decompiled too: `initialize_bss`, the two C++ static
constructor runners — `run_relocations_and_ctors` (relocation-relative table at
`0x48c010..0x48c3ec`, 244 entries) and `run_static_ctors` (absolute table,
empty in this build) — the locale init chain (`get_locale_block`,
`find_active_locale`, `resolve_locale_table`, `initialize_locale`), and the
runtime flag store (`store_runtime_flag`), and the system-state helpers used
by the main entry (`get_heap_info_field`, `get_system_service_object`, the
`claim_once` once-guard, and the `initialize_lookup_table` lazy initializer),
and the sleep-wait state initializer (`initialize_list_head`,
`initialize_sleep_wait_state`), the stack-setup helpers
(`get_heap_info_field_deep`, `compute_stack_size`, `initialize_stack_region`),
and the process-state getters (`get_process_flags`, `get_service_state`).
The sleep-mode wait loop (`wait_for_sleep_mode`) is also ported with the
state-check logic; its SVC wait is stubbed for now. The runtime-init wrapper
(`initialize_runtime` at `0x1040fc`) is ported with the system calls stubbed.
The formatter also includes the 16-bit buffer writer (`write_u16_to_buffer`),
the null-terminating buffer formatter (`format_to_buffer` at `0x1006c0`),
the bounded string copy (`copy_string_bounded` at `0x100fe8`), the
last-character search (`find_last_character` at `0x101a3c`), the character
classification helper (`is_character_class` at `0x101a54`), and the wide
character search (`find_wide_character` at `0x102cf4`). The game object layer
includes the object state getter (`get_game_object_state`), the flag bit setter
(`set_object_flag_bits`), the flag clearer (`clear_object_flag`), the handle
getters (`get_object_handle`, `get_object_state_handle`), the bit clearer
(`clear_object_bit`), the entry getter (`get_object_entry`), the entry finder
(`find_object_entry`), the state reset (`reset_object_state`), and the state
initializer (`initialize_object_state`). The game logic layer includes the
state initializer (`initialize_game_state`), the flag clearer (`clear_game_flag`),
the flag setter (`set_game_flag`), the bounds checker (`check_game_bounds`),
the mode validator (`validate_game_mode`), the build tag getters
(`get_game_version_tag`, `get_game_build_tag`), the entry initializers
(`initialize_game_entry`, `initialize_name_entry`, `initialize_command_entry`),
and the counter clearer (`clear_object_counters`). The runtime layer includes
the recursive mutex pair (`recursive_mutex_lock`, `recursive_mutex_unlock`),
the tick getter (`get_system_tick`), the fill primitive (`rt_memset`), and the
intrusive linked-list primitives (`initialize_linked_list`, `push_list_front`,
`pop_list_front`). The remaining startup call is the main game entry at
`0x104580`, which orchestrates game object creation and needs the object model
mapped.

## Layout

| Path        | Contents                                   |
|-------------|--------------------------------------------|
| `baserom/`  | your dump (git-ignored)                    |
| `extracted/`| extracted ExeFS/RomFS (git-ignored)        |
| `asm/`      | generated reference disassembly            |
| `config/`   | hashes, symbol maps, split definitions     |
| `src/`      | decompiled C/C++                           |
| `include/`  | headers                                    |
| `tools/`    | helper scripts                             |

## Notes

The retail binary was likely built with ARM's RVCT/armcc; a byte-matching build requires that toolchain, which is not included.
