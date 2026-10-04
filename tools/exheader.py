#!/usr/bin/env python3
"""Parse the NCCH extended header to get code segment layout."""
import struct
import sys
from dataclasses import dataclass
from pathlib import Path

PAGE = 0x1000


@dataclass
class Segment:
    name: str
    addr: int
    pages: int
    size: int


@dataclass
class ExHeader:
    title: str
    title_id: int
    text: Segment
    rodata: Segment
    data: Segment
    bss_size: int
    stack_size: int

    def file_offset(self, seg: Segment) -> int:
        """Offset of a segment inside the decompressed code.bin."""
        off = 0
        for s in (self.text, self.rodata, self.data):
            if s is seg:
                return off
            off += s.pages * PAGE
        raise ValueError(seg.name)


def parse(path: Path) -> ExHeader:
    b = path.read_bytes()

    def seg(name, off):
        addr, pages, size = struct.unpack_from("<III", b, off)
        return Segment(name, addr, pages, size)

    return ExHeader(
        title=b[0:8].rstrip(b"\0").decode("ascii", "replace"),
        title_id=struct.unpack_from("<Q", b, 0x200)[0],
        text=seg(".text", 0x10),
        stack_size=struct.unpack_from("<I", b, 0x1C)[0],
        rodata=seg(".rodata", 0x20),
        data=seg(".data", 0x30),
        bss_size=struct.unpack_from("<I", b, 0x3C)[0],
    )


if __name__ == "__main__":
    p = Path(sys.argv[1] if len(sys.argv) > 1 else "extracted/exheader.bin")
    h = parse(p)
    print(f"title    {h.title}  ({h.title_id:016X})")
    for s in (h.text, h.rodata, h.data):
        print(f"{s.name:8} addr {s.addr:08X}  size {s.size:08X}  pages {s.pages:5}  file+{h.file_offset(s):08X}")
    print(f".bss     size {h.bss_size:08X}")
    print(f"stack    size {h.stack_size:08X}")
