#include <stdio.h>
#include "calc.h"

#define MAXVAL 100

static int sp = 0;
static double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];

    printf("error: stack empty\n");
    return 0.0;
}

int stack_size(void)
{
    return sp;
}

double stack_top(void)
{
    if (sp > 0)
        return val[sp - 1];

    return 0.0;
}

void printtop2(void)
{
    if (sp >= 2)
        printf("P: %.1f, %.1f\n", val[sp - 2], val[sp - 1]);
    else
        printf("error: not enough operands\n");
}

void duplicate(void)
{
    if (sp < MAXVAL)
        val[sp++] = val[sp - 1];
    else
        printf("error: can't duplicate last element, because stack is full\n");
}

void swaplast2(void)
{
    double temp;

    if (sp >= 2) {
        temp = val[sp - 2];
        val[sp - 2] = val[sp - 1];
        val[sp - 1] = temp;
    } else {
        printf("error: not enough operands\n");
    }
}

void clearstack(void)
{
    sp = 0;
}
