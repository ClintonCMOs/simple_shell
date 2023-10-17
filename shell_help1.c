#include "main.h"
/**
 * shell_help_env - Assistance info for shell inbuilts
 * Return: Nothing
 */
void shell_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [argum]]\n\t";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "Print shell's environment.\n";
	write(STDOUT_FILENO, help, str_ln(help));
}
/**
 * shell_help_setenv - Assistance for shell set environment
 * Return: no return
 */
void shell_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, str_ln(help));
	help = "Define environment again\n";
	write(STDOUT_FILENO, help, str_ln(help));
}
/**
 * shell_help_unsetenv - Assistance for shell unset environment
 * Return: no return
 */
void shell_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "Eliminate entry form env\n";
	write(STDOUT_FILENO, help, str_ln(help));
}


/**
 * shell_help_general - Entry point for all assistance
 * Return: Nothing
 */
void shell_help_general(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "Defiened Internally.Type 'help' for list view";
	write(STDOUT_FILENO, help, str_ln(help));
	help = "Type 'help name' to learn more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, str_ln(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, str_ln(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, str_ln(help));
	help = "[argum]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, str_ln(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, str_ln(help));
}
/**
 * shell_help_exit - Assistance for built in exit
 * Return: Nothing
 */
void shell_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "Exits with an exe_status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, str_ln(help));
	help = "status of the last command executed\n";
	write(STDOUT_FILENO, help, str_ln(help));
}
