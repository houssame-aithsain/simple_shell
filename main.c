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
int main(int argc, char **argv, char **env)
{
	t_container src;
	char *line;
	(void)argc;

	src.p_name = argv[0];
	if (!getcwd(src.current_p, sizeof(src.current_p)))
		perror("getcwd");
	_strcpy(src.last_p, src.current_p);
	set_env(&src);
	while (TRUE)
	{
		write(1, "simple_shell$> ", 15);
		line = _getline(STDIN_FILENO);
		if (!line)
			exit(0);
		split_cmd_line(line, &src);
		free(line);
	}
}
