#ifndef SIMPLE_SHELL_SHELL_H_
#define SIMPLE_SHELL_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define ENDOFFILE (-2)
#define EXIT (-3)

/* Global environemnt */
extern char **environ;
/* Global program name */
char *globalProgramName;
/* Global history counter */
int historyCounter;

/**
 * struct list_m - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_m.
 */
typedef struct list_m
{
	char *directory_path;
	struct list_m *next;
} list_t;

/**
 * struct builtin_m - A new struct type defining builtin commands.
 * @name: The globalProgramName of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_m
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_m - A new struct defining alias_list.
 * @name: The globalProgramName of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_m.
 */
typedef struct alias_m
{
	char *name;
	char *value;
	struct alias_m *next;
} alias_t;

/* Global alias linked list */
alias_t *alias_list;

/* Main Helpers */
void sig_handler(int sig);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t get_new_len(char *line);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
void logical_ops(char *line, ssize_t *new_len);
void *_realloc_(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok_(char *line, char *delim);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list_m(list_t *head);
char *_itoa_(int num);

/* Input Helpers */
void handle_line_entered(char **line, ssize_t read);
void replace_variable(char **args, int *exe_ret);
char *get_argmnts(char *line, int *exe_ret);
int call_argmnts(char **args, char **front, int *exe_ret);
int run_argmnts(char **args, char **front, int *exe_ret);
int handle_argmnts(int *exe_ret);
int check_argmnts(char **args);
void free_argmnts(char **args, char **front);
char **replaceAliases(char **args);
int num_len(int num);

/* String functions */
int _str_len_(const char *s);
char *_str_cat_(char *dest, const char *src);
char *_str_n_cat_(char *dest, const char *src, size_t n);
char *_str_cpy_(char *dest, const char *src);
char *_str_chr_(char *s, char c);
int _str_spn_(char *s, char *accept);
int _str_cmp_(char *s1, char *s2);
int _str_n_cmp_(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int shellby_exit(char **args, char **front);
int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int make_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list_m(list_t *head);

void helpAll(void);
void helpAlias(void);
void helpCd(void);
void helpExit(void);
void hhelp(void);
void helpEnv(void);
void helpSetenv(void);
void helpUnsetenv(void);

char *fill_path_dir(char *path);
int procFileCommands(char *file_path, int *exe_ret);
#endif /* SIMPLE_SHELL_SHELL_H_ */
