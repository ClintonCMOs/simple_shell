#include "main.h"

/**
 * get_shell_help - A function that retrieves help builtin msgs
 * @shell_dt: argum and input_str data
 * Return: Return 0
*/
int get_shell_help(sh_dt *shell_dt)
{

	if (shell_dt->argum[1] == 0)
		shell_help_general();
	else if (string_cmp(shell_dt->argum[1], "setenv") == 0)
		shell_help_setenv();
	else if (string_cmp(shell_dt->argum[1], "env") == 0)
		shell_help_env();
	else if (string_cmp(shell_dt->argum[1], "unsetenv") == 0)
		shell_help_unsetenv();
	else if (string_cmp(shell_dt->argum[1], "help") == 0)
		shell_help();
	else if (string_cmp(shell_dt->argum[1], "exit") == 0)
		shell_help_exit();
	else if (string_cmp(shell_dt->argum[1], "cd") == 0)
		shell_help_cd();
	else if (string_cmp(shell_dt->argum[1], "alias") == 0)
		shell_help_alias();
	else
		write(STDERR_FILENO, shell_dt->argum[0],
		      str_ln(shell_dt->argum[0]));

	shell_dt->exe_status = 0;
	return (1);
}
