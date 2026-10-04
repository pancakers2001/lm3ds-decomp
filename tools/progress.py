#!/usr/bin/env python3
"""Regenerate docs/progress.svg from the current symbol coverage."""

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SYMBOLS = ROOT / "config" / "symbols.txt"
FUNCTIONS_CSV = ROOT / "build" / "ghidra" / "exports" / "functions.csv"
SVG = ROOT / "docs" / "progress.svg"


def main() -> None:
    named = 0
    with SYMBOLS.open() as f:
        for line in f:
            if re.match(r"^[a-z_][a-z0-9_]* = 0x", line):
                named += 1

    total = 0
    with FUNCTIONS_CSV.open() as f:
        total = max(0, sum(1 for _ in f) - 1)

    if total == 0:
        raise SystemExit("no functions.csv - run make analyze first")

    percent = named * 100.0 / total
    width = 600
    fill = max(1, round(width * percent / 100.0))

    SVG.write_text(
        '<svg xmlns="http://www.w3.org/2000/svg" width="{w}" height="40" '
        'role="img" aria-label="Progress: {p:.1f}%">\n'
        '  <title>Progress: {p:.1f}%</title>\n'
        '  <rect x="0" y="0" width="{w}" height="40" rx="4" fill="#30363d"/>\n'
        '  <rect x="0" y="0" width="{f}" height="40" rx="4" fill="#2ea043"/>\n'
        '  <rect x="{fx}" y="0" width="4" height="40" fill="#30363d"/>\n'
        '  <text x="{cx}" y="26" font-family="Verdana,DejaVu Sans,sans-serif" '
        'font-size="16" fill="#e6edf3" text-anchor="middle">'
        '{n} / {t} functions ported ({p:.1f}%)</text>\n'
        "</svg>\n".format(
            w=width, f=fill, fx=max(0, fill - 4), cx=width // 2,
            n=named, t=total, p=percent,
        )
    )
    print(f"{named}/{total} = {percent:.2f}% -> {SVG.relative_to(ROOT)}")


if __name__ == "__main__":
    main()
