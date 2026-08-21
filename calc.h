#ifndef CALC_H
#define CALC_H

#define MAXOP 100

#define NUMBER   '0'
#define VARIABLE 'v'
#define FUNCTION 'f'

void push(double);
double pop(void);

int stack_size(void);
double stack_top(void);

int getop(char []);

void printtop2(void);
void duplicate(void);
void swaplast2(void);
void clearstack(void);

#endif
