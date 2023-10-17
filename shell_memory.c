#include "main.h"
/**
 * copy_mem - copies memory for void pointers
 * @new_pointer: dest pointer
 * @ptr: The source pointer.
 * @size: size of the new pointer.
 * Return: no return.
 */
void copy_mem(void *new_pointer, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_new_pointer = (char *)new_pointer;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_new_pointer[i] = char_ptr[i];
}

/**
 * realloc_c - reallocates a block of memory.
 * @ptr: previous memory pointer
 * @prev_size: size previous allocated ni bytes
 * @new_size: new size in bytes
 * Return: ptr.
 */
void *realloc_c(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	void *new_pointer;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == prev_size)
		return (ptr);

	new_pointer = malloc(new_size);
	if (new_pointer == NULL)
		return (NULL);

	if (new_size < prev_size)
		copy_mem(new_pointer, ptr, new_size);
	else
		copy_mem(new_pointer, ptr, prev_size);

	free(ptr);
	return (new_pointer);
}

/**
 * realloc_dp_c - reallocates a block of memory for block pointer.
 * @ptr: double pointer for previously allocated memory
 * @prev_size: previous size in bytes
 * @new_size: new size in bytes
 * Return: new pointer.
 */
char **realloc_dp_c(char **ptr, unsigned int prev_size, unsigned int new_size)
{
	char **new_pointer;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == prev_size)
		return (ptr);

	new_pointer = malloc(sizeof(char *) * new_size);
	if (new_pointer == NULL)
		return (NULL);

	for (i = 0; i < prev_size; i++)
		new_pointer[i] = ptr[i];

	free(ptr);

	return (new_pointer);
}
