# RPN Calculator

A Reverse Polish Notation (RPN) calculator written in C and organized as a multi-source application.

## Project Structure

```text
.
├── main.c
├── getop.c
├── stack.c
├── calc.h
├── Makefile
├── README.md
└── LICENSE
```

## Description

The calculator uses Reverse Polish Notation, where operators are placed after their operands.

Example:

```text
2 3 +
Result: 5
```

More complex expressions can be written without parentheses:

```text
2 3 4 + *
Result: 14
```

## Features

* Basic arithmetic operations:

  * `+`
  * `-`
  * `*`
  * `/`
  * `%`
* Floating-point calculations
* Negative numbers
* Variables `a` through `z`
* Variable assignment
* Functions:

  * `sin`
  * `exp`
  * `pow`
* Stack operations:

  * `print`
  * `duplicate`
  * `swap`
  * `clear`
* Store and reuse the last calculated result with `@`
* Input parsing from complete lines
* Stack overflow and underflow checks

## Variables

Variables use single lowercase letters.

Example:

```text
10 a =
a 5 *
Result: 50
```

A variable must be assigned a value before it can be used.

```text
a
```

If the variable has no assigned value, an error is reported and the stack is cleared.

## Functions

### `sin`

```text
1 sin
```

### `exp`

```text
2 exp
```

### `pow`

```text
2 3 pow
```

Result:

```text
Result: 8
```

## Stack Commands

### Print top two elements

```text
1 2 print
```

### Duplicate top element

```text
5 duplicate
```

### Swap top two elements

```text
1 2 swap
```

### Clear stack

```text
1 2 3 clear
```

## Last Result

The `@` operator pushes the last printed result back onto the stack.

Example:

```text
2 3 +
Result: 5
@ 2 *
Result: 10
```

## Source Files

### `main.c`

Contains the main program loop, command processing, variables, functions, and calculation logic.

### `getop.c`

Handles input processing and identifies numbers, variables, functions, operators, assignments, and special commands.

The input buffer and parsing state are kept private to this source file using `static` variables.

### `stack.c`

Implements the calculator stack.

The stack pointer and stack array are declared as file-local `static` variables:

```c
static int sp = 0;
static double val[MAXVAL];
```

They can only be accessed directly by functions inside `stack.c`.

### `calc.h`

Contains shared constants and function declarations used by the different source files.

## Compilation

Compile all source files:

```bash
gcc main.c getop.c stack.c -lm -o rpn
```

For debugging:

```bash
gcc -g -Wall -Wextra main.c getop.c stack.c -lm -o rpn
```

## Running

```bash
./rpn
```

## Example

```text
$ ./rpn
5 6 +
Result: 11
2 *
Result: 22
10 a =
a 3 pow
Result: 1000
```

## Make

If a `Makefile` is provided, the project can be built with:

```bash
make
```

Clean the generated object files and executable with:

```bash
make clean
```

