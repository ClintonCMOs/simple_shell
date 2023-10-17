#include "main.h"
/**
 * char_repeat - counts char repetitions
 * @input_str: input_str string
 * @i: index_
 * Return: index_ i
 */
int char_repeat(char *input_str, int i)
{
	if (*(input_str - 1) == *input_str)
		return (char_repeat(input_str - 1, i + 1));

	return (i);
}

/**
 * sep_op_err - syntax error finder
 *
 * @input_str: input_str string
 * @i: index
 * @last: last char read
 * Return: error index or 0 when there are none
 * errors
 */
int sep_op_err(char *input_str, int i, char last)
{
	int count;

	count = 0;
	if (*input_str == '\0')
		return (0);

	if (*input_str == ' ' || *input_str == '\t')
		return (sep_op_err(input_str + 1, i + 1, last));

	if (*input_str == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input_str == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = char_repeat(input_str, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input_str == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = char_repeat(input_str, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (sep_op_err(input_str + 1, i + 1, *input_str));
}

/**
 * initial_char - finds index of the first char
 * @input_str: input_str string
 * @i: index
 * Return: 1 if error. 0 otherwise
 */
int initial_char(char *input_str, int *i)
{

	for (*i = 0; input_str[*i]; *i += 1)
	{
		if (input_str[*i] == ' ' || input_str[*i] == '\t')
			continue;

		if (input_str[*i] == ';' || input_str[*i] == '|' || input_str[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * disp_syntax_err - Displays syntax error found
 *
 * @shell_dt: data_structure
 * @input_str: input_str string
 * @i: error index
 * @bool: control msg error
 * Return: no return
 */
void disp_syntax_err(sh_dt *shell_dt, char *input_str, int i, int bool)
{
	char *info, *msg2, *msg3, *error, *cmd_count;
	int string_length;

	if (input_str[i] == ';')
	{
		if (bool == 0)
			info = (input_str[i + 1] == ';' ? ";;" : ";");
		else
			info = (input_str[i - 1] == ';' ? ";;" : ";");
	}

	if (input_str[i] == '|')
		info = (input_str[i + 1] == '|' ? "||" : "|");

	if (input_str[i] == '&')
		info = (input_str[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax errors: \"";
	msg3 = "\" unexpected error\n";
	cmd_count = itoa_c(shell_dt->cmd_count);
	string_length = str_ln(shell_dt->avg[0]) + str_ln(cmd_count);
	string_length += str_ln(info) + str_ln(msg2) + str_ln(msg3) + 2;

	error = malloc(sizeof(char) * (string_length + 1));
	if (error == 0)
	{
		free(cmd_count);
		return;
	}
	string_cpy(error, shell_dt->avg[0]);
	string_cat(error, ": ");
	string_cat(error, cmd_count);
	string_cat(error, msg2);
	string_cat(error, info);
	string_cat(error, msg3);
	string_cat(error, "\0");

	write(STDERR_FILENO, error, string_length);
	free(error);
	free(cmd_count);
}

/**
 * verify_syntax_err - function to intermediate function
 * find and print a syntax error
 *
 * @shell_dt: data structure
 * @input_str: input_str string
 * Return: 1 if error. 0 in other case
 */
int verify_syntax_err(sh_dt *shell_dt, char *input_str)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = initial_char(input_str, &begin);
	if (f_char == -1)
	{
		disp_syntax_err(shell_dt, input_str, begin, 0);
		return (1);
	}

	i = sep_op_err(input_str + begin, 0, *(input_str + begin));
	if (i != 0)
	{
		disp_syntax_err(shell_dt, input_str, begin + i, 1);
		return (1);
	}

	return (0);
}
