#include "main.h"

/**
 * get_interrupt_sig - Handle the "crtl + c" function call in the prompt
 * @sig_handler: Signal_handler
 */
void get_interrupt_sig(int sig_handler)
{
	(void)sig_handler;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
