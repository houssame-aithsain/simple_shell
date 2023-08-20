#include "simple_shell.h"

void __filename_input(t_container *src, char *str)
{
	int fd = -1;
	char **tmp;

	tmp = strtow(str, ' ');
	__new_line_sanitizer(tmp[0]);
	if (_strcmp(tmp[0], ".") && _strcmp(tmp[0], "..") && __fd_status(tmp[0]))
		fd = open(tmp[0], O_RDONLY);
	if (fd > 0)
	{
		_free(tmp, NULL, 1);
		__main_free(src, FD);
		src->arg = NULL;
		src->fdLine = NULL;
		while ((src->fdLine = _getline(fd)))
		{
			src->is_fd = 1;
			split_cmd_line(src->fdLine, src);
			free(src->fdLine);
		}
		close(fd);
		_free(src->alias.name, NULL, 1);
		_free(src->alias.value, NULL, 1);
		_free(src->env, NULL, 1);
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

	__var_init(&src, argc, argv);
	while (TRUE)
	{
		src.mainLine = NULL;
		src.arg = NULL;
		write(1, "simple_shell$> ", 15);
		src.mainLine = _getline(STDIN_FILENO);
		if (!src.mainLine)
		{
			__main_free(&src, MAIN);
			exit(0);
		}
		split_cmd_line(src.mainLine, &src);
		free(src.mainLine);
	}
}
