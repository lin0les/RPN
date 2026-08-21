#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "calc.h"

#define MAXLEN 50

static char input[MAXLEN];
static int ip = 0;
static bool ii = false;

static int mygetline(char s[])
{
    int i = 0;
    int c;

    ip = 0;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < MAXLEN - 1)
            s[i++] = c;
        else
            printf("You reached to max len\n");
    }

    if (c == '\n')
        s[i++] = '\n';

    s[i] = '\0';

    ii = true;

    return i;
}

int getop(char s[])
{
    int i, c, next;

    if (!ii)
        mygetline(input);

    while ((c = input[ip]) != '\0') {

        if (c == ' ' || c == '\t') {
            while ((c = input[ip]) == ' ' || c == '\t')
                ip++;
        }

        if (isalpha(c)) {

            s[0] = input[ip++];

            int stock = c;

            i = 0;

            while (isalpha(c = input[ip++]))
                s[++i] = c;

            s[++i] = '\0';

            ip--;

            if (strlen(s) > 1)
                return FUNCTION;

            while ((c = input[ip++]) == ' ' || c == '\t')
                ;

            if (c == '=') {
                /*
                 * Variable name is returned in s[0].
                 */
                s[0] = stock;
                s[1] = '\0';

                return '=';
            }

            ip--;

            s[0] = stock;
            s[1] = '\0';

            return VARIABLE;
        }

        if (c == '@') {
            ip++;
            return '@';
        }

        s[0] = c;
        s[1] = '\0';

        if (c == '-') {
            next = input[ip++];

            if (isdigit(next)) {
                s[0] = '-';
                s[1] = next;
                i = 1;
                c = next;

                goto negative;
            }

            c = '-';
            ip--;
        }

        i = 0;

negative:

        if (!isdigit(c) && c != '.') {
            ip++;
            return c;
        }

        if (isdigit(c))
            while (isdigit(s[++i] = c = input[++ip]))
                ;

        if (c == '.')
            while (isdigit(s[++i] = c = input[++ip]))
                ;

        s[i] = '\0';

        return NUMBER;
    }

    return EOF;
}
