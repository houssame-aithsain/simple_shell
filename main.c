#include "simple_shell.h"

/**
 * main - Simple shell main function
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * This function implements a simple shell. It repeatedly
 * prompts the user for input,
 * attempts to execute the provided command using the ft_execve
 * function, and waits
 * for the child process to finish. It also handles memory
 * allocation and freeing for
 * the input buffer.
 * Return: .....
 */
int main(int argc, char **argv)
{
	size_t n = 0;
	char *line;
	int read;

	(void)argc;
	line = NULL;
	while (TRUE)
	{
		write(1, "simple_shell$> ", 15);
		read = getline(&line, &n, stdin);
		if (read == -1)
		{
			free(line);
			exit(0);
		}
		if (!strncmp("exit", line, 4))
			exit(0);
		ft_execve(line, argv);
	}
}
