#include "getstr.h"

int get_str(char **str, FILE *file) {
  int answer = 0;
  char ch;
  int len_str = 0;
  do {
    ch = fgetc(file);
    if (ch != EOF) {
      str[0] = realloc(str[0], sizeof(char) * (++len_str));
      str[0][len_str - 1] = ch;
    }
  } while (ch != '\n' && ch != EOF);
  if (ch == EOF && len_str == 0) {
    answer = ch;
  } else {
    if (str[0][len_str - 1] != '\n') {
      str[0] = realloc(str[0], sizeof(char) * (++len_str));
      str[0][len_str - 1] = '\n';
    }
    str[0] = realloc(str[0], sizeof(char) * (len_str + 1));
    str[0][len_str] = '\0';
  }
  return answer;
}
