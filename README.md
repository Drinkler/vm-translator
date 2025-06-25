# VMTranslator

A modern C implementation of the Hack **Virtual‑Machine → Assembly** translator (chapters 7–8 of the *Nand2Tetris* course).

---

## Features

* **Complete VM command set** – arithmetic/logic, memory‐access, branching, functions.
* Written in **portable C2x**, no external dependencies.
* Two build flavours via GNU Make:

  * **Debug** (default): assertions & debug symbols (`-O0 -g`).
  * **Release**: fully optimised with `-O3`.
* Clean separation of source (`src/`) and public headers (`include/`).

---

## Directory layout

```text
.
├── include/        # public headers
├── src/            # .c implementation files
├── build/          # auto‑generated objects
│   ├── debug/
│   └── release/
├── bin/            # final executables
│   ├── debug/
│   └── release/
└── Makefile
```

---

## Building

```bash
# Debug build (default)
make            # or: make BUILD=debug

# Release build
make release    # or: make BUILD=release

# Wipe all artefacts
make clean
```

---

## Usage

```bash
# Translate a single VM file → Hack ASM
./bin/release/VMTranslator MyProgram.vm

# Translate every .vm file in a directory
./bin/release/VMTranslator ./StackTest
```

When the input is a directory, the translator emits `DirectoryName.asm` inside the same folder; for a single file it writes `BaseName.asm` alongside the source file.

---
