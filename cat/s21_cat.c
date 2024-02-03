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
  unsigned int n_cnt = 0;
  while ((ch = fgetc(fp)) != EOF) {
    if (!is_n_char(ch) && new_line_flag == TRUE &&
        (flags & FLAG_B || flags & FLAG_N)) {
      printf("%6u\t", line_counter++);
    }
    if (is_n_char(ch) && new_line_flag == TRUE && flags & FLAG_N) {
      printf("%6u\t", line_counter++);
      new_line_flag = FALSE;
    }
    if ((is_spec_char(ch) && flags & FLAG_V) ||
               (is_t_char(ch) && flags & FLAG_T)) {
      new_line_flag = FALSE;
      n_cnt = 0;
      if (ch > 127) printf("M-");
      printf("^%c", ch >= 32 ? ch - 128 + '@' : ch + '@');
    } else if (is_n_char(ch)) {
      if (n_cnt < 2) {
        new_line_flag = TRUE;
        if (flags & FLAG_E) {
          printf("$\n");
        } else {
          printf("\n");
        }
      }
      if (flags & FLAG_S) n_cnt++;
    } else {
      n_cnt = 0;
      new_line_flag = FALSE;
      printf("%c", ch);
    }
  }
  fclose(fp);
  return OK;
}

int parse_args(int argc, char **argv, unsigned int *flags) {
  int getopt_result = 0;
  int result_code;
  struct option long_options[] = {{"number", 0, 0, 'n'},
                                  {"squeeze-blank", 0, 0, 's'},
                                  {"number-nonblank", 0, 0, 'b'},
                                  {0, 0, 0, 0}};
  while (getopt_result > -1) {
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
    if (*flags & FLAG_N) {
      *flags &= ~FLAG_N;
    }
  } else if (getopt_result == 'e') {
    *flags |= FLAG_V;
    *flags |= FLAG_E;
  } else if (getopt_result == 'E') {
    *flags |= FLAG_E;
  } else if (getopt_result == 'n') {
    if (!(*flags & FLAG_B)) {
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

void print_arg_error() { fprintf(stderr, "usage: cat [-benstv] [file ...]\n"); }

void print_file_error(char *file_name) {
  fprintf(stderr, "s21_cat: %s: No such file or directory\n", file_name);
}
