#include "main.h"
/**
 * shell_help - Assistance for the builtin help.
 * Return: Nothing
 */
void shell_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "\tDisplay information for inbuilt instructions.\n ";
	write(STDOUT_FILENO, help, str_ln(help));
	help = "Print summaries of inbuilt commands.\n";
	write(STDOUT_FILENO, help, str_ln(help));
}
/**
 * shell_help_alias - Assistance for the builtin alias.
 * Return: no return
 */
void shell_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "\tDefine or print aliases.\n ";
	write(STDOUT_FILENO, help, str_ln(help));
}
/**
 * shell_help_cd - Assistance for inbuiltin cd.
 * Return: no return
 */
void shell_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, str_ln(help));
	help = "\tChange shell's current directory.\n ";
	write(STDOUT_FILENO, help, str_ln(help));
}
