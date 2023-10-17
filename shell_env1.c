#include "main.h"
/**
  *cmp_environ_name - Function that compares names of environment
  *			variables with the name that is passed.
  *
  *@nenv: Thane name provided for the environment variable
  *
  *
  *@name: The name passed to the program.
  *
  *Return: 0 if values are not equal, else another value.
  */
int cmp_environ_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}
	return (i + 1);
}

/**
  *shell_getenv - extract shell's environment varibles.
  *
  *@name: The name given to the environment variable.
  *
  *@s_env: shell's evironment variable.
  *
  *Return: The value of shell's environment variable if any,
  *		else returns NULL.
  */
char *shell_getenv(const char *name, char **s_env)
{
	char *ptr_env;
	int i, mov;

	ptr_env = NULL;
	mov = 0;
	for (i = 0; s_env[i]; i++)
	{
		mov = cmp_environ_name(s_env[i], name);
		if (mov)
		{
			ptr_env = s_env[i];
			break;
		}
	}
	return (ptr_env + mov);
}

/**
  *shell_env - The function that displays the evironment variables
  *
  *@shell_dt: relevant data to shell
  *
  *Return: 1 success.
  */
int shell_env(sh_dt *shell_dt)
{
	int i, j;

	for (i = 0; shell_dt->s_env[i]; i++)
	{
		for (j = 0; shell_dt->s_env[i][j]; j++)
			write(STDOUT_FILENO, shell_dt->s_env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shell_dt->exe_status = 0;
	return (1);
}
