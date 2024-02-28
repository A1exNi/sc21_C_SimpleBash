#include "chline.h"

int is_new_line(FILE *file) {
  int result = 0;
  long int pos = ftell(file);
  if (pos == 1) {
    fseek(file, pos - 1, SEEK_SET);
  } else {
    fseek(file, pos - 2, SEEK_SET);
  }
  char ch = fgetc(file);
  if (ch == '\n' || pos == 1) result = 1;
  fseek(file, pos, SEEK_SET);
  return result;
}

int is_empty_line(FILE *file) {
  int result = 0;
  long int pos = ftell(file);
  char ch = fgetc(file);
  if (ch == '\n') result = 1;
  fseek(file, pos, SEEK_SET);
  return result;
}
