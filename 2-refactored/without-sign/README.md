# Arbitrary Precision Calculator — Without-Sign Engine

This is the unsigned variant of my multi-precision arithmetic engine. The operands are always non-negative whole numbers, and I model each one as a doubly linked list of decimal digits — most significant digit at the head, least significant at the tail. Only subtraction can produce a value below zero, and when it does I print a single leading `-`.

It is a command-line calculator that adds, subtracts, multiplies, and divides non-negative integers of arbitrary length.

## Building

```sh
make            # build the ./apc binary
make debug      # build with symbols and no optimisation, for gdb/valgrind
make memcheck   # run a valgrind leak check over a sample operation
make clean      # remove all build artifacts
```

## Using it

Three arguments: a number, an operator, and a number. I use `x` for multiplication so the shell does not expand a `*`.

```sh
./apc 12345678901234567890 + 98765
./apc 100 - 99999          # Subtraction Result = -99899
./apc 999999 x 999999
./apc 1000000 / 7          # Division Result = 142857
```

Signs on the input are rejected as invalid, which is what separates this build from the with-sign engine.

## What I fixed relative to the original without-sign code

- **Division no longer hangs.** The original looped forever on any division with a remainder (for example `10 / 3`). I rewrote division as long division, where each quotient digit costs at most nine subtractions, so it always terminates and runs in polynomial time.
- **The quotient is now a real big number.** The original stored the quotient in a single `int`; mine builds it as a full digit list, so it stays arbitrary precision.
- **No memory leaks.** The original never freed its lists. I free all three lists in `main.c` on every path, and every transient list inside multiplication and division is freed the moment it is replaced. Verified under Valgrind: zero bytes in use at exit, zero errors.
- **No crash on bad input.** I check the argument count and reject malformed operands instead of dereferencing past the end of `argv`.
- **Full leading-zero stripping.** `delete_zero` now removes every redundant leading zero (so `007` becomes `7`) while always keeping a single `0` for the number zero itself.

## Repository layout

| File | What I put in it |
| --- | --- |
| `bignum.h` | The node definition, status macros, and every public prototype. |
| `bignum.c` | The whole engine: list primitives, magnitude routines, and the four operations. |
| `main.c` | The command-line driver: argument validation, dispatch, printing, and cleanup. |
| `Makefile` | The GCC build, including debug and valgrind targets. |
| `../../docs/PROJECT_FILE_GUIDE.md` | How the whole repository is organised (covers every version). |
