#include "main.h"

/**
 * is_current_dir - checks if ":" is in the current dir.
 * @path: type char pointer.
 * @i: type int pointer of index.
 * Return: 1 if path = searchable in the cd, 0 otherwise.
 */
int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * shell_which - locates a command
 * @cmd: command name
 * @s_env: environment variable
 * Return: location of the command.
 */
char *shell_which(char *cmd, char **s_env)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = shell_getenv("PATH", s_env);
	if (path)
	{
		ptr_path = string_dup(path);
		len_cmd = str_ln(cmd);
		token_path = strtok_c(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = str_ln(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			string_cpy(dir, token_path);
			string_cat(dir, "/");
			string_cat(dir, cmd);
			string_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = strtok_c(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_execute_cmd - checks if file is executable
 * @shell_dt: data_structure
 * Return: 0 if non-executable, other number if it does
 */
int is_execute_cmd(sh_dt *shell_dt)
{
	struct stat st;
	int i;
	char *input_str;

	input_str = shell_dt->argum[0];
	for (i = 0; input_str[i]; i++)
	{
		if (input_str[i] == '.')
		{
			if (input_str[i + 1] == '.')
				return (0);
			if (input_str[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input_str[i] == '/' && i != 0)
		{
			if (input_str[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input_str + i, &st) == 0)
	{
		return (i);
	}
	handle_get_err(shell_dt, 127);
	return (-1);
}

/**
 * inspect_cmd_err - verifies if user has permissions to access
 * @dir: destination directory
 * @shell_dt: data structure
 * Return: 1 if there is an error, 0 if not
 */
int inspect_cmd_err(char *dir, sh_dt *shell_dt)
{
	if (dir == NULL)
	{
		handle_get_err(shell_dt, 127);
		return (1);
	}

	if (string_cmp(shell_dt->argum[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			handle_get_err(shell_dt, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shell_dt->argum[0], X_OK) == -1)
		{
			handle_get_err(shell_dt, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_cmd - executes cmd lines
 * @shell_dt: argum and input_str data
 * Return: 1 on success.
 */
int execute_cmd(sh_dt *shell_dt)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_execute_cmd(shell_dt);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = shell_which(shell_dt->argum[0], shell_dt->s_env);
		if (inspect_cmd_err(dir, shell_dt) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = shell_which(shell_dt->argum[0], shell_dt->s_env);
		else
			dir = shell_dt->argum[0];
		execve(dir + exec, shell_dt->argum, shell_dt->s_env);
	}
	else if (pd < 0)
	{
		perror(shell_dt->avg[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell_dt->exe_status = state / 256;
	return (1);
}
