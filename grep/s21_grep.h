//
// Created by Manhunte on 03.02.2024.
//

#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLAG_I (1 << 0)
#define FLAG_V (1 << 1)
#define FLAG_C (1 << 2)
#define FLAG_L (1 << 3)
#define FLAG_N (1 << 4)
#define FLAG_H (1 << 5)
#define FLAG_S (1 << 6)
#define FLAG_O (1 << 7)
#define SINGLE_FILE (1 << 8)
#define IS_FLAG_I(flag) (flag & FLAG_I)
#define IS_FLAG_V(flag) (flag & FLAG_V)
#define IS_FLAG_C(flag) (flag & FLAG_C)
#define IS_FLAG_L(flag) (flag & FLAG_L)
#define IS_FLAG_N(flag) (flag & FLAG_N)
#define IS_FLAG_H(flag) (flag & FLAG_H)
#define IS_FLAG_S(flag) (flag & FLAG_S)
#define IS_FLAG_O(flag) (flag & FLAG_O)
#define IS_SINGLE_FILE(flag) (flag & SINGLE_FILE)
#define TRUE 1
#define FALSE 0

typedef struct templates {
  char *tpl;
  struct templates *next;
} LIST;

enum { OK, FLAG_ERROR, FILE_ERROR, TEMPLATE_ERROR, MEMORY_ERROR };

int parse_args(int argc, char **argv, unsigned int *flags, LIST **templates);
int process_flags(unsigned int *flags, int getopt_result, LIST **templates);
int process_e_flag(char *template_str, LIST **templates);
int process_f_flag(char *file_name, LIST **templates);
int add_str_to_templates(char *str, LIST **templates);
void process_files(char *file_name, unsigned int flags, LIST *templates);
LIST *process_line(char *checked_line, unsigned int flags, LIST *templates);
LIST *process_v_flag(unsigned int flags, const char *checked_line, LIST *tokens);
int process_l_flag(unsigned int flags, int token_line_cnt, const LIST *tokens);
LIST *process_o_flag(const char *checked_line, LIST *templates,
                     regmatch_t *regmatch, int cflags, regex_t *reg,
                     int match_res, LIST *founded_list, size_t *offset);
LIST *reverse_list(LIST *head);

LIST *add_node(LIST *head, char *template);
void free_list(LIST *head);

void line_print(char const *file_name, char *str, int cnt,
                       unsigned int flags);
void flag_lc_print(char *str, int line_cnt, unsigned int flags);

void print_arg_error();
void print_file_error(char *file_name);
void print_tokens(const char *file_name, unsigned int flags, int file_line_cnt, LIST *head_tokens);
#endif  // SRC_GREP_S21_GREP_H_
