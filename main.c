#include "simple_shell.h"

/**
 * DisplayedPrompt - Display the custom shell prompt
 * @src: src.
 * Prints the custom shell prompt
 * including the shell name and the prompt symbol.
 * Utilizes ANSI color codes for shell name
 * and prompt symbol coloring.
 */
void DisplayedPrompt(t_container *src)
{
	write(1, ANSI_COLOR_GRAY, _strlen(ANSI_COLOR_GRAY));
	write(1, "┌─", 7);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, ANSI_COLOR_CYAN, _strlen(ANSI_COLOR_CYAN));
	write(1, "simple", 7);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, ANSI_COLOR_GRAY, _strlen(ANSI_COLOR_GRAY));
	write(1, "─", 4);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, ANSI_COLOR_CYAN, _strlen(ANSI_COLOR_CYAN));
	write(1, "shell", 6);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, ANSI_COLOR_GRAY, _strlen(ANSI_COLOR_GRAY));
	write(1, "─[", 5);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, ANSI_COLOR_MAGENTA, _strlen(ANSI_COLOR_MAGENTA));
	write(1, src->PWD, _strlen(src->PWD));
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, "]\n╰─$ ", 11);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
}

/**
 * __ - Process file content if it's a regular non-executable file
 * @src: Pointer to the container struct
 * @fd: File descriptor of the file to process
 * @fileName: Name of the file to process
 *
 * This function checks if the given file is a regular non-executable file.
 * If so, it reads the content line by line using _getline, splits the lines
 * into arguments, and processes each command line. After processing, it frees
 * resources and exits with the current exit status.
 */
void __(t_container *src, int fd, char *fileName)
{
	struct stat file_info;

	stat(fileName, &file_info);
	if (S_ISREG(file_info.st_mode)
		&& !(file_info.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
	{
		src->fdLine = NULL;
		while ((src->fdLine = _getline(fd)))
		{
			src->is_fd = 1;
			src->arg = NULL;
			split_cmd_line(src->fdLine, src);
			free(src->fdLine);
		}
		close(fd);
		_free(src->alias.name, NULL, 1);
		_free(src->alias.value, NULL, 1);
		_free(src->env, NULL, 1);
		exit(src->exit_status);
	}
}

/**
 * __filename_input - Processes commands from a file and executes them
 * @argv: Pointer to the shell container
 * @fd: String containing the filename to read commands from
 *
 * This function opens the specified file and reads commands from it line
 * by line.
 * Each command line is processed and executed. The shell container's state may
 * change as a result of executing commands from the file.
 * Return: -1.
 */
int __filename_input(char **argv, int fd)
{
	if (fd < 0)
	{
		if (errno == ENOENT)
		{
			write(2, argv[0], _strlen(argv[0]));
			write(2, ": 0: Can't open ", 17);
			write(2, argv[1], _strlen(argv[1]));
			write(2, "\n", 1);
			exit(127);
		}
		else if (errno == EACCES)
			exit(126);
		else
			return (1);
	}
	return (0);
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
	int fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		__filename_input(argv, fd);
		__var_init(&src, argc, argv);
		__(&src, fd, argv[1]);
	}
	__var_init(&src, argc, argv);
	while (TRUE)
	{
		src.mainLine = NULL;
		src.arg = NULL;
		if (isatty(STDIN_FILENO))
			DisplayedPrompt(&src);
		src.mainLine = _getline(STDIN_FILENO);
		if (!src.mainLine)
		{
			__main_free(&src, MAIN);
			exit(src.exit_status);
		}
		split_cmd_line(src.mainLine, &src);
		free(src.mainLine);
	}
}
