#include "main.h"
/**
 * character_swap - swaps | and & for charaters that are not printed
 * @input_str: string input
 * @bool: boolean swap
 * Return: The string that has been swapped.
 */
char *character_swap(char *input_str, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input_str[i]; i++)
		{
			if (input_str[i] == '|')
			{
				if (input_str[i + 1] != '|')
					input_str[i] = 16;
				else
					i++;
			}

			if (input_str[i] == '&')
			{
				if (input_str[i + 1] != '&')
					input_str[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input_str[i]; i++)
		{
			input_str[i] = (input_str[i] == 16 ? '|' : input_str[i]);
			input_str[i] = (input_str[i] == 12 ? '&' : input_str[i]);
		}
	}
	return (input_str);
}

/**
 * append_nodes - add separators in the lists
 * @head_s: head of sep list
 * @head_l: head of command lines list
 * @input_str: string input
 * Return: nothing
 */
void append_nodes(separate_lst **head_s, ln_lst **head_l, char *input_str)
{
	int i;
	char *line;

	input_str = character_swap(input_str, 0);

	for (i = 0; input_str[i]; i++)
	{
		if (input_str[i] == ';')
			append_sep_node_tail(head_s, input_str[i]);

		if (input_str[i] == '|' || input_str[i] == '&')
		{
			append_sep_node_tail(head_s, input_str[i]);
			i++;
		}
	}

	line = strtok_c(input_str, ";|&");
	do {
		line = character_swap(line, 1);
		append_ln_node_tail(head_l, line);
		line = strtok_c(NULL, ";|&");
	} while (line != NULL);

}

/**
 * proc_forward - go to the nxt CLI
 * @list_s: sep list
 * @list_l: command line list
 * @shell_dt: shell's data
 * Return: no return
 */
void proc_forward(separate_lst **list_s, ln_lst **list_l, sh_dt *shell_dt)
{
	int loop_sep;
	separate_lst *ls_s;
	ln_lst *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shell_dt->exe_status == 0)
		{
			if (ls_s->separator_c == '&' || ls_s->separator_c == ';')
				loop_sep = 0;
			if (ls_s->separator_c == '|')
				ls_l = ls_l->nxt, ls_s = ls_s->nxt;
		}
		else
		{
			if (ls_s->separator_c == '|' || ls_s->separator_c == ';')
				loop_sep = 0;
			if (ls_s->separator_c == '&')
				ls_l = ls_l->nxt, ls_s = ls_s->nxt;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->nxt;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_instructions - splits command lines according to separator.
 * @shell_dt: shell's data
 * @input_str: string input
 * Return: 0 on success to exit, else 1 to continue
 */
int split_instructions(sh_dt *shell_dt, char *input_str)
{

	separate_lst *head_s, *list_s;
	ln_lst *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	append_nodes(&head_s, &head_l, input_str);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		shell_dt->input_str = list_l->line;
		shell_dt->argum = split_ln(shell_dt->input_str);
		loop = exe_ln(shell_dt);
		free(shell_dt->argum);

		if (loop == 0)
			break;

		proc_forward(&list_s, &list_l, shell_dt);

		if (list_l != NULL)
			list_l = list_l->nxt;
	}

	empty_sep_lst(&head_s);
	empty_ln_lst(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}
/**
 * split_ln - tokenizes the string input
 * @input_str: input string
 * Return: splitted string
 */
char **split_ln(char *input_str)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": error in allocation\n", 18);
		exit(EXIT_FAILURE);
	}

	token = strtok_c(input_str, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = realloc_dp_c(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": error in allaction\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok_c(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
