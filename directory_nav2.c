#include "main.h"

/**
 * cd_shell_c - changes current directory
 * @shell_dt: data relevant environ
 * Return: 1 on success
 */
int cd_shell_c(sh_dt *shell_dt)
{
	char *dir;
	int home_1, home_2, is_dash;

	dir = shell_dt->argum[1];

	if (dir != NULL)
	{
		home_1 = string_cmp("$HOME", dir);
		home_2 = string_cmp("~", dir);
		is_dash = string_cmp("--", dir);
	}

	if (dir == NULL || !home_1 || !home_2 || !is_dash)
	{
		cd_homedir(shell_dt);
		return (1);
	}

	if (string_cmp("-", dir) == 0)
	{
		cd_prevdir(shell_dt);
		return (1);
	}

	if (string_cmp(".", dir) == 0 || string_cmp("..", dir) == 0)
	{
		cd_currentdir(shell_dt);
		return (1);
	}

	cd_dir(shell_dt);

	return (1);
}
