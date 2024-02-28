#ifndef GREP_S21_GREP_H_
#define GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../common/chfilename.h"
#include "../common/chline.h"
#include "../common/getstr.h"

typedef struct {
  int i;
  int e;
  int n;
  int s;
  int l;
  int v;
  int c;
  int h;
  int f;
  int o;
  int number_files;
  char **file_names;
  int number_regs;
  char **regs;
  int number_template;
  char **filename_template;
  int error_reg_read;
  int reg_new_line;
} options;

options input(int *argc, char **argv);
void get_arg(int *argc, char **argv, options *opt);
void get_file_name(int *argc, char **argv, options *opt);
void work(options *opt);
void all_regexec(regex_t *reg, char *str, int eflags);
int is_bin(FILE *file);
char *create_reg_from_file(options *opt, int *len_reg);
char *create_reg_from_e(options *opt, int *len_reg, char *regex);
int search_end_char(char *string, char ch);
char *get_reg(options *opt);

#endif  // GREP_S21_GREP_H_
