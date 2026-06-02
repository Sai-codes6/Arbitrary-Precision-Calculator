# Arbitrary Precision Calculator — A Multi-Precision Integer Arithmetic Engine in C

Exact arithmetic in C on integers far larger than any native type can hold. Where a `long long` gives out around 19 digits, this keeps going for hundreds of digits, because every number is modelled as a doubly linked list of decimal digits with carries and borrows propagated by hand.

This repository keeps every version of the project side by side so the progression is visible — from my first drafts to the audited, leak-free engine.

## What lives where

### `1-original/`

My original drafts, exactly as I first wrote them.

- **`with-sign/`** — the version that accepts signed operands (`+`/`-` on either number). It works on many cases but has known bugs: input parsing corrupts a number when only one operand carries a sign, magnitude comparison reads the sign character by mistake, and division hangs on any remainder.
- **`without-sign/`** — the version that accepts only non-negative operands. Addition, subtraction, multiplication, and exact division are correct, but division hangs on any division with a remainder, the lists are never freed, and running it with no arguments crashes.

These folders are split across several files (`apc.h`, `main.c`, `addition.c`, `subtraction.c`, `multiplication.c`, `division.c`, `functions.c`).

### `docs/`

The repository-wide **Project File Guide** — how every folder and file is organised across all four versions, and what changed between the original drafts and the refactor.

### `2-refactored/`

The audited and corrected engine, consolidated into a clean three-file layout (`bignum.h`, `bignum.c`, `main.c`) with a Makefile, a `.gitignore`, a README, and docs. Each variant passes a full regression battery and reports zero leaks under Valgrind.

- **`with-sign/`** — the signed engine, with every original bug fixed: independent per-operand parsing, list-based magnitude comparison, long division that always terminates, a true big-number quotient, and complete cleanup of all memory.
- **`without-sign/`** — the unsigned engine, rebuilt to the same standard: long division, no leaks, no crash on bad input, and full leading-zero stripping.

Every refactored variant builds with `make` and runs as `./apc <number> <operator> <number>`, using `x` for multiplication.

## How I represent a number

One decimal digit per node in a doubly linked list, most significant digit at the head and least significant at the tail. The `prev` pointers let me walk backward when I propagate carries and borrows; the `next` pointers let me walk forward when I print or run long division. In the signed engine the sign is a single character kept entirely separate from the digits; in the unsigned engine only subtraction can go negative, and it reports that through a flag. Keeping the sign apart from the magnitude is what makes the digit logic clean.

## Quick start (refactored engine)

```sh
cd 2-refactored/with-sign      # or 2-refactored/without-sign
make
./apc 12345678901234567890 x 98765
make memcheck                  # optional: valgrind leak check
make clean
```
