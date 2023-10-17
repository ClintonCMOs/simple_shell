#include "main.h"

/**
 * free_data - A function to free data struct
 * @shell_dt: data struct
 * Return: no return
 */
void free_data(sh_dt *shell_dt)
{
	unsigned int i;

	for (i = 0; shell_dt->s_env[i]; i++)
	{
		free(shell_dt->s_env[i]);
	}

	free(shell_dt->s_env);
	free(shell_dt->proc_id);
}

/**
 * set_data - A function to Initialize data struct
 * @shell_dt: data struct
 * @avg: arg vector
 * Return: Nothing
 */
void set_data(sh_dt *shell_dt, char **avg)
{
	unsigned int i;

	shell_dt->avg = avg;
	shell_dt->input_str = NULL;
	shell_dt->argum = NULL;
	shell_dt->exe_status = 0;
	shell_dt->cmd_count = 1;

	for (i = 0; environ[i]; i++)
		;

	shell_dt->s_env = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		shell_dt->s_env[i] = string_dup(environ[i]);
	}

	shell_dt->s_env[i] = NULL;
	shell_dt->proc_id = itoa_c(getpid());
}

/**
 * main - Main program entry point
 * @ac: argument count
 * @avg: argument vector
 * Return: 0 if success
 */
int main(int ac, char **avg)
{
	sh_dt shell_dt;
	(void) ac;

	signal(SIGINT, get_interrupt_sig);
	set_data(&shell_dt, avg);
	s_loop(&shell_dt);
	free_data(&shell_dt);
	if (shell_dt.exe_status < 0)
		return (255);
	return (shell_dt.exe_status);
}
