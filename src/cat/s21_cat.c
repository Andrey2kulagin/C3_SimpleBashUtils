#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void b_flag(char *input_str, int i);
void n_flag(char *input_str, int i);
void e_flag(char *input_str, int is_E);
void file_open(char filename[100], char *flag);
int output_str(char *input_str);
void s_flag(char *input_str, int i);
int is_not_empty(char *input_str);
void t_flag(char *input_str, int is_T);
void get_params(int argc, char *argv[], char flag[], char *files[],
                int flags_files_count[]);
int print_nonprt_str(char *input_str);
void print_nonprt_symb(char c);
void flag_logic(char *flag, char *input_str, int is_new_file);
void gen_edit_str(int j, char out_str[]);

int main(int argc, char *argv[]) {
  int flags_files_count[2] = {0, 0};
  char flag[10];
  char *files[argc];
  get_params(argc, argv, flag, files, flags_files_count);
  for (int i = 0; i < flags_files_count[1]; i++) {
    file_open(files[i], flag);
  }
  return 0;
}

void get_params(int argc, char *argv[], char flag[], char *files[],
                int flags_files_count[]) {
  int files_index = 0;
  if (argv[1][0] == '-') {
    strcpy(flag, argv[1]);
  } else {
    strcpy(flag, "-p\0");
  }
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      files[files_index] = argv[i];
      files_index++;
    }
    flags_files_count[1] = files_index;
  }
}
void file_open(char filename[100], char *flag) {
  int is_new_file = 1;
  char *input_str;
  char *tmp = malloc(sizeof(char));
  if (tmp != NULL) {
    input_str = tmp;
  }
  FILE *fin;
  fin = fopen(filename, "r");
  if (fin) {
    int i = 0;
    char ch;
    while (1 == 1) {
      ch = fgetc(fin);
      if ((ch == '\n') || (ch == EOF)) {
        tmp = realloc(input_str, sizeof(char) * (i + 1));
        if (tmp != NULL) {
          input_str = tmp;
        }
        input_str[i] = ch;
        flag_logic(flag, input_str, is_new_file);
        is_new_file = 0;
        i = 0;
        free(input_str);
        if ((ch == EOF)) {
          fclose(fin);
          break;
        }
        tmp = malloc(sizeof(char));
        if (tmp != NULL) {
          input_str = tmp;
        }

      } else {
        tmp = realloc(input_str, sizeof(char) * (i + 1));
        if (tmp != NULL) {
          input_str = tmp;
        }
        input_str[i] = ch;
        i++;
      }
    }
  } else {
    free(input_str);
    fprintf(stderr, "cat: %s: No such file or directory", filename);
  }
}
void flag_logic(char *flag, char *input_str, int is_new_file) {
  if (!strcmp(flag, "-e")) {
    e_flag(input_str, 0);
  }
  if (!strcmp(flag, "-E")) {
    e_flag(input_str, 1);
  }
  if ((!strcmp(flag, "-b")) || (!strcmp(flag, "--number-nonblank"))) {
    b_flag(input_str, is_new_file);
  }
  if ((!strcmp(flag, "-n")) || (!strcmp(flag, "--number"))) {
    n_flag(input_str, is_new_file);
  }
  if ((!strcmp(flag, "-s")) || (!strcmp(flag, "--squeeze-blank"))) {
    s_flag(input_str, is_new_file);
  }
  if (!strcmp(flag, "-t")) {
    t_flag(input_str, 0);
  }
  if (!strcmp(flag, "-T")) {
    t_flag(input_str, 1);
  }
  if (!strcmp(flag, "-p")) {
    if (!output_str(input_str)) {
      printf("\n");
    }
  }
}
int is_not_empty(char *input_str) {
  int i = 0;
  int flag = 0;
  if (input_str[i] != '\n' && input_str[i] != EOF) {
    flag = 1;
  }
  return flag;
}

void b_flag(char *input_str, int is_new_file) {
  char edit_str[150];
  static int j = 1;
  if (is_new_file == 1) {
    j = 1;
  }
  if (is_not_empty(input_str) != 0) {
    gen_edit_str(j, edit_str);
    printf("%s%d\t", edit_str, j);
    j++;
  }
  if (!output_str(input_str)) {
    printf("\n");
  }
}
int output_str(char *input_str) {
  int i = 0;
  while ((input_str[i] != '\n') && (input_str[i] != EOF)) {
    printf("%c", input_str[i]);
    i++;
  }
  return input_str[i] == EOF;
}

void e_flag(char *input_str, int is_E) {
  if (!is_E) {
    if (!print_nonprt_str(input_str)) {
      printf("$\n");
    }
  } else {
    if (!output_str(input_str)) {
      printf("$\n");
    }
  }
}

void n_flag(char *input_str, int is_new_file) {
  static int j = 1;
  char edit_str[200];
  if (is_new_file == 1) {
    j = 1;
  }
  gen_edit_str(j, edit_str);
  if (input_str[0] != EOF) {
    printf("%s%d\t", edit_str, j);
  }
  if (!output_str(input_str)) {
    printf("\n");
  }
  j++;
}

void s_flag(char *input_str, int is_new_file) {
  static int is_previous_not_empty = 1;
  if (is_new_file) {
    is_previous_not_empty = 1;
  }
  if ((is_previous_not_empty) ||
      ((is_previous_not_empty == 0) && is_not_empty(input_str) == 1)) {
    if (!output_str(input_str)) {
      printf("\n");
    }
  }
  is_previous_not_empty = is_not_empty(input_str);
}

void t_flag(char *input_str, int is_T) {
  int i = 0;
  while (input_str[i] != '\n' && input_str[i] != EOF) {
    if (input_str[i] == '\t') {
      printf("^I");
    } else {
      if (!is_T) {
        print_nonprt_symb(input_str[i]);
      } else {
        printf("%c", input_str[i]);
      }
    }
    i++;
  }
  if (input_str[i] != EOF) {
    printf("\n");
  }
}

int print_nonprt_str(char *input_str) {
  int i = 0;
  while ((input_str[i] != '\n') && input_str[i] != EOF) {
    char c = input_str[i];
    print_nonprt_symb(c);
    i++;
  }
  return input_str[i] == EOF;
}
void print_nonprt_symb(char c) {
  if (c < -96) {
    printf("M-^%c", c + 192);
  } else if (c < 0) {
    printf("M-%c", c + 128);
  } else if (c == 9 || c == 10) {
    printf("%c", c);
  } else if (c < 32) {
    printf("^%c", c + 64);
  } else if (c < 127) {
    printf("%c", c);
  } else {
    printf("^?");
  }
}

void gen_edit_str(int j, char out_str[]) {
  if (j < 10) {
    strcpy(out_str, "     \0");
  }
  if (100 > j && j >= 10) {
    strcpy(out_str, "    \0");
  }
  if (100 <= j && j <= 999) {
    strcpy(out_str, "   \0");
  }
  if (1000 <= j && j <= 9999) {
    strcpy(out_str, "  \0");
  }
  if (10000 <= j && j <= 99999) {
    strcpy(out_str, " \0");
  }
  if (j >= 100000) {
    strcpy(out_str, " \0");
  }
}