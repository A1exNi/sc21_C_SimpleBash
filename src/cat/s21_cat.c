#include "s21_cat.h"

int main(int argc, char **argv) {
  options opt = input(&argc, argv);
  if (opt.file_names != NULL && opt.error_reg_read != '?') {
    work(&opt);
    free(opt.file_names);
  }
  return 0;
}

options input(int *argc, char **argv) {
  options opt = {0};
  if (*argc > 1) {
    get_arg(argc, argv, &opt);
    if (opt.error_reg_read != '?') get_file_name(argc, argv, &opt);
  } else {
    fprintf(stderr, "No arguments\n");
  }
  return opt;
}

void get_arg(int *argc, char **argv, options *opt) {
  const char *short_options = "+benstvET";
  const struct option long_options[4] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  int result = 0;
  while (result != -1) {
    result = getopt_long(*argc, argv, short_options, long_options, NULL);
    switch (result) {
      case 'b':
        opt->b = 1;
        break;
      case 'e':
        opt->e = 1;
        opt->v = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 't':
        opt->t = 1;
        opt->v = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'E':
        opt->e = 1;
        break;
      case 'T':
        opt->t = 1;
        break;
      case '?':
        opt->error_reg_read = result;
        break;
    }
  }
}

void get_file_name(int *argc, char **argv, options *opt) {
  for (int i = 1; i < *argc; i++) {  // Под нулевым имя программы
    if (*argv[i] != '-') {
      if (check_filename(argv[i]) == 0) {
        opt->file_names =
            realloc(opt->file_names, sizeof(char *) * (++opt->number_files));
        opt->file_names[opt->number_files - 1] = argv[i];
      }
    }
  }
}

void work(options *opt) {
  for (int i = 0; i < opt->number_files; i++) {
    int isdir = is_a_directory(opt->file_names[i], 0);
    if (!isdir) {
      FILE *file = fopen(opt->file_names[i], "r");
      char ch;
      int number_line = 1;
      int empty_line_count = 0;
      long int pos = 0;
      fseek(file, 0, SEEK_END);
      long int pos_end = ftell(file);
      fseek(file, 0, SEEK_SET);
      do {
        if (pos < pos_end) {
          int empty_line = is_empty_line(file);
          ch = fgetc(file);
          pos++;
          if (opt->s && empty_line && is_new_line(file)) {
            empty_line_count++;
          } else {
            empty_line_count = 0;
          }
          if (opt->n && is_new_line(file) && !opt->b &&  // n
              empty_line_count < 2) {
            printf("%6d\t", number_line++);
          } else {
            if (opt->b && is_new_line(file) && !empty_line) {  // b
              printf("%6d\t", number_line++);
            }
          }
          if (opt->v) {
            print_v(&ch);
          }
          if (opt->e && ch == '\n' && empty_line_count < 2) {  // e
            printf("$");
          }
          if (opt->t && ch == '\t') {  // t
            printf("^");
            ch = 'I';
          }
          if (empty_line_count < 2)
            printf("%c", ch);
          else
            empty_line_count--;
        }
      } while (pos < pos_end);
      fclose(file);
    }
  }
}

void print_v(char *ch) {
  if (*ch < -96) {
    printf("M-^");
    *ch += 192;
  }
  if (*ch > -1 && *ch < 32 && *ch != 10 && *ch != 9) {
    printf("^");
    *ch += 64;
  }
  if (*ch == 127) {
    printf("^");
    *ch = '?';
  }
}
