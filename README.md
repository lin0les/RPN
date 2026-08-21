# Multi-Source C Application

A C application organized into multiple source and header files.

## Project Structure

```text
.
├── main.c
├── rpn.c
├── rpn.h
├── stack.c
├── stack.h
└── Makefile
```

## Description

The application is separated into multiple source files to keep the code organized and make individual components easier to maintain.

* `main.c` — Program entry point and main application flow.
* `rpn.c` — RPN input processing and calculation logic.
* `rpn.h` — Function declarations and shared definitions for the RPN module.
* `stack.c` — Stack implementation and stack operations.
* `stack.h` — Function declarations for the stack module.
* `Makefile` — Build configuration.

## Static Variables

Internal variables that should not be accessed directly from other source files can be declared with `static`.

For example:

```c
static double val[MAXVAL];
static int sp;
```

These variables can be accessed by functions inside the same `.c` file, but they are not visible from other source files.

## Compilation

Compile the application with:

```bash
gcc main.c rpn.c stack.c -o rpn
```

If the program uses functions from the math library:

```bash
gcc main.c rpn.c stack.c -lm -o rpn
```

For debugging:

```bash
gcc -g -Wall -Wextra main.c rpn.c stack.c -lm -o rpn
```

## Using Make

Build the project:

```bash
make
```

Clean compiled files:

```bash
make clean
```

## Running

```bash
./rpn
```

