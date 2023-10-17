#include "main.h"

/**
 * handle_get_err - A function that calls the builtin error commands
 * @shell_dt: data struct that contains args
 * @eval: value of error
 * Return: error
 */
int handle_get_err(sh_dt *shell_dt, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = handle_env_err(shell_dt);
		break;
	case 126:
		error = handle_path_126_err(shell_dt);
		break;
	case 127:
		error = not_found_err(shell_dt);
		break;
	case 2:
		if (string_cmp("exit", shell_dt->argum[0]) == 0)
			error = exit_shell_err(shell_dt);
		else if (string_cmp("cd", shell_dt->argum[0]) == 0)
			error = get_cd_err(shell_dt);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, str_ln(error));
		free(error);
	}

	shell_dt->exe_status = eval;
	return (eval);
}
