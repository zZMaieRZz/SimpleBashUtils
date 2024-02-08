//
// Created by Manhunte on 03.02.2024.
//

#include "s21_cat.h"

int main(int argc, char **argv) {
  unsigned int flags = 0;
  int result_code;
  result_code = parse_args(argc, argv, &flags);
  if (result_code == OK) {
    while (optind < argc) {
      char *file_name = argv[optind++];
      if (process_files(file_name, flags) == FILE_ERROR) {
        print_file_error(file_name);
      }
    }
  }
  if (result_code == FLAG_ERROR) {
    print_arg_error();
  }
  return result_code;
}

int process_files(char *file_name, unsigned int flags) {
  FILE *fp = fopen(file_name, "r");
  if (fp == NULL) return FILE_ERROR;
  int ch;
  unsigned int new_line_flag = TRUE;
  unsigned int line_counter = 1;
  unsigned int new_line_counter = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (!IS_NL_CHAR(ch) && new_line_flag == TRUE &&
        (IS_FLAG_B(flags) || IS_FLAG_N(flags))) {
      printf("%6u\t", line_counter++);
    }
    if (IS_NL_CHAR(ch) && new_line_flag == TRUE && IS_FLAG_N(flags)) {
      printf("%6u\t", line_counter++);
      new_line_flag = FALSE;
    }
    if ((IS_SPEC_CHAR(ch) && IS_FLAG_V(flags)) ||
        (IS_TAB_CHAR(ch) && IS_FLAG_T(flags))) {
      new_line_flag = FALSE;
      new_line_counter = 0;
      if (ch > 127) printf("M-");
      printf("^%c", ch >= 32 ? ch - '@' : ch + '@');
    } else if (IS_NL_CHAR(ch)) {
      if (new_line_counter < 2) {
        new_line_flag = TRUE;
        if (IS_FLAG_E(flags)) {
          printf("$\n");
        } else {
          printf("\n");
        }
      }
      if (IS_FLAG_S(flags)) new_line_counter++;
    } else {
      new_line_counter = 0;
      new_line_flag = FALSE;
      printf("%c", ch);
    }
  }
  fclose(fp);
  return OK;
}

int parse_args(int argc, char **argv, unsigned int *flags) {
  int getopt_result = 0;
  int result_code = OK;
  struct option long_options[] = {{"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {"number-nonblank", 0, 0, 'b'},
                                  {0, 0, 0, 0}};
  while (getopt_result > -1 && result_code == OK) {
    int option_index = 0;
    getopt_result =
        getopt_long(argc, argv, "+beEnstTv", long_options, &option_index);
    result_code = process_flags(flags, getopt_result);
  }
  return result_code;
}

int process_flags(unsigned int *flags, int getopt_result) {
  int result_code = OK;
  if (getopt_result == 'b') {
    *flags |= FLAG_B;
    if (IS_FLAG_N(*flags)) {
      *flags &= ~FLAG_N;
    }
  } else if (getopt_result == 'e') {
    *flags |= FLAG_V;
    *flags |= FLAG_E;
  } else if (getopt_result == 'E') {
    *flags |= FLAG_E;
  } else if (getopt_result == 'n') {
    if (!(IS_FLAG_B(*flags))) {
      *flags |= FLAG_N;
    }
  } else if (getopt_result == 's') {
    *flags |= FLAG_S;
  } else if (getopt_result == 't') {
    *flags |= FLAG_V;
    *flags |= FLAG_T;
  } else if (getopt_result == 'T') {
    *flags |= FLAG_T;
  } else if (getopt_result == 'v') {
    *flags |= FLAG_V;
  } else if (getopt_result == '?') {
    result_code = FLAG_ERROR;
  }
  return result_code;
}

void print_arg_error() {
  fprintf(stderr, "usage: s21_cat [-beEnstTv] [file ...]\n");
}

void print_file_error(char *file_name) {
  fprintf(stderr, "s21_cat: %s: No such file or directory\n", file_name);
}
