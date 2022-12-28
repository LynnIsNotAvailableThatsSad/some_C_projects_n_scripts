#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include<stdio.h>
#include<string.h>
#include<unistd.h>


struct flags {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int patterncount;
    int filecount;
    int cou;
    char *flags[50];
    char *files[100];
};

typedef struct flags flag;

int flag_parser(int argc, char* argv[], flag* flags);
char *filename(int argc, flag* flags);
char *pattern(flag* flags, int ff);
int ignorecase(char *pat, char *to_print);
int result(int argc, flag* flags, FILE *FL, char *name, int ff);

#endif  //  SRC_GREP_S21_GREP_H_
