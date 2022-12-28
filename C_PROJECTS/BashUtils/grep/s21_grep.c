#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "s21_grep.h"
#include<stdlib.h>

int main(int argc, char* argv[]) {
flag flags = {0};
flags.filecount = 1;
flags.patterncount = 0;
char *name = NULL;
FILE *FL;
int ff = flag_parser(argc, argv, &flags);
flags.cou = flags.e;
    for (int i = 1; i < argc; i++) {
        name = filename(argc, &flags);
      if (name != NULL) {
         if ((FL = fopen(name, "r")) != NULL) {
           result(argc, &flags, FL, name, ff);
           fclose(FL);
         } else {
             if (!flags.s) {
                printf("NO SUCH FILE - %s\n", name);
             }
             continue;
         }
      } else {
          break;
      }
    }
}

int result(int argc, flag* flags, FILE *FL, char *name, int ff) {
char *to_print = NULL;
char *pat;
size_t n = 4;
int found = 0;
int count4c = 0;
int string_number = 1;
  while (getline(&to_print, &n, FL) != -1) {
    found = 0;
    flags->patterncount = 0;
    if (flags->e || ff == 0) {
        while ((pat = pattern(flags, ff)) != NULL) {
          if (strstr(to_print, pat) != NULL) {
            found++;
          }
        }
    } else {
    pat = pattern(flags, ff);
        if (flags->n || flags->h || flags->s) {
           if (strstr(to_print, pat) != NULL) {
                found++;
           }
        } else if (flags->l) {
           if (strstr(to_print, pat) != NULL) {
                printf("%s\n", name);
                break;
           }
        } else if (flags->c) {
           if (strstr(to_print, pat) != NULL) {
                count4c++;
           }
        } else if (flags->i) {
           if (ignorecase(pat, to_print) != -1) {
                 found++;
           }
        } else if (flags->v) {
            if (strstr(to_print, pat) == NULL) {
                found++;
            }
        }
    }

        if (found) {
           if ((argc - (ff*2+1) > 1) && argc > 4 && !flags->h) {
             if (flags->n) {
                printf("%s:%d:%s", name, string_number, to_print);
             } else {
             printf("%s:%s", name, to_print);
             }
           } else {
             if (flags->n) {
                printf("%d:%s", string_number, to_print);
             } else {
             printf("%s", to_print);
             }
           }
        }
        string_number++;
  }
  if (flags->c) {
    if ((argc - (ff*2+1) > 1) && argc > 4) {
      printf("%s:%d\n", name, count4c);
    } else {
      printf("%d\n", count4c);
    }
  }
free(to_print);
return 0;
}

int ignorecase(char *pat, char *to_print) {
int truth = 0;
int len = strlen(to_print);
int len_pat = strlen(pat);
int j = 0;
    for (int i = 0; i < len; i++) {
    if (truth == len_pat) {
        break;
    } else if ((unsigned long)j >= strlen(pat)) {
        j = 0;
    }
        if (to_print[i] == pat[j]) {
            truth++;
            j++;
            continue;
        } else if (to_print[i] > 96 && to_print[i] < 123) {
            if ((to_print[i] - 32) == pat[j]) {
                truth++;
                j++;
                continue;
            }
        } else if (to_print[i] > 64 && to_print[i] < 91) {
            if ((to_print[i] + 32) == pat[j]) {
                truth++;
                j++;
                continue;
            }
        } else {
            j = 0;
            truth = 0;
        }
    }
    if (truth < len_pat) truth = -1;
return truth;
}

char *pattern(flag* flags, int ff) {
  char *ptn = NULL;
    if ((flags->e && flags->patterncount < flags->e)) {
            ptn = flags->files[flags->patterncount];
            flags->patterncount++;
    } else if (ff == 0) {
        ptn = flags->files[0];
        if (flags->patterncount > 1) {
            ptn = NULL;
        }
        flags->patterncount++;
    } else if (!flags->e) {
        ptn = flags->files[0];
    }
return ptn;
}

char *filename(int argc, flag* flags) {
char *fp = NULL;
    if (flags->e) {
      if (flags->filecount < (argc - (flags->e*2))) {
        fp = flags->files[flags->cou];
        flags->cou++;
        flags->filecount++;
      }
    } else {
        fp = flags->files[flags->filecount];
        flags->filecount++;
    }
return fp;
}

int flag_parser(int argc, char* argv[], flag* flags) {
int f = 0;
int counter = 1;
int s = 0;
    while (counter < argc) {
            if (strcmp(argv[counter], "-e") == 0) {
                flags->files[s] = argv[counter+1];
                flags->e++;
                flags->flags[f] = argv[counter];
                f++;
                s++;
                counter = counter + 2;
                continue;
            } else if (strcmp(argv[counter], "-i") == 0) {
                flags->i = 1;
                flags->flags[f] = argv[counter];
                f++;
                counter++;
                continue;
            } else if (strcmp(argv[counter], "-v") == 0) {
                flags->v = 1;
                flags->flags[f] = argv[counter];
                f++;
                counter++;
                continue;
            } else if (strcmp(argv[counter], "-c") == 0) {
                flags->c = 1;
                flags->flags[f] = argv[counter];
                f++;
                counter++;
                continue;
            } else if (strcmp(argv[counter], "-l") == 0) {
                flags->l = 1;
                flags->flags[f] = argv[counter];
                f++;
                counter++;
                continue;
            } else if (strcmp(argv[counter], "-n") == 0) {
                flags->n = 1;
                flags->flags[f] = argv[counter];
                f++;
                counter++;
                continue;
            } else if (strcmp(argv[counter], "-h") == 0) {
                flags->h = 1;
                flags->flags[f] = argv[counter];
                f++;
                counter++;
                continue;
            } else if (strcmp(argv[counter], "-s") == 0) {
                flags->s = 1;
                flags->flags[f] = argv[counter];
                f++;
                counter++;
                continue;
            } else {
                if (argv[counter][0] == '-') {
                    if (strlen(argv[counter]) == 2) {
                         printf("NO SUCH OPTION -- %s\n", argv[counter]);
                         exit(0);
                    } else {
                      flags->files[s] = argv[counter];
                      s++;
                      counter++;
                      continue;
                    }
                } else {
                    flags->files[s] = argv[counter];
                    s++;
                    counter++;
                    continue;
                }
            }
    }
return f;
}
