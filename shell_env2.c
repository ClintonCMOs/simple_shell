#include "main.h"
/**
  *info_cpy - The function that copies information
  *		to create new envrionment or alis.
  *
  *@name: The name of the envrionment or alias.
  *
  *@value: The value assigned to envrionment or alias
  *
  *Return: new environment or alias
  */
char *info_cpy(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = str_ln(name);
	len_value = str_ln(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	string_cpy(new, name);
	string_cat(new, "=");
	string_cat(new, value);
	string_cat(new, "\0");
	return (new);
}
/**
  *environ_set - The function sets an environment variable
  *
  *@name: The name assigned to the environment variable
  *
  *@value: The value given to environment variable
  *
  *@shell_dt: Environment's data structure.
  *
  *Return: Nothing on success
  */
void environ_set(char *name, char *value, sh_dt *shell_dt)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; shell_dt->s_env[i]; i++)
	{
		var_env = string_dup(shell_dt->s_env[i]);
		name_env = strtok_c(var_env, "=");
		if (string_cmp(name_env, name) == 0)
		{
			free(shell_dt->s_env[i]);
			shell_dt->s_env[i] = info_cpy(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}
	shell_dt->s_env = realloc_dp_c(shell_dt->s_env, i, sizeof(char *) * (i + 2));
	shell_dt->s_env[i] = info_cpy(name, value);
	shell_dt->s_env[i + 1] = NULL;
}

/**
  *shell_setenv - The function sets evironment variable.
  *
  *@shell_dt: data revelevant to shell
  *
  *Return: 1 if all is okay
  */
int shell_setenv(sh_dt *shell_dt)
{

	if (shell_dt->argum[1] == NULL || shell_dt->argum[2] == NULL)
	{
		handle_get_err(shell_dt, -1);
		return (1);
	}
	environ_set(shell_dt->argum[1], shell_dt->argum[2], shell_dt);
	return (1);
}

/**
  *shell_unsetenv - unsets the environment variable
  *
  *@shell_dt: shell's data
  *
  *Return: 1 on success.
  */
int shell_unsetenv(sh_dt *shell_dt)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (shell_dt->argum[1] == NULL)
	{
		handle_get_err(shell_dt, -1);
		return (1);
	}
	k = -1;
	for (i = 0; shell_dt->s_env[i]; i++)
	{
		var_env = string_dup(shell_dt->s_env[i]);
		name_env = strtok_c(var_env, "=");
		if (string_cmp(name_env, shell_dt->argum[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		handle_get_err(shell_dt, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; shell_dt->s_env[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = shell_dt->s_env[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(shell_dt->s_env[k]);
	free(shell_dt->s_env);
	shell_dt->s_env = realloc_environ;
	return (1);
}
