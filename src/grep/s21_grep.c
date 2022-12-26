#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int is_str_fit(char *input_str, char *re, int param);
void file_open(char filename[100], char flag[3], char *re, int is_many_files);
void flag_logic(char *flag, char *input_str, char *re, int is_many_files,
                char *filename, int is_new_file, char ch);
void e_i_v_flag(char *input_str, char *re, int is_many_files, char *filename,
                int param, int is_not_v);
void get_params(int argc, char *argv[], char flag[], char *files[],
                int params_count[], char *re[]);
void c_flag(char *input_str, char *re, int is_many_files, char *filename,
            int is_new_file, char ch);
void l_flag(char *input_str, char *re, char *filename, int is_new_file,
            char ch);
void n_flag(char *input_str, char *re, int is_many_files, char *filename,
            int is_new_file);
void non_arg_err(int files_count);
int main(int argc, char *argv[]) {
  char flag[10];
  char *files[argc];
  int params_count[3] = {0, 0, 0};
  char *re[argc];
  get_params(argc, argv, flag, files, params_count, re);
  int files_count = params_count[1];
  non_arg_err(files_count);
  for (int i = 0; i < files_count; i++) {
    file_open(files[i], flag, re[0], files_count > 1);
  }
}

void file_open(char filename[100], char flag[3], char *re, int is_many_files) {
  FILE *fin;
  fin = fopen(filename, "r");
  int is_new_file = 1;
  char *input_str = NULL;
  char *tmp = malloc(sizeof(char));
  if (tmp != NULL) {
    input_str = tmp;
  }
  if (fin) {
    int i = 0;
    char ch;
    while (1 == 1) {
      ch = fgetc(fin);
      if (ch == '\n' || ch == EOF) {
        tmp = realloc(input_str, sizeof(char) * (i + 1) + 1);
        if (tmp != NULL) {
          input_str = tmp;
        }
        if (ch != EOF) {
          input_str[i] = ch;
        } else {
          if (i > 0) {
            input_str[i] = '\n';
          } else {
            input_str[i] = '\0';
          }
        }
        input_str[i + 1] = '\0';
        flag_logic(flag, input_str, re, is_many_files, filename, is_new_file,
                   ch);
        is_new_file = 0;
        i = 0;
        free(input_str);
        tmp = malloc(sizeof(char));
        if (tmp != NULL) {
          input_str = tmp;
        }
        if (ch == EOF) {
          free(input_str);
          fclose(fin);
          break;
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
    fprintf(stderr, "grep: %s: No such file or directory\n", filename);
  }
}

int is_str_fit(char *input_str, char *re, int param) {
  regex_t myre;
  int err;
  regcomp(&myre, re, param);
  // printf("получилось регкомп\n");
  err = regexec(&myre, input_str, 0, NULL, 0);
  // printf("Сравнили без освобождения памяти\n");
  regfree(&myre);
  // printf("сравнил %s %d\n",input_str, err==0);
  return !err;
}

void flag_logic(char *flag, char *input_str, char *re, int is_many_files,
                char *filename, int is_new_file, char ch) {
  if (!strcmp(flag, "-e")) {
    e_i_v_flag(input_str, re, is_many_files, filename, 0001, 1);
  }
  if (!strcmp(flag, "-i")) {
    // printf("зашел в флаг логик\n");
    e_i_v_flag(input_str, re, is_many_files, filename, 0002, 1);
  }
  if (!strcmp(flag, "-v")) {
    e_i_v_flag(input_str, re, is_many_files, filename, 0001, 0);
  }
  if (!strcmp(flag, "-c")) {
    c_flag(input_str, re, is_many_files, filename, is_new_file, ch);
  }
  if (!strcmp(flag, "-l")) {
    l_flag(input_str, re, filename, is_new_file, ch);
  }
  if (!strcmp(flag, "-n")) {
    n_flag(input_str, re, is_many_files, filename, is_new_file);
  }
}

void e_i_v_flag(char *input_str, char *re, int is_many_files, char *filename,
                int param, int is_not_v) {
  // printf("зашел в функцию флагов\n");
  // printf("%s", input_str);
  if (is_str_fit(input_str, re, param) == is_not_v) {
    if (is_many_files && input_str[0] != '\0') {
      printf("%s:%s", filename, input_str);
    } else {
      printf("%s", input_str);
    }
  }
}

void c_flag(char *input_str, char *re, int is_many_files, char *filename,
            int is_new_file, char ch) {
  static int count = 0;
  if (is_new_file) {
    count = 0;
  }
  if (is_str_fit(input_str, re, 0001)) {
    count++;
  }
  if (ch == EOF) {
    if (is_many_files) {
      printf("%s:%d\n", filename, count);
    } else {
      printf("%d\n", count);
    }
  }
}

void l_flag(char *input_str, char *re, char *filename, int is_new_file,
            char ch) {
  static int flag = 0;
  if (is_new_file) {
    flag = 0;
  }
  if (flag == 0 && is_str_fit(input_str, re, 0001)) {
    flag++;
  }
  if (ch == EOF && (flag) > 0) {
    printf("%s\n", filename);
  }
}

void n_flag(char *input_str, char *re, int is_many_files, char *filename,
            int is_new_file) {
  static int number = 1;
  if (is_new_file) {
    number = 1;
  }
  if (is_str_fit(input_str, re, 0001)) {
    if (is_many_files)
      printf("%s:%d:%s", filename, number, input_str);
    else
      printf("%d:%s", number, input_str);
  }
  number++;
}

void get_params(int argc, char *argv[], char flag[], char *files[],
                int params_count[], char *re[]) {
  int flags_index = 0;
  int re_index = 0;
  int files_index = 0;
  if (argv[1][0] == '-') {
    strcpy(flag, argv[1]);
  } else {
    strcpy(flag, "-e\0");
  }
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      if (re_index == 0) {
        re[re_index] = argv[i];
        re_index++;
        re[re_index] = '\0';
      } else {
        files[files_index] = argv[i];
        files_index++;
      }
    }
  }

  params_count[0] = flags_index;
  params_count[1] = files_index;
  params_count[2] = re_index;
}
void non_arg_err(int files_count) {
  if (files_count == 0) {
    fprintf(stderr, "grep: option requires an argument -- e\n");
    fprintf(stderr,
            "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B "
            "num] [-C[num]]\n");
    fprintf(stderr,
            "        [-e pattern] [-f file] [--binary-files=value] "
            "[--color=when]\n");
    fprintf(stderr,
            "        [--context[=num]] [--directories=action] "
            "[--label] [--line-buffered]\n");
    fprintf(stderr, "        [--null] [pattern] [file ...]");
  }
}