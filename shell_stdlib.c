#include "main.h"

/**
 * get_string_length - A function to get the lenght of a number.
 * @n: integer number.
 * Return: Number length.
 */
int get_string_length(int n)
{
	unsigned int num1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		num1 = n * -1;
	}
	else
	{
		num1 = n;
	}
	while (num1 > 9)
	{
		lenght++;
		num1 = num1 / 10;
	}

	return (lenght);
}
/**
 * itoa_c - A function to convert an int into string.
 * @n: type int number
 * Return: Str.
 */
char *itoa_c(int n)
{
	unsigned int num1;
	int lenght = get_string_length(n);
	char *buff;

	buff = malloc(sizeof(char) * (lenght + 1));
	if (buff == 0)
		return (NULL);

	*(buff + lenght) = '\0';

	if (n < 0)
	{
		num1 = n * -1;
		buff[0] = '-';
	}
	else
	{
		num1 = n;
	}

	lenght--;
	do {
		*(buff + lenght) = (num1 % 10) + '0';
		num1 = num1 / 10;
		lenght--;
	}
	while (num1 > 0)
		;
	return (buff);
}

/**
 * shell_atoi - A function to convert a string to an int.
 * @s: input_str
 * Return: integer.
 */
int shell_atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
