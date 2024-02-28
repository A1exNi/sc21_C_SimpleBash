#ifndef CAT_S21_CAT_H_
#define CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../common/chfilename.h"
#include "../common/chline.h"

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int number_files;
  char **file_names;
  int error_reg_read;
} options;

options input(int *argc, char **argv);
void get_arg(int *argc, char **argv, options *opt);
void get_file_name(int *argc, char **argv, options *opt);
void work(options *opt);
void print_v(char *ch);

#endif  // CAT_S21_CAH_H_
