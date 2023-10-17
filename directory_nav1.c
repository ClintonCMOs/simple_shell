#include "main.h"

/**
 * cd_currentdir - changes to the parent dir
 * @shell_dt: data environ
 *
 * Return: no return
 */
void cd_currentdir(sh_dt *shell_dt)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = string_dup(pwd);
	environ_set("OLDPWD", cp_pwd, shell_dt);
	dir = shell_dt->argum[1];
	if (string_cmp(".", dir) == 0)
	{
		environ_set("PWD", cp_pwd, shell_dt);
		free(cp_pwd);
		return;
	}
	if (string_cmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	string_reverse(cp_strtok_pwd);
	cp_strtok_pwd = strtok_c(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = strtok_c(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			string_reverse(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		environ_set("PWD", cp_strtok_pwd, shell_dt);
	}
	else
	{
		chdir("/");
		environ_set("PWD", "/", shell_dt);
	}
	shell_dt->exe_status = 0;
	free(cp_pwd);
}

/**
 * cd_dir - changes to a directory given by user
 * @shell_dt: data relevant (directories)
 * Return: no return
 */
void cd_dir(sh_dt *shell_dt)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = shell_dt->argum[1];
	if (chdir(dir) == -1)
	{
		handle_get_err(shell_dt, 2);
		return;
	}

	cp_pwd = string_dup(pwd);
	environ_set("OLDPWD", cp_pwd, shell_dt);

	cp_dir = string_dup(dir);
	environ_set("PWD", cp_dir, shell_dt);

	free(cp_pwd);
	free(cp_dir);

	shell_dt->exe_status = 0;

	chdir(dir);
}

/**
 * cd_prevdir - changes to the previous directory
 * @shell_dt: data environ
 * Return: no return
 */
void cd_prevdir(sh_dt *shell_dt)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = string_dup(pwd);

	p_oldpwd = shell_getenv("OLDPWD", shell_dt->s_env);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = string_dup(p_oldpwd);

	environ_set("OLDPWD", cp_pwd, shell_dt);

	if (chdir(cp_oldpwd) == -1)
		environ_set("PWD", cp_pwd, shell_dt);
	else
		environ_set("PWD", cp_oldpwd, shell_dt);

	p_pwd = shell_getenv("PWD", shell_dt->s_env);

	write(STDOUT_FILENO, p_pwd, str_ln(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shell_dt->exe_status = 0;

	chdir(p_pwd);
}

/**
 * cd_homedir - a function that changes to home dir
 *
 * @shell_dt: data environ
 * Return: no return
 */
void cd_homedir(sh_dt *shell_dt)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = string_dup(pwd);

	home = shell_getenv("HOME", shell_dt->s_env);

	if (home == NULL)
	{
		environ_set("OLDPWD", p_pwd, shell_dt);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		handle_get_err(shell_dt, 2);
		free(p_pwd);
		return;
	}

	environ_set("OLDPWD", p_pwd, shell_dt);
	environ_set("PWD", home, shell_dt);
	free(p_pwd);
	shell_dt->exe_status = 0;
}
