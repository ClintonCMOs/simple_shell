#include "main.h"

/**
 * string_cat_cd - function that concatenates cd error info
 * @shell_dt: shell's data
 * @info: information to display
 * @error: error information
 * @string_ver: counter for string.
 * Return: error information
 */
char *string_cat_cd(sh_dt *shell_dt, char *info, char *error, char *string_ver)
{
	char *invalid_flag;

	string_cpy(error, shell_dt->avg[0]);
	string_cat(error, ": ");
	string_cat(error, string_ver);
	string_cat(error, ": ");
	string_cat(error, shell_dt->argum[0]);
	string_cat(error, info);
	if (shell_dt->argum[1][0] == '-')
	{
		invalid_flag = malloc(3);
		invalid_flag[0] = '-';
		invalid_flag[1] = shell_dt->argum[1][1];
		invalid_flag[2] = '\0';
		string_cat(error, invalid_flag);
		free(invalid_flag);
	}
	else
	{
		string_cat(error, shell_dt->argum[1]);
	}

	string_cat(error, "\n");
	string_cat(error, "\0");
	return (error);
}

/**
 * get_cd_err - obtain error information for cd.
 * @shell_dt: shell's data
 * Return: Error information
 */
char *get_cd_err(sh_dt *shell_dt)
{
	int string_length, len_id;
	char *error, *string_ver, *info;

	string_ver = itoa_c(shell_dt->cmd_count);
	if (shell_dt->argum[1][0] == '-')
	{
		info = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		info = ": can't cd to ";
		len_id = str_ln(shell_dt->argum[1]);
	}

	string_length = str_ln(shell_dt->avg[0]) + str_ln(shell_dt->argum[0]);
	string_length += str_ln(string_ver) + str_ln(info) + len_id + 5;
	error = malloc(sizeof(char) * (string_length + 1));

	if (error == 0)
	{
		free(string_ver);
		return (NULL);
	}
	error = string_cat_cd(shell_dt, info, error, string_ver);
	free(string_ver);
	return (error);
}

/**
 * not_found_err - Information for no error
 * @shell_dt: shell's data
 * Return: Error information
 */
char *not_found_err(sh_dt *shell_dt)
{
	int string_length;
	char *error;
	char *string_ver;

	string_ver = itoa_c(shell_dt->cmd_count);
	string_length = str_ln(shell_dt->avg[0]) + str_ln(string_ver);
	string_length += str_ln(shell_dt->argum[0]) + 16;
	error = malloc(sizeof(char) * (string_length + 1));
	if (error == 0)
	{
		free(error);
		free(string_ver);
		return (NULL);
	}
	string_cpy(error, shell_dt->avg[0]);
	string_cat(error, ": ");
	string_cat(error, string_ver);
	string_cat(error, ": ");
	string_cat(error, shell_dt->argum[0]);
	string_cat(error, ": unavailable\n");
	string_cat(error, "\0");
	free(string_ver);
	return (error);
}

/**
 * exit_shell_err - error information for exit
 * @shell_dt: shell's data
 * Return: Error information
 */
char *exit_shell_err(sh_dt *shell_dt)
{
	int string_length;
	char *error;
	char *string_ver;

	string_ver = itoa_c(shell_dt->cmd_count);
	string_length = str_ln(shell_dt->avg[0]) + str_ln(string_ver);
	string_length += str_ln(shell_dt->argum[0]) + str_ln(shell_dt->argum[1]) + 23;
	error = malloc(sizeof(char) * (string_length + 1));
	if (error == 0)
	{
		free(string_ver);
		return (NULL);
	}
	string_cpy(error, shell_dt->avg[0]);
	string_cat(error, ": ");
	string_cat(error, string_ver);
	string_cat(error, ": ");
	string_cat(error, shell_dt->argum[0]);
	string_cat(error, ": Num not allowed: ");
	string_cat(error, shell_dt->argum[1]);
	string_cat(error, "\n\0");
	free(string_ver);
	return (error);
}
