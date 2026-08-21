#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "calc.h"

static double variables[26];
static bool used[26] = {false};
static double last;

int main(int argc, char *argv[])
{
    int type;
    double op1, op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {

        switch (type) {

        case NUMBER:
            push(atof(s));
            break;

        case '+':
            push(pop() + pop());
            break;

        case '*':
            push(pop() * pop());
            break;

        case '-':
            op2 = pop();
            push(pop() - op2);
            break;

        case '/':
            op2 = pop();

            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");

            break;

        case '%':
            op2 = pop();

            if (op2 == 0)
                printf("error: zero divisor\n");
            else
                push(fmod(pop(), op2));

            break;

        case '=':
            if (stack_size() > 0) {
                variables[s[0] - 'a'] = stack_top();
                used[s[0] - 'a'] = true;
            } else {
                printf(
                    "error: no operand to assign to '%c'\n",
                    s[0]
                );
            }

            break;

        case '\n':
            last = pop();
            printf("Result: %.8g\n", last);
            break;

        case FUNCTION:

            if (strcmp(s, "sin") == 0) {
                push(sin(pop()));

            } else if (strcmp(s, "exp") == 0) {
                push(exp(pop()));

            } else if (strcmp(s, "pow") == 0) {
                op2 = pop();
                op1 = pop();

                push(pow(op1, op2));

            } else if (strcmp(s, "print") == 0) {
                printtop2();

            } else if (strcmp(s, "swap") == 0) {
                swaplast2();

            } else if (strcmp(s, "duplicate") == 0) {
                duplicate();

            } else if (strcmp(s, "clear") == 0) {
                clearstack();

            } else {
                printf("error: unknown function %s\n", s);
            }

            break;

        case VARIABLE:

            if (used[s[0] - 'a'])
                push(variables[s[0] - 'a']);
            else {
                printf(
                    "error: '%c' has no value yet, stack will be cleared\n",
                    s[0]
                );

                clearstack();
            }

            break;

        case '@':
            push(last);
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    return 0;
}
