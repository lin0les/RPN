#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'
#define VARIABLE 'v'
#define FUNCTION 'f'
#define MAXLEN 50

int sp = 0;
double val[MAXVAL];
double variables[26];
bool used[26] = {false};
double last;
int ch;
int buf;
bool buf_full = false;
char input[MAXLEN];
int ip = 0;
bool ii = false;

int getop(char[]);
void push(double);
double pop(void);

void printtop2(void);
void duplicate(void);
void swaplast2(void);
void clearstack(void);
int mygetline(char []);

int main(int argc, char *argv[]){
    int type;
    double op1, op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF){
        switch(type){
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
                if(op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();

                if(op2 == 0)
                    printf("error: zero divisor\n");
                else
                    push(fmod(pop(), op2));
                break;
            case '=':
                if(sp > 0){
                    variables[ch - 'a'] = val[sp - 1];
                    used[ch - 'a'] = true;

                } else{
                    printf("error: no operand to assign to '%c'\n", ch);
                }
                break;
            case '\n':
                last = pop();
                printf("Result: %.8g\n", last);
                ii = false;
                break;
            case FUNCTION:
                if(strcmp(s, "sin") == 0){
                    push(sin(pop()));
                } else if(strcmp(s, "exp") == 0){
                    push(exp(pop()));
                } else if(strcmp(s, "pow") == 0){
                    op2 = pop();
                    op1 = pop();
                    push(pow(op1, op2));
                } else if(strcmp(s, "print") == 0){
                    printtop2();
                } else if(strcmp(s, "swap") == 0){
                    swaplast2();
                } else if(strcmp(s, "duplicate") == 0){
                    duplicate();
                } else if(strcmp(s, "clear") == 0){
                    clearstack();
                } else {
                    printf("error: unknown function %s\n", s);
                }
                break;
            case VARIABLE:
                push(variables[s[0] - 'a']);
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

void push(double f){
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void){
    if(sp > 0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}

int mygetline(char s[]){
    int i = 0;
    int c;
    ip = 0;
    while((c = getchar()) != '\n' && c != EOF){
        if(i < MAXLEN - 1)
            s[i++] = c;
        else
            printf("You reached to max len\n");
    }
    if(c == '\n'){
        s[i++] = '\n';
    }
    s[i] = '\0';
    ii = true;
    return i;
}

int getop(char s[]){
    int i, c, next;

    if(!ii)
        mygetline(input);

    while((c = input[ip]) != '\0'){
        
        if(c == ' ' || c == '\t')
            while((c = input[ip]) == ' ' || c == '\t'){
                ip++;
            }
        
        if(isalpha(c)){
            s[0] = input[ip++];

            int stock = c;

            i = 0;
            while(isalpha(c = input[ip++])){
                s[++i] = c;
            }

            s[++i] = '\0';

            ip--;

            if(strlen(s) > 1)
                return FUNCTION;

            while((c = input[ip++]) == ' ' || c == '\t')
                ;

            if(c == '='){
                ch = stock;
                return '=';
            }

            if(used[stock - 'a'] == false){
                printf("error: '%c' has no value yet, stack will be cleared\n", ch);
                strcpy(s, "clear");
                return FUNCTION;
            }
            
            ip--;

            s[0] = stock;
            s[1] = '\0';

            return VARIABLE;
        }

        if(c == '@'){
            ip++;
            return '@';
        }

        s[0] = c;
        s[1] = '\0';

        if(c == '-'){
            next = input[ip++];
            if(isdigit(next)){
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
        if(!isdigit(c) && c != '.'){
            ip++;
            return c;
        }

        if(isdigit(c))
            while(isdigit(s[++i] = c = input[++ip]))
                ;

        if(c == '.')
            while(isdigit(s[++i] = c = input[++ip]))
                ;

        s[i] = '\0';

        return NUMBER;
    }

    return EOF;
}

void printtop2(void){
    if(sp >= 2)
        printf("P: %.1f, %.1f\n", val[sp - 2], val[sp - 1]);
    else
        printf("error: not enough operands\n");
}

void duplicate(void){
    if(sp < MAXVAL)
        val[sp++] = val[sp - 1];
    else
        printf("error: can't duplicate last element, because stack is full\n");
}

void swaplast2(void){
    double temp;

    if(sp >= 2){
        temp = val[sp - 2];
        val[sp - 2] = val[sp - 1];
        val[sp - 1] = temp;
    } else {
        printf("error: not enough operands\n");
    }
}

void clearstack(void){
    sp = 0;
}
