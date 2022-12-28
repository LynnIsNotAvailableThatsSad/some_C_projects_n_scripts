#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#define _POSIX_C_SOURCE 200809L

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

struct flags {
    int flag_b;
    int flag_e;
    int flag_n;
    int flag_s;
    int flag_t;
    int flag_v;
};

typedef struct flags fcat;

void print_file(FILE *FL, fcat *flags_cat);
int search4flag(int argc, char* argv[], fcat *flags_cat);


#endif  //  SRC_CAT_S21_CAT_H_
