# Arbitrary Precision Calculator — Multi-Precision Arithmetic Engine

I built this in C to do exact arithmetic on integers far larger than any native type can hold. Where a `long long` gives out around 19 digits, this engine keeps going — I have run it on hundreds of digits with no loss of precision — because I represent every number as a doubly linked list of decimal digits and carry a sign alongside it.

It is a command-line calculator that adds, subtracts, multiplies, and divides signed whole numbers of arbitrary length.

## Why I wrote it this way

Each number is a doubly linked list: one decimal digit per node, most significant digit at the head, least significant at the tail. The `prev` pointers let me walk a number backward when I propagate carries and borrows; the `next` pointers let me walk it forward when I print or run long division. The sign is a single character kept completely separate from the digits, so my core digit logic never has to think about signs and my sign logic never has to think about individual digits. That separation is what keeps the engine clean.

## Building

I use GCC and a small Makefile.

```sh
make            # build the ./apc binary
make debug      # build with symbols and no optimisation, for gdb/valgrind
make memcheck   # run a valgrind leak check over a sample operation
make clean      # remove all build artifacts
```

## Using it

The calculator takes three arguments: a number, an operator, and a number. I use `x` for multiplication so the shell does not expand a `*`.

```sh
./apc 12345678901234567890 + 98765
./apc -4096 - 12
./apc 999999 x 999999
./apc 1000000000000 / 13
```

Each operand may carry an optional leading `+` or `-`:

```sh
./apc -50 + 50          # Addition Result = 0
./apc -12 x 12          # Multiplication Result = -144
./apc -144 / -12        # Division Result = 12
```

## What it handles

I cover all four sign combinations for every operator, carry growth (999 + 1 = 1000), borrow with leading-zero collapse (1000 − 1 = 999), exact and truncating division (144 / 12 and 10 / 3), zero results normalised so they never print as `-0`, division by zero rejected with an error, and invalid or malformed input rejected cleanly. The division uses long division, so a single quotient digit costs at most nine subtractions and the whole operation stays polynomial rather than the exponential cost of naive repeated subtraction.

## Memory

Every list I allocate, I free — both operands and the result in `main.c`, and every transient list inside multiplication and division the moment it is replaced. I verified this under Valgrind across all four operations and the failure paths: zero bytes in use at exit, zero errors.

## Repository layout

| File | What I put in it |
| --- | --- |
| `bignum.h` | The node definition, status macros, and every public prototype — the engine's contract. |
| `bignum.c` | The whole engine: list primitives, sign-blind magnitude routines, and the four signed operations. |
| `main.c` | The command-line driver: argument validation, dispatch, printing, and cleanup. |
| `Makefile` | The GCC build, including debug and valgrind targets. |
| `../../docs/PROJECT_FILE_GUIDE.md` | How the whole repository is organised (covers every version). |
