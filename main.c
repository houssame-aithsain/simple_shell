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
 * __filename_input - Processes commands from a file and executes them
 * @src: Pointer to the shell container
 * @fileName: String containing the filename to read commands from
 *
 * This function opens the specified file and reads commands from it line
 * by line.
 * Each command line is processed and executed. The shell container's state may
 * change as a result of executing commands from the file.
 * Return: -1.
 */
int __filename_input(t_container *src, char *fileName)
{
	struct stat file_info;
	int size;

	src->fd = open(fileName, O_RDONLY);
	if (src->fd < 0)
	{
		if (errno == ENOENT)
			_fileNameError(src, fileName);
		else if (errno == EACCES)
			exit(126);
		else
			return (1);
	}
	if (src->fd > 0)
	{
		if (fstat(src->fd, &file_info))
		{
			close(src->fd);
			return (1);
		}
		size = file_info.st_size;
		if (size < 2)
			return (0);
		src->arg = NULL;
		src->fdLine = NULL;
		while ((src->fdLine = _getline(src->fd)))
		{
			src->is_fd = 1;
			src->arg = NULL;
			split_cmd_line(src->fdLine, src);
			free(src->fdLine);
		}
		close(src->fd);
		__main_free(src, FD);
		exit(src->exit_status);
	}
	return (0);
}

/**
 * main - Simple shell main function
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * @env: .....
 * This function implements a simple shell. It repeatedly
 * prompts the user for input,
 * attempts to execute the provided command using the SortCmdType
 * function, and waits
 * for the child process to finish. It also handles memory
 * allocation and freeing for
 * the input buffer.
 * Return: .....
 */
int main(int argc, char **argv, char **env)
{
	t_container src;

	__var_init(&src, argc, argv, env);
	if (argc == 2)
	{
		if (__filename_input(&src, argv[1]))
		{
			_free(src.env, NULL, 1);
			return (EXIT_FAILURE);
		}
	}
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
	return (EXIT_SUCCESS);
}
