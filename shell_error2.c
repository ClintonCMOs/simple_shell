#include "main.h"
/**
 * handle_env_err - The function handle's error info for envronment.
 * @shell_dt: shell's data
 * Return: An error info
 */
char *handle_env_err(sh_dt *shell_dt)
{
	int string_length;
	char *error;
	char *info;
	char *string_ver;

	string_ver = itoa_c(shell_dt->cmd_count);
	info = ": Not in a position to modify environment\n";
	string_length = str_ln(shell_dt->avg[0]) + str_ln(string_ver);
	string_length += str_ln(shell_dt->argum[0]) + str_ln(info) + 4;
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
	string_cat(error, info);
	string_cat(error, "\0");
	free(string_ver);
	return (error);
}
/**
 * handle_path_126_err - handles error for denied permission in path
 * @shell_dt: shell's data
 * Return: error information
 */
char *handle_path_126_err(sh_dt *shell_dt)
{
	int string_length;
	char *string_ver;
	char *error;

	string_ver = itoa_c(shell_dt->cmd_count);
	string_length = str_ln(shell_dt->avg[0]) + str_ln(string_ver);
	string_length += str_ln(shell_dt->argum[0]) + 24;
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
	string_cat(error, ": Access denied\n");
	string_cat(error, "\0");
	free(string_ver);
	return (error);
}
