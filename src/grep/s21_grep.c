#include "s21_grep.h"

int main(int argc, char **argv) {
  options opt = input(&argc, argv);
  if (opt.file_names != NULL && opt.error_reg_read != '?') {
    work(&opt);
    free(opt.file_names);
  } else {
    fprintf(
        stderr,
        "usage: %s [-ivclnhs] [-e pattern] [-f file] [pattern] [file ...]\n",
        argv[0]);
  }
  if (opt.regs != NULL) free(opt.regs);
  if (opt.filename_template != NULL) free(opt.filename_template);
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
  const char *short_options = "e:ivclnhsf:o";
  const struct option long_options[1] = {{0}};
  int result = 0;
  while (result != -1) {
    result = getopt_long(*argc, argv, short_options, long_options, NULL);
    switch (result) {
      case 'e':
        opt->e = 1;
        opt->regs = realloc(opt->regs, sizeof(char *) * (++opt->number_regs));
        opt->regs[opt->number_regs - 1] = optarg;
        if (optarg[0] == '$' && optarg[1] == '\0') opt->reg_new_line = 1;
        break;
      case 'i':
        opt->i = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'c':
        opt->c = 1;
        break;
      case 'l':
        opt->l = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 'h':
        opt->h = 1;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'f':
        if (check_filename(optarg) == 0) {  // Проверка длины имени файла
          opt->f = 1;
          int isdir = is_a_directory(
              optarg, opt->s);  // Проверка на папку и отсутствие файла
          if (isdir) {
            opt->error_reg_read = '?';
            result = -1;
          } else {
            opt->filename_template =
                realloc(opt->filename_template,
                        sizeof(char *) * (++opt->number_template));
            opt->filename_template[opt->number_template - 1] = optarg;
          }
        } else {
          opt->error_reg_read = '?';
          result = -1;
        }
        break;
      case 'o':
        opt->o = 1;
        break;
      case '?':
        opt->error_reg_read = result;
        break;
    }
  }
}

void get_file_name(int *argc, char **argv, options *opt) {
  int arg_wout_min = 0;
  for (int i = 1; i < *argc; i++) {  // Под нулевым индексом имя программы
    if (*argv[i] != '-') {  // Все аргументы без -
      // Если есть -e или -f, то арг является именем файла.
      // Или если нет -f и -e и при этом уже был арг без -
      if ((opt->e || opt->f) || (!opt->e && !opt->f && arg_wout_min)) {
        if (check_filename(argv[i]) == 0) {  // Проверяем на длину имени файла
          opt->file_names =
              realloc(opt->file_names, sizeof(char *) * (++opt->number_files));
          opt->file_names[opt->number_files - 1] = argv[i];
        }
      } else {
        if (!arg_wout_min) {  // Если это первый арг без - и нет -e или -f,
                              // то это рег выражение
          opt->regs = realloc(opt->regs, sizeof(char *) * (++opt->number_regs));
          opt->regs[opt->number_regs - 1] = argv[i];
          arg_wout_min = 1;
        }
      }
    } else {
      // Если аргумент -e или -f в конце, следующий аргумент мы не должны
      // обрабатывать как имя файла
      if (search_end_char(argv[i], 'e') || search_end_char(argv[i], 'f')) i++;
    }
  }
}

int search_end_char(char *string, char ch) {
  int answer = 0;
  for (char *ptr = string; *ptr != '\0'; ptr++) {
    if (*ptr == ch && *(ptr + 1) == '\0') answer = 1;
  }
  return answer;
}

void work(options *opt) {
  regex_t reg;
  char *regex = get_reg(opt);
  int cflags = REG_EXTENDED;
  if (opt->i) cflags |= REG_ICASE;  // i
  int error_regc;
  if (regex != NULL)  // возможно если в файле при -f пусто
    error_regc = regcomp(&reg, regex, cflags);
  else
    error_regc = 14;
  if (error_regc == 0) {
    int eflags = 0;
    for (int i = 0; i < opt->number_files; i++) {
      // проверяем на каталог
      int isdir = is_a_directory(opt->file_names[i], opt->s);
      if (!isdir) {
        FILE *file = fopen(opt->file_names[i], "r");
        // проверка на бин
        if (!is_bin(file)) {
          char *str = NULL;
          int nmatch = 0;
          int nstr = 0;
          int error_s;
          int error_rege;
          int empty_line = 0;
          do {
            if (!opt->reg_new_line) empty_line = is_empty_line(file);
            error_s = get_str(&str, file);
            if (error_s > -1) {
              nstr++;
              error_rege = regexec(&reg, str, 0, NULL, eflags);
              if ((!opt->v && error_rege == 0 && !empty_line) ||
                  (opt->v &&
                   (error_rege != 0 || (error_rege == 0 && empty_line)))) {
                nmatch++;
                if (!opt->c && !opt->l) {
                  if (opt->number_files > 1 &&
                      !opt->h) {  // имя файла перед строкой
                    printf("%s:", opt->file_names[i]);
                  }
                  if (opt->n) {  // n
                    printf("%d:", nstr);
                  }
                  if ((!opt->o || (opt->v && opt->o))) {
                    printf("%s", str);  // печать всей строки
                  } else {
                    if (opt->reg_new_line)
                      printf("%s", str);
                    else
                      all_regexec(&reg, str, eflags);  // печать совпадений
                  }
                }
              }
            }
          } while (error_s > -1);
          fclose(file);
          if (opt->c && !opt->l) {  // c
            if ((!empty_line && nstr > 0) ||
                (!empty_line && !opt->reg_new_line)) {
              if (opt->number_files > 1 && !opt->h)
                printf("%s:", opt->file_names[i]);
              printf("%d\n", nmatch);
            }
          }
          if (opt->l) {
            if (opt->number_files > 1 && opt->c && !opt->h)
              printf("%s:", opt->file_names[i]);
            if (opt->c) {
              if (nmatch > 0) {
                printf("1\n");
              } else {
                if ((!empty_line && nstr > 0) ||
                    (!empty_line && !opt->reg_new_line))
                  printf("0\n");
              }
            }
            if (nmatch > 0) printf("%s\n", opt->file_names[i]);
          }
          free(str);
        } else {
          fprintf(stderr, "Binary file match\n");
        }
      }
    }
  } else {
    if (regex != NULL) {
      size_t errbuf_size = 256;
      char errbuf[errbuf_size];
      regerror(error_regc, &reg, errbuf, errbuf_size);
      fprintf(stderr, "%s\n", errbuf);
    }
  }
  if ((opt->e || opt->f) && regex != NULL) free(regex);
  if (regex != NULL) regfree(&reg);
}

