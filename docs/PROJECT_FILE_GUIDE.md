# Project File Guide

This is how I organised the whole Arbitrary Precision Calculator repository, written in my own words so anyone opening it can see what each folder and file is for and why the project is laid out the way it is. The repository holds two generations of the same idea, with two variants in each, so I will walk through the structure top down.

## The big picture

```
arbitrary-precision-calculator/
├── README.md            -> the master overview of every version
├── .gitignore           -> build/compiler/IDE artifacts I keep out of git
├── docs/                -> this guide (how the project is organised)
├── 1-original/          -> my first drafts, exactly as I first wrote them
│   ├── with-sign/
│   └── without-sign/
└── 2-refactored/        -> the audited, corrected, leak-free engine
    ├── with-sign/
    └── without-sign/
```

I kept the originals in the repository on purpose. They show where the project started, and the refactored folders show where it ended up once I had audited every operation. Seeing both side by side is the clearest record of what I learned.

## The core idea every version shares

In all four variants a number is a doubly linked list of decimal digits — one digit per node, the most significant digit at the head and the least significant at the tail. I rely on the backward `prev` pointers when I propagate carries and borrows (those flow from least significant to most significant), and on the forward `next` pointers when I print a number or run long division. The sign is always kept separate from the digits, never mixed into them. That single decision — magnitude in the list, sign on the side — is the backbone of the whole project.

## 1-original/ — my first drafts

Both original variants use the same multi-file partition that I started the project with. Each operation lived in its own translation unit:

| File | What I put in it |
| --- | --- |
| `apc.h` | The `Dlist` node, the `SUCCESS`/`FAILURE` macros, and every prototype. |
| `main.c` | Argument handling and the operator `switch`. |
| `functions.c` | The shared list utilities: insert, delete, print, and input parsing. |
| `addition.c` | The addition routine. |
| `subtraction.c` | The subtraction routine plus the borrow helper. |
| `multiplication.c` | The multiplication routine. |
| `division.c` | The division routine. |

### 1-original/with-sign/

This is the variant that accepts a leading `+` or `-` on either operand. It carries a `char sign` inside each node and threads sign pointers through every function. It works on many inputs but I later found three real bugs in it: the input parser corrupts a number when only one operand carries a sign, the magnitude comparison accidentally compares the sign character because it reads the raw command-line strings, and the division loops forever on any division that leaves a remainder.

### 1-original/without-sign/

This is the simpler variant that only accepts non-negative operands. Its node has no sign field and its functions take no sign pointers. Addition, subtraction, multiplication, and exact division are correct, but the same division loop hangs on any remainder, the lists are never freed, and running it with no arguments crashes.

## 2-refactored/ — the audited engine

When I refactored, I made one structural decision: collapse the seven-file split into a clean three-file layout. A calculator of this size does not need a separate file per operation; it needs one header that states the contract, one implementation file that honours it, and one driver. Both refactored variants share this layout:

| File | What I put in it |
| --- | --- |
| `bignum.h` | The node definition, the status macros, and every public prototype — the engine's contract. |
| `bignum.c` | The whole engine, in three layers: list primitives, sign-blind magnitude routines, and the top-level operations. |
| `main.c` | The thin driver: argument validation, dispatch, printing, and cleanup. |
| `Makefile` | The GCC build with `all`, `debug`, `memcheck`, and `clean` targets. |
| `.gitignore` | Local ignore rules for that buildable folder. |
| `README.md` | A quick start and a summary of what I fixed. |

Inside `bignum.c` I deliberately grouped the functions so the file reads from simplest to hardest. The list primitives come first and are the only functions that ever call `malloc` or `free`, which keeps my memory management auditable in one place. The magnitude primitives come next and know nothing about signs. The signed (or, in the unsigned variant, the plain) operations come last and only decide policy — which sign the result takes, or whether a subtraction went negative — before delegating the digit work downward.

### 2-refactored/with-sign/

The corrected signed engine. I fixed every original bug: each operand is now parsed with its own private index so they cannot corrupt each other, magnitude comparison works directly on the digit lists instead of the raw strings, division is rewritten as long division that always terminates and produces a true big-number quotient, and every list is freed on every exit path.

### 2-refactored/without-sign/

The corrected unsigned engine, rebuilt to the same standard. It rejects signed input by design, reports a negative subtraction result through a small flag rather than a stored sign, uses the same long division, and leaks nothing.

## docs/ — the written material

I keep this guide here, at the repository root, because it describes the project as a whole rather than any single folder. Each refactored variant is self-contained and buildable on its own, but the explanation of how the versions relate lives here.

## Why this organisation helps me

The two-generation split is a narrative: `1-original` is where I started and `2-refactored` is where careful auditing took me. Within the refactored engine, the header is the contract I read at a glance, `bignum.c` is the single file I open to change arithmetic behaviour, and `main.c` is where I look to change how the program talks to the outside world. Because every allocation is concentrated at the top of the engine, I can audit memory without reading the whole file — which is exactly the confidence I wanted before calling the refactored versions production-grade.
