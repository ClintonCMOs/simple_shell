#include "main.h"

/**
 * inspect_env - A function to check if the typed variable is an env variable
 * @h: lead of linked list
 * @in: input_str string
 * @data: data structure
 * Return: Nothing
 */
void inspect_env(variable_r **h, char *in, sh_dt *data)
{
	int row, char_c, j, l_var;
	char **_envr;

	_envr = data->s_env;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, char_c = 0; _envr[row][char_c]; char_c++)
		{
			if (_envr[row][char_c] == '=')
			{
				l_var = str_ln(_envr[row] + char_c + 1);
				append_rvar_node(h, j, _envr[row] + char_c + 1, l_var);
				return;
			}

			if (in[j] == _envr[row][char_c])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	append_rvar_node(h, j, NULL, 0);
}

/**
 * inspect_vars - A function to check if the typed variable is $$ or $
 * @h: lead of the linked list
 * @in: input_str string
 * @st: last exe_status of the Shell
 * @data: data struct
 * Return: Nothing
 */
int inspect_vars(variable_r **h, char *in, char *st, sh_dt *data)
{
	int i, lst, lpd;

	lst = str_ln(st);
	lpd = str_ln(data->proc_id);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				append_rvar_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				append_rvar_node(h, 2, data->proc_id, lpd), i++;
			else if (in[i + 1] == '\n')
				append_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				append_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				append_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				append_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				append_rvar_node(h, 0, NULL, 0);
			else
				inspect_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * mod_input - A function that replaces string into variables
 * @lead: lead of the linked list
 * @input_str: input_str string
 * @new_input: new input string
 * @nlen: new string_length
 * Return: replaced string
 */
char *mod_input(variable_r **lead, char *input_str, char *new_input, int nlen)
{
	variable_r *indx;
	int i, j, k;

	indx = *lead;
	for (j = i = 0; i < nlen; i++)
	{
		if (input_str[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input_str[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->nxt;
		}
		else
		{
			new_input[i] = input_str[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * replace_variable - A function to invoke functions to replace strings
 * @input_str: input_str string
 * @shell_dt: data struct
 * Return: replaced str
 */
char *replace_variable(char *input_str, sh_dt *shell_dt)
{
	variable_r *lead, *indx;
	char *exe_status, *new_input;
	int olen, nlen;

	exe_status = itoa_c(shell_dt->exe_status);
	lead = NULL;

	olen = inspect_vars(&lead, input_str, exe_status, shell_dt);

	if (lead == NULL)
	{
		free(exe_status);
		return (input_str);
	}

	indx = lead;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->nxt;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = mod_input(&lead, input_str, new_input, nlen);

	free(input_str);
	free(exe_status);
	empty_rvariable_lst(&lead);

	return (new_input);
}
