//
// Created by Manhunte on 03.02.2024.
//

#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>

#define FLAG_B (1 << 0)
#define FLAG_E (1 << 1)
#define FLAG_N (1 << 2)
#define FLAG_S (1 << 3)
#define FLAG_T (1 << 4)
#define FLAG_V (1 << 5)
#define IS_FLAG_B(flag) (flag & FLAG_B)
#define IS_FLAG_E(flag) (flag & FLAG_E)
#define IS_FLAG_N(flag) (flag & FLAG_N)
#define IS_FLAG_S(flag) (flag & FLAG_S)
#define IS_FLAG_T(flag) (flag & FLAG_T)
#define IS_FLAG_V(flag) (flag & FLAG_V)
#define TRUE 1
#define FALSE 0

#define IS_SPEC_CHAR(ch) (((ch) >= 0 && (ch) <= 8) || ((ch) >= 11 && (ch) <= 31) || ((ch) >= 127 && (ch) <= 159))
#define IS_TAB_CHAR(ch) (((ch) == '\t'))
#define IS_NL_CHAR(ch) (((ch) == '\n'))

enum { OK, FLAG_ERROR, FILE_ERROR };

int parse_args(int argc, char **argv, unsigned int *flags);
int process_flags(unsigned int *flags, int getopt_result);
int process_files(char *file_name, unsigned int flags);
void print_arg_error();
void print_file_error(char *file_name);

#endif  // SRC_CAT_S21_CAT_H_
