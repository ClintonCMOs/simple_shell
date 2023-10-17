#include "main.h"
/**
 * no_comment_c - erases comments for input
 * @in: inpu string
 * Return: input string with no comments
 */
char *no_comment_c(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = realloc_c(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}
/**
 * s_loop - shell's loop
 * @shell_dt: shell's data
 * Return: Nothing
 */
void s_loop(sh_dt *shell_dt)
{
	int loop, i_eof;
	char *input_str;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input_str = read_ln(&i_eof);
		if (i_eof != -1)
		{
			input_str = no_comment_c(input_str);
			if (input_str == NULL)
				continue;

			if (verify_syntax_err(shell_dt, input_str) == 1)
			{
				shell_dt->exe_status = 2;
				free(input_str);
				continue;
			}
			input_str = replace_variable(input_str, shell_dt);
			loop = split_instructions(shell_dt, input_str);
			shell_dt->cmd_count += 1;
			free(input_str);
		}
		else
		{
			loop = 0;
			free(input_str);
		}
	}
}
