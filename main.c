#include "simple_shell.h"

void __filename_input(t_container *src, char *line)
{
	int fd = -1;
	char **tmp;

	tmp = strtow(line, ' ');
	__new_line_sanitizer(tmp[0]);
	if (_strcmp(tmp[0], ".") && _strcmp(tmp[0], "..") && __fd_status(tmp[0]))
		fd = open(tmp[0], O_RDONLY);
	if (fd > 0)
	{
		free(line);
		line = NULL;
		_free(tmp, NULL, 1);
		line = _getline(fd);
		while (line)
		{
			split_cmd_line(line, src);
			free(line);
			line = _getline(fd);
		}
		close(fd);
		__main_free(src);
		exit(0);
	}
	_free(tmp, NULL, 1);
}

/**
 * main - Simple shell main function
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * This function implements a simple shell. It repeatedly
 * prompts the user for input,
 * attempts to execute the provided command using the SortCmdType
 * function, and waits
 * for the child process to finish. It also handles memory
 * allocation and freeing for
 * the input buffer.
 * Return: .....
 */
int main(int argc, char **argv)
{
	t_container src;
	char *line;

	__var_init(&src, argc, argv);
	set_env(&src);
	while (TRUE)
	{
		write(1, "simple_shell$> ", 15);
		line = _getline(STDIN_FILENO);
		if (!line)
		{
			__main_free(&src);
			exit(0);
		}
		/* read from fd */
		__filename_input(&src, line);
		/* end fd */
		split_cmd_line(line, &src);
		free(line);
	}
}
