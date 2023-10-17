#include "main.h"

/**
 * exe_ln - A function to find builtins and commands
 * @shell_dt: data relevant (argum)
 * Return: 1 on success.
 */
int exe_ln(sh_dt *shell_dt)
{
	int (*builtin)(sh_dt *shell_dt);

	if (shell_dt->argum[0] == NULL)
		return (1);

	builtin = get_inbuilt(shell_dt->argum[0]);

	if (builtin != NULL)
		return (builtin(shell_dt));

	return (execute_cmd(shell_dt));
}
/**
 * shell_c_exit - A function to exit the shell
 * @shell_dt: exe_status and argum data
 * Return: 0 on success.
 */
int shell_c_exit(sh_dt *shell_dt)
{
	unsigned int u_status;
	int is_digit;
	int str_len;
	int big_number;

	if (shell_dt->argum[1] != NULL)
	{
		u_status = shell_atoi(shell_dt->argum[1]);
		is_digit = if_digit(shell_dt->argum[1]);
		str_len = str_ln(shell_dt->argum[1]);
		big_number = u_status > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			handle_get_err(shell_dt, 2);
			shell_dt->exe_status = 2;
			return (1);
		}
		shell_dt->exe_status = (u_status % 256);
	}
	return (0);
}
