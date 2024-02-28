#include "chfilename.h"

#include <stdio.h>
#include <sys/stat.h>

int check_filename(char *str) {
  int len = 0;
  int path = 0;
  int answer = 0;
  for (char *ptr = str; *ptr != '\0'; ptr++) {
    len++;
    if (*ptr == '/')  // Если имя файла состовное
      path = 1;
  }
  if (len >= FILENAME_MAX || (!path && len > 255)) {
    fprintf(stderr, "Too long filename\n");
    answer = 1;
  }
  return answer;
}

int is_a_directory(char *file_name, int dont_print) {
  struct stat dir;
  int result = stat(file_name, &dir);
  if (result != -1) {
    if (S_ISDIR(dir.st_mode)) {
      result = 1;
    }
  } else {
    result = 2;
  }
  if (result == 1 && !dont_print) fprintf(stderr, "Is a directory\n");
  if (result == 2 && !dont_print)
    fprintf(stderr, "No such file or directory \n");
  return result;
}
