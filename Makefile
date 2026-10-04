PYTHON ?= python3
CC ?= cc
GHIDRA_HOME ?=
GHIDRA_PROJECT_DIR := $(abspath build/ghidra)
GHIDRA_PROJECT_NAME ?= LM3DS
GHIDRA_FUNCTIONS ?= 0x00100024
GHIDRA_EXPORT_DIR := $(abspath build/ghidra/exports)

.PHONY: setup extract info disasm analyze progress lint test-decomp test-decomp-sanitize test-game clean

setup:
	$(PYTHON) -m venv .venv && .venv/bin/pip install -r requirements.txt

extract:
	$(PYTHON) tools/extract_rom.py $(if $(ROM),"$(ROM)") $(ARGS)

info:
	$(PYTHON) tools/exheader.py extracted/exheader.bin

disasm:
	.venv/bin/python tools/disasm.py

analyze:
	@test -x "$(GHIDRA_HOME)/support/analyzeHeadless" || { echo "error: set GHIDRA_HOME to your Ghidra installation"; exit 1; }
	@mkdir -p "$(GHIDRA_PROJECT_DIR)"
	@if test -f "$(GHIDRA_PROJECT_DIR)/$(GHIDRA_PROJECT_NAME).gpr"; then \
		"$(GHIDRA_HOME)/support/analyzeHeadless" "$(GHIDRA_PROJECT_DIR)" "$(GHIDRA_PROJECT_NAME)" -process code.bin -noanalysis -scriptPath "$(abspath tools/ghidra)" -postScript ExportFunctionAnalysis.java "$(GHIDRA_EXPORT_DIR)" "$(abspath config/symbols.txt)" $(GHIDRA_FUNCTIONS); \
	else \
		"$(GHIDRA_HOME)/support/analyzeHeadless" "$(GHIDRA_PROJECT_DIR)" "$(GHIDRA_PROJECT_NAME)" -import extracted/exefs/code.bin -processor ARM:LE:32:v6 -loader BinaryLoader -loader-baseAddr 0x00100000 -scriptPath "$(abspath tools/ghidra)" -postScript ExportFunctionAnalysis.java "$(GHIDRA_EXPORT_DIR)" "$(abspath config/symbols.txt)" $(GHIDRA_FUNCTIONS); \
	fi

progress:
	$(PYTHON) tools/progress.py

lint:
	$(PYTHON) tools/lint_symbols.py

test-decomp:
	@mkdir -p build
	$(CC) -std=c11 -Wall -Wextra -Werror -no-pie -Iinclude tests/format_parser_test.c tests/ctors_test.c tests/locale_test.c tests/runtime_test.c tests/system_state_test.c tests/sleep_state_test.c tests/stack_setup_test.c tests/process_state_test.c tests/sleep_wait_test.c tests/runtime_wrapper_test.c src/format_arithmetic.c src/format_parse.c src/format_output.c src/format_specifier.c src/format_wrapper.c src/ctors.c src/locale_init.c src/runtime_init.c src/system_state.c src/sleep_state.c src/stack_setup.c src/process_state.c src/sleep_wait.c src/runtime_wrapper.c src/system_interface.c -o build/format_parser_test
	build/format_parser_test

test-decomp-sanitize:
	@mkdir -p build
	$(CC) -std=c11 -Wall -Wextra -Werror -no-pie -fsanitize=address,undefined -fno-omit-frame-pointer -Iinclude tests/format_parser_test.c tests/ctors_test.c tests/locale_test.c tests/runtime_test.c tests/system_state_test.c tests/sleep_state_test.c tests/stack_setup_test.c tests/process_state_test.c tests/sleep_wait_test.c tests/runtime_wrapper_test.c src/format_arithmetic.c src/format_parse.c src/format_output.c src/format_specifier.c src/format_wrapper.c src/ctors.c src/locale_init.c src/runtime_init.c src/system_state.c src/sleep_state.c src/stack_setup.c src/process_state.c src/sleep_wait.c src/runtime_wrapper.c src/system_interface.c -o build/format_parser_test_sanitize
	build/format_parser_test_sanitize

test-game:
	@mkdir -p build
	$(CC) -std=c11 -Wall -Wextra -Werror -no-pie -Iinclude tests/game_state_test.c src/system_interface.c src/game_state.c src/main_entry.c src/system_state.c src/stack_setup.c src/sleep_state.c src/game_object.c -o build/game_test
	build/game_test

clean:
	rm -rf build asm