char *get_reg(options *opt) {
  int len_reg = 0;
  char *regex = NULL;
  if (opt->f) {
    regex = create_reg_from_file(opt, &len_reg);
  }
  if (opt->e) {
    regex = create_reg_from_e(opt, &len_reg, regex);
  }
  if (!opt->e && !opt->f) {
    regex = opt->regs[0];
  }
  return regex;
}

char *create_reg_from_e(options *opt, int *len_reg, char *regex) {
  if (!opt->reg_new_line) {
    if (*len_reg > 0) {
      *len_reg += 1;
      regex = realloc(regex, sizeof(char) * (*len_reg));
      regex[*len_reg - 1] = '|';
    }
    for (int i = 0; i < opt->number_regs; i++) {
      for (char *ptr = opt->regs[i]; *ptr != '\0'; ptr++) {
        regex = realloc(regex, sizeof(char) * (++(*len_reg)));
        regex[*len_reg - 1] = *ptr;
      }
      if (i < opt->number_regs - 1) {
        *len_reg += 1;
        regex = realloc(regex, sizeof(char) * (*len_reg));
        regex[*len_reg - 1] = '|';
      }
    }
  } else {
    *len_reg = 1;
    regex = realloc(regex, sizeof(char) * (*len_reg));
    regex[*len_reg - 1] = '$';
  }
  regex = realloc(regex, sizeof(char) * (*len_reg + 1));
  regex[*len_reg] = '\0';
  return regex;
}

char *create_reg_from_file(options *opt, int *len_reg) {
  char *regex = NULL;
  char *buf = NULL;
  int error_str;
  int is_char = 0;
  int empty_line = 0;
  for (int i = 0; i < opt->number_template; i++) {
    FILE *file = fopen(opt->filename_template[i], "r");
    do {
      empty_line = is_empty_line(file);
      error_str = get_str(&buf, file);
      if (error_str > -1) {
        for (char *ptr = buf; *ptr != '\0'; ptr++) {
          if (*ptr == '\n') {
            if (is_char) {
              *len_reg += 1;
              regex = realloc(regex, (*len_reg) * sizeof(char));
              regex[*len_reg - 1] = '|';
            }
          } else {
            is_char = 1;
            regex = realloc(regex, (++(*len_reg)) * sizeof(char));
            regex[*len_reg - 1] = *ptr;
          }
        }
      }
    } while (!feof(file) && !empty_line);
    fclose(file);
  }
  if (empty_line) {
    opt->reg_new_line = 1;
    *len_reg = 1;
    regex = realloc(regex, ((*len_reg) + 1) * sizeof(char));
    regex[*len_reg - 1] = '$';
    regex[*len_reg] = '\0';
  }
  if (*len_reg > 1) {
    regex[*len_reg - 1] = '\0';
    *len_reg -= 1;
    free(buf);
  }
  return regex;
}

int is_bin(FILE *file) {
  int answer = 0;
  char ch, ch2;
  int is_extended = 0;
  do {
    ch = fgetc(file);
    if (ch > -63 && ch < -32) {
      ch2 = fgetc(file);
      if (ch2 > -65) {
        is_extended = 1;
        fseek(file, -1, SEEK_CUR);
      }
    }
  } while (!feof(file));
  if (is_extended) answer = 1;
  fseek(file, 0, SEEK_SET);
  return answer;
}

void all_regexec(regex_t *reg, char *str, int eflags) {
  char *buf_str = str;
  int error;
  regmatch_t pmatch[1];
  do {
    error = regexec(reg, buf_str, 1, pmatch, eflags);
    if (error == 0) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        printf("%c", buf_str[i]);
      }
      if (pmatch[0].rm_so == pmatch[0].rm_eo) {
        buf_str += pmatch[0].rm_eo + 1;
      } else {
        buf_str += pmatch[0].rm_eo;
        printf("\n");
      }
    }
  } while (error == 0 && buf_str[0] != '\0');
}
