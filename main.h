#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - structure with data runtime data
 * @avg: arg vector
 * @input_str: user written command line
 * @argum: argum of the command line
 * @exe_status: last exe_status of the shell
 * @cmd_count: lines cmd_count
 * @s_env: shell environment variable
 * @proc_id: shell process ID
 */
typedef struct data
{
	char **avg;
	char *input_str;
	char **argum;
	int exe_status;
	int cmd_count;
	char **s_env;
	char *proc_id;
} sh_dt;

/**
 * struct separate_lst_s - single linked list
 * @separator_c: ; | &
 * @nxt: nxt node
 * Description: single linked list to store separators
 */
typedef struct separate_lst_s
{
	char separator_c;
	struct separate_lst_s *nxt;
} separate_lst;

/**
 * struct ln_lst_s - singly linked list
 * @line: command line
 * @nxt: nxt node
 * Description: list to store command lines
 */
typedef struct ln_lst_s
{
	char *line;
	struct ln_lst_s *nxt;
} ln_lst;

/**
 * struct rvariable_lst - singly linked list
 * @len_var: variable string_length
 * @val: value of the variable
 * @len_val:  value string_length
 * @nxt: nxt node
 * Description: singly linked list for storing var
 */
typedef struct rvariable_lst
{
	int len_var;
	char *val;
	int len_val;
	struct rvariable_lst *nxt;
} variable_r;

/**
 * struct inbuilt_s - Builtin struct for cmd args.
 * @name: The name of the command builtin
 * @f: pointer function to data type.
 */
typedef struct inbuilt_s
{
	char *name;
	int (*f)(sh_dt *shell_dt);
} inbuilt_t;

separate_lst *append_sep_node_tail(separate_lst **lead, char sep);
void empty_sep_lst(separate_lst **lead);
ln_lst *append_ln_node_tail(ln_lst **lead, char *line);
void empty_ln_lst(ln_lst **lead);

variable_r *append_rvar_node(variable_r **lead, int lvar, char *var, int lval);
void empty_rvariable_lst(variable_r **lead);

char *string_cat(char *dest, const char *src);
char *string_cpy(char *dest, char *src);
int string_cmp(char *s1, char *s2);
char *string_chr(char *s, char c);
int string_spn(char *s, char *accept);

void copy_mem(void *new_pointer, const void *ptr, unsigned int size);
void *realloc_c(void *ptr, unsigned int prev_size, unsigned int new_size);
char **realloc_dp_c(char **ptr, unsigned int prev_size, unsigned int new_size);

char *string_dup(const char *s);
int str_ln(const char *s);
int string_cmp_chars(char str[], const char *dlm);
char *strtok_c(char str[], const char *dlm);
int if_digit(const char *s);

void string_reverse(char *s);

int char_repeat(char *input_str, int i);
int sep_op_err(char *input_str, int i, char last);
int initial_char(char *input_str, int *i);
void disp_syntax_err(sh_dt *shell_dt, char *input_str, int i, int bool);
int verify_syntax_err(sh_dt *shell_dt, char *input_str);

char *no_comment_c(char *in);
void s_loop(sh_dt *shell_dt);

char *read_ln(int *i_eof);

char *character_swap(char *input_str, int bool);
void append_nodes(separate_lst **head_s, ln_lst **head_l, char *input_str);
void proc_forward(separate_lst **list_s, ln_lst **list_l, sh_dt *shell_dt);
int split_instructions(sh_dt *shell_dt, char *input_str);
char **split_ln(char *input_str);

void inspect_env(variable_r **h, char *in, sh_dt *data);
int inspect_vars(variable_r **h, char *in, char *st, sh_dt *data);
char *mod_input(variable_r **lead, char *input_str, char *new_input, int nlen);
char *replace_variable(char *input_str, sh_dt *shell_dt);

void get_ln(char **lineptr, size_t *n, char *buff, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *strm);

int exe_ln(sh_dt *shell_dt);

int is_current_dir(char *path, int *i);
char *shell_which(char *cmd, char **s_env);
int is_execute_cmd(sh_dt *shell_dt);
int inspect_cmd_err(char *dir, sh_dt *shell_dt);
int execute_cmd(sh_dt *shell_dt);

char *shell_getenv(const char *name, char **s_env);
int shell_env(sh_dt *shell_dt);

char *info_cpy(char *name, char *value);
void environ_set(char *name, char *value, sh_dt *shell_dt);
int shell_setenv(sh_dt *shell_dt);
int shell_unsetenv(sh_dt *shell_dt);

void cd_currentdir(sh_dt *shell_dt);
void cd_dir(sh_dt *shell_dt);
void cd_prevdir(sh_dt *shell_dt);
void cd_homedir(sh_dt *shell_dt);

int cd_shell_c(sh_dt *shell_dt);

int (*get_inbuilt(char *cmd))(sh_dt *shell_dt);

int shell_c_exit(sh_dt *shell_dt);

int get_string_length(int n);
char *itoa_c(int n);
int shell_atoi(char *s);

char *string_cat_cd(sh_dt *, char *, char *, char *);
char *get_cd_err(sh_dt *shell_dt);
char *not_found_err(sh_dt *shell_dt);
char *exit_shell_err(sh_dt *shell_dt);

char *handle_alias_err(char **argum);
char *handle_env_err(sh_dt *shell_dt);
char *handle_syntax_err(char **argum);
char *handle_permis_err(char **argum);
char *handle_path_126_err(sh_dt *shell_dt);

int handle_get_err(sh_dt *shell_dt, int eval);

void get_interrupt_sig(int sig_handler);

void shell_help_env(void);
void shell_help_setenv(void);
void shell_help_unsetenv(void);
void shell_help_general(void);
void shell_help_exit(void);

void shell_help(void);
void shell_help_alias(void);
void shell_help_cd(void);

int get_shell_help(sh_dt *shell_dt);

#endif
