#!/usr/bin/env python3
"""Extract a decrypted Luigi's Mansion 3DS dump into extracted/."""
import argparse
import hashlib
import shutil
import subprocess
import sys
from pathlib import Path

from exheader import parse

ROOT = Path(__file__).resolve().parent.parent
OUT = ROOT / "extracted"
PAGE_SIZE = 0x1000


def run(*args):
    print("+", " ".join(str(a) for a in args))
    subprocess.run([str(a) for a in args], check=True)


def need(tool):
    if shutil.which(tool) is None:
        sys.exit(f"error: '{tool}' not found in PATH (see README.md)")


def extract_ctrtool(rom: Path, seeddb: Path | None, seed: str | None):
    need("ctrtool")
    args = ["ctrtool"]
    if seeddb:
        args.append(f"--seeddb={seeddb}")
    if seed:
        args.append(f"--seed={seed}")
    if rom.suffix.lower() in (".3ds", ".cci"):
        args.append("--ncch=0")
    args.extend((
        f"--exheader={OUT / 'exheader.bin'}",
        f"--exefsdir={OUT / 'exefs'}",
        f"--romfsdir={OUT / 'romfs'}",
        rom,
    ))
    run(*args)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("rom", nargs="?", help="path to decrypted .3ds/.cci/.cxi/.cia (default: first file in baserom/)")
    ap.add_argument("--seeddb", type=Path, help="path to a locally dumped 3DS seed database (CIA only)")
    ap.add_argument("--seed", help="title seed in hexadecimal (CIA only)")
    args = ap.parse_args()

    if args.rom:
        rom = Path(args.rom)
    else:
        roms = [p for p in (ROOT / "baserom").iterdir() if p.suffix.lower() in (".3ds", ".cci", ".cxi", ".cia")]
        if not roms:
            sys.exit("error: place your decrypted dump in baserom/")
        rom = roms[0]

    hash_path = ROOT / "config" / "code.bin.sha1"
    hash_path.unlink(missing_ok=True)
    OUT.mkdir(exist_ok=True)
    extract_ctrtool(rom, args.seeddb, args.seed)

    code = OUT / "exefs" / "code.bin"
    if not code.exists():
        sys.exit("error: code.bin not produced - is the dump decrypted?")
    hdr = parse(OUT / "exheader.bin")
    expected_size = sum(s.pages * PAGE_SIZE for s in (hdr.text, hdr.rodata, hdr.data))
    actual_size = code.stat().st_size
    if actual_size != expected_size:
        sys.exit(
            f"error: code.bin is {actual_size:#x} bytes, expected {expected_size:#x} "
            "from the exheader; the CIA may need seed-based decryption. "
            "Supply --seeddb or --seed, or extract a decrypted dump."
        )
    sha1 = hashlib.sha1(code.read_bytes()).hexdigest()
    hash_path.write_text(sha1 + "\n")
    print(f"code.bin sha1: {sha1}")


if __name__ == "__main__":
    main()
