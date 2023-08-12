#include "simple_shell.h"

/**
 * main - Simple shell main function
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * This function implements a simple shell. It repeatedly
 * prompts the user for input,
 * attempts to execute the provided command using the _execve
 * function, and waits
 * for the child process to finish. It also handles memory
 * allocation and freeing for
 * the input buffer.
 * Return: .....
 */
int main(int argc, char **argv)
{
	char *line;

	(void)argc;
	line = NULL;
	while (TRUE)
	{
		write(1, "simple_shell$> ", 15);
		line = _getline(STDIN_FILENO);
		if (!line)
			exit(0);
		_execve(line, argv);
		free(line);
	}
}
