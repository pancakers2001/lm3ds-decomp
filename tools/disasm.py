#!/usr/bin/env python3
"""Produce a reference ARM disassembly of code.bin (not reassemblable)."""
import struct
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs

from exheader import parse

ROOT = Path(__file__).resolve().parent.parent
EXT = ROOT / "extracted"
ASM = ROOT / "asm"
PAGE_SIZE = 0x1000


def is_func_start(insn) -> bool:
    return insn.mnemonic.startswith(("push", "stmdb")) and "lr" in insn.op_str


def main():
    hdr = parse(EXT / "exheader.bin")
    code = (EXT / "exefs" / "code.bin").read_bytes()
    expected_size = sum(s.pages * PAGE_SIZE for s in (hdr.text, hdr.rodata, hdr.data))
    if len(code) != expected_size:
        raise SystemExit(
            f"error: code.bin is {len(code):#x} bytes, expected {expected_size:#x} "
            "from the exheader; run make extract with a decrypted dump or the "
            "required CIA seed."
        )
    ASM.mkdir(exist_ok=True)

    text = hdr.text
    off = hdr.file_offset(text)
    blob = code[off:off + text.size]

    md = Cs(CS_ARCH_ARM, CS_MODE_ARM)
    md.skipdata = True
    funcs = []
    with open(ASM / "text.s", "w") as f:
        f.write(f"@ .text  {text.addr:08X}-{text.addr + text.size:08X}\n")
        for insn in md.disasm(blob, text.addr):
            if is_func_start(insn):
                funcs.append(insn.address)
                f.write(f"\nfunc_{insn.address:08X}:\n")
            f.write(f"  /* {insn.address:08X} {insn.bytes.hex().upper():8} */ {insn.mnemonic} {insn.op_str}\n")

    for seg in (hdr.rodata, hdr.data):
        o = hdr.file_offset(seg)
        (ASM / f"{seg.name.lstrip('.')}.bin").write_bytes(code[o:o + seg.size])

    with open(ASM / "functions.txt", "w") as f:
        for a in funcs:
            f.write(f"func_{a:08X} = 0x{a:08X};\n")

    print(f"{len(funcs)} candidate functions -> asm/")


if __name__ == "__main__":
    main()
