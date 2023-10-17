#include "main.h"
/**
 * read_ln - read input string
 * @i_eof: return value for get_ln function
 * Return: string
 */
char *read_ln(int *i_eof)
{
	char *input_str = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input_str, &bufsize, stdin);

	return (input_str);
}
