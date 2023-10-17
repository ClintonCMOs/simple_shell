#include "main.h"
/**
 * append_rvar_node - append variable at the end of var list
 * @lead: head of the linked list.
 * @lvar: length of str.
 * @val: variable value
 * @lval: str length
 * Return: address of the head.
 */
variable_r *append_rvar_node(variable_r **lead, int lvar, char *val, int lval)
{
	variable_r *new, *temp;

	new = malloc(sizeof(variable_r));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->nxt = NULL;
	temp = *lead;
	if (temp == NULL)
	{
		*lead = new;
	}
	else
	{
		while (temp->nxt != NULL)
			temp = temp->nxt;
		temp->nxt = new;
	}

	return (*lead);
}
/**
 * empty_rvariable_lst - empty variable list
 * @lead: head of linked list
 * Return: Nothing
 */
void empty_rvariable_lst(variable_r **lead)
{
	variable_r *temp;
	variable_r *current;

	if (lead != NULL)
	{
		current = *lead;
		while ((temp = current) != NULL)
		{
			current = current->nxt;
			free(temp);
		}
		*lead = NULL;
	}
}
