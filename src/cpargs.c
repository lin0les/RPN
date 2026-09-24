#include <stdio.h>
#include "calc.h"

int copyargs(int argc, char *argv[]){

    extern char input[MAXLEN];

    int counter_high=0;
    int counter_low=0;
    int counter=0;
    argv++;

    for(; counter_low < argc && counter < MAXLEN-1; counter_low++){
        if(argv[counter_low] && counter < MAXLEN-1){
            for(counter_high=0; counter < MAXLEN-1; counter_high++){

                if(*(*(argv+counter_low)+counter_high) == '\0'){
                    input[counter++]=' ';
                    break;
                }

                input[counter++]=*(*(argv+counter_low)+counter_high);

            }

            if(counter >= MAXLEN-1){
                printf("error: input[] isn't enough to keep arguments\n");
                return 1;
            }
        }
    }

    if(--counter > MAXLEN-1){
        printf("error: input[] isn't enough to keep arguments\n");
        return 1;
    }

    input[counter]='\n';
    input[++counter]='\0';

    return 0;

}
