#define _POSIX_C_SOURCE 200809L
#include<stdio.h>
#include "s21_cat.h"
#include<unistd.h>
#include<string.h>
//#define _GNU_SOURCE

int main(int argc, char* argv[]) {
  fcat flags_cat = {0};
  FILE *FL;
  int ff = search4flag(argc, argv, &flags_cat);
  for (int i = 1 + ff; i < argc; i++) {
    FL = fopen(argv[i], "r");
    if (FL == NULL) {
            printf("%s - NET TAKOGO FILE, DEBIL. WRITE CORRECT FILENAME OR PASHOL NAHUI\n", argv[i]);
    } else {
      print_file(FL, &flags_cat);
    }
  }
}

void print_file(FILE *FL, fcat *flags_cat) {
  unsigned char s;
  unsigned char s1;
  int number = 1;
  s = fgetc(FL);
    if (!feof(FL)) {
      if ((flags_cat->flag_b && s != '\n') || flags_cat->flag_n) {
            printf("%6d\t", number);
            number++;
      } else if (flags_cat->flag_s && s == '\n') {
            while (s == '\n') {
              s1 = getc(FL);
              if (feof(FL)) {
                 break;
              } else if (s1 != '\n') {
                  if (flags_cat->flag_e) {
                    printf("$");
                  }
                 printf("%c", s);
              }
              s = s1;
            }
      } else if (!flags_cat->flag_s && flags_cat->flag_e && s == '\n') {
        printf("$");
      }
    }
        while (!feof(FL)) {
        s1 = fgetc(FL);
            if (flags_cat->flag_t && s == '\t') {
              printf("^I");
            } else if (flags_cat->flag_v && s < 32 && s != 10 && s != 9) {
              printf("^%c", s + 64);
            } else if (flags_cat->flag_v && s == 127) {
              printf("^%c", s - 64);
            } else if (flags_cat->flag_v && s > 127 && s < 160) {
              printf("M-^%c", s - 64);
            } else {
              printf("%c", s);
            }
            if (flags_cat->flag_b && s == '\n' && s1 != '\n' && (!feof(FL))) {
              printf("%6d\t", number);
              number++;
            } else if (flags_cat->flag_n && s == '\n' && (!feof(FL))) {
              printf("%6d\t", number);
              number++;
            }
            if (flags_cat->flag_e && s1 == '\n') {
                printf("$");
            }
            if (flags_cat->flag_s && s == '\n' && s1 == '\n') {
                printf("%c", s1);
                while (s1 == '\n') {
                    s1 = getc(FL);
                }
            }
         s = s1;
        }
  fclose(FL);
}

int search4flag(int argc, char* argv[], fcat* flags_cat) {
    int switcher = 0;
    int f = 0;
    int gnu = 0;
    char *pointer = argv[1];
      while ((switcher = getopt(argc, argv, "-benstvET")) != -1) {
            switch (switcher) {
                case 'v':
                   flags_cat->flag_v = 1;
                   break;
                case 'b':
                   flags_cat->flag_b = 1;
                   break;
                case 'E':
                   flags_cat->flag_e = 1;
                   break;
                case 'e':
                   flags_cat->flag_e = 1;
                   flags_cat->flag_v = 1;
                   break;
                case 'n':
                   flags_cat->flag_n = 1;
                   break;
                case 's':
                   flags_cat->flag_s = 1;
                   break;
                case 'T':
                   flags_cat->flag_t = 1;
                   break;
                case 't':
                   flags_cat->flag_t = 1;
                   flags_cat->flag_v = 1;
                   break;
                case '-':
                   if (strcmp(pointer, "--number-nonblank") == 0) {
                    flags_cat->flag_b = 1;
                    gnu++;
                    break;
                   } else if (strcmp(pointer, "--number") == 0) {
                    flags_cat->flag_n = 1;
                    gnu++;
                    break;
                   } else if (strcmp(pointer, "--squeeze-blank") == 0) {
                    flags_cat->flag_s = 1;
                    gnu++;
                    break;
                   } else {
                       printf("PASHOL NAHUI %s\n", pointer);
                   break;
                   }
                default:
    printf("%c - NE FLAG, BOLVAN. USE './s21_cat [-benstv][filename]' or PASHOL NAHUI\n", switcher);
    exit(0);
            }
            pointer++;
            f++;
            if (gnu) break;
      }
return f;
}

