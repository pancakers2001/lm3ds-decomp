#!/usr/bin/env python3
"""Lint config/symbols.txt for consistency issues.

Checks:
  - no duplicate addresses (two names for one function)
  - no duplicate names (one name for two functions)
  - every address is a real function start in functions.csv
"""
import csv
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SYMBOLS = ROOT / "config" / "symbols.txt"
FUNCTIONS_CSV = ROOT / "build" / "ghidra" / "exports" / "functions.csv"

SYMBOL_RE = re.compile(r"^([a-z_][a-z0-9_]*) = 0x([0-9A-Fa-f]{8});$")


def main() -> int:
    entries = defaultdict(list)
    names = defaultdict(list)

    with SYMBOLS.open() as f:
        for lineno, line in enumerate(f, 1):
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            m = SYMBOL_RE.match(line)
            if not m:
                print(f"symbols.txt:{lineno}: malformed line: {line!r}")
                continue
            name, addr = m.group(1), m.group(2).lower()
            entries[addr].append((name, lineno))
            names[name].append((addr, lineno))

    errors = 0

    for addr, lst in sorted(entries.items()):
        if len(lst) > 1:
            detail = ", ".join(f"{n} (line {i})" for n, i in lst)
            print(f"ERROR: duplicate address 0x{addr}: {detail}")
            errors += 1

    for name, lst in sorted(names.items()):
        if len(lst) > 1:
            detail = ", ".join(f"0x{a} (line {i})" for a, i in lst)
            print(f"ERROR: duplicate name {name}: {detail}")
            errors += 1

    if FUNCTIONS_CSV.exists():
        with FUNCTIONS_CSV.open() as f:
            valid = {r["address"].lower() for r in csv.DictReader(f)}
        for addr, lst in sorted(entries.items()):
            if addr not in valid:
                for name, lineno in lst:
                    print(f"ERROR: {name} = 0x{addr} (line {lineno}) is not a function start")
                    errors += 1
    else:
        print(f"NOTE: {FUNCTIONS_CSV} not found, skipping function-start check")

    total = len(entries)
    if errors:
        print(f"\n{errors} error(s) in {total} symbols")
        return 1
    print(f"OK: {total} symbols, no duplicates or invalid addresses")
    return 0


if __name__ == "__main__":
    sys.exit(main())
