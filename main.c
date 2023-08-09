#include "simple_shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @s: Pointer to the string.
 *
 * Description: This function calculates the length of a string by
 *              iterating through the characters until it reaches
 *              the null terminator ('\0').
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

/**
 * ft_execve - Execute a command using execve
 * @path: Path to the command
 * @argv: Argument vector containing the command
 *
 * This function attempts to execute the specified command
 * using the execve system call.
 * If the execution fails, it prints an error message indicating
 * that the command was not found.
 * It then exits with a status of -1.
 */
void	ft_execve(char *path, char *argv)
{
	char *arr[] = {"ls", NULL};

	if (execve(path, arr, NULL) == -1)
	{
		write(1, argv, _strlen(argv));
		write(1, ": No such file or directory\n", 28);
	}
	exit(-1);
}

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
	int ps_id;

	(void)argc;
	line = NULL;
	ps_id = 1;
	while (TRUE)
	{
		write(1, "simple_shell$> ", 15);
		read = getline(&line, &n, stdin);
		if (read == -1)
			exit(1);
		line[_strlen(line) - 1] = 0;
		ps_id = fork();
		if (!ps_id)
			ft_execve(line, argv[0]);
		if (ps_id)
			waitpid(ps_id, NULL, 0);
		if (line)
			free(line);
		line = NULL;
	}
}
