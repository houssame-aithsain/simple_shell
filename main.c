#include "simple_shell.h"

/**
 * DisplayedPrompt - Display the custom shell prompt
 *
 * Prints the custom shell prompt
 * including the shell name and the prompt symbol.
 * Utilizes ANSI color codes for shell name
 * and prompt symbol coloring.
 */
void DisplayedPrompt(void)
{
	write(1, ANSI_COLOR_GRAY, _strlen(ANSI_COLOR_GRAY));
	write(1, "┌──", 6);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, ANSI_COLOR_CYAN, _strlen(ANSI_COLOR_CYAN));
	write(1, "simple_shell$", 14);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
	write(1, ANSI_COLOR_GRAY, _strlen(ANSI_COLOR_GRAY));
	write(1, "──🔰 ", 12);
	write(1, "\n", 1);
	write(1, "╰──# ", 12);
	write(1, ANSI_COLOR_RESET, _strlen(ANSI_COLOR_RESET));
}


/**
 * __filename_input - Processes commands from a file and executes them
 * @src: Pointer to the shell container
 * @str: String containing the filename to read commands from
 *
 * This function opens the specified file and reads commands from it line
 * by line.
 * Each command line is processed and executed. The shell container's state may
 * change as a result of executing commands from the file.
 * Return: -1.
 */
int __filename_input(t_container *src, char *str)
{
	int fd = -1;
	char **tmp;
	DIR *dir;
	struct stat file_stat;

	tmp = strtow(str, ' ');
	__new_line_sanitizer(tmp[0]);
	dir = opendir(tmp[0]);
	if (_strcmp(tmp[0], ".") && _strcmp(tmp[0], "..") && !dir)
		fd = open(tmp[0], O_RDONLY);
	if (dir)
		closedir(dir);
	if (fd > 0 && !stat(tmp[0], &file_stat)
		&& !access(tmp[0], R_OK))
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
	return (-1);
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
		if (isatty(STDIN_FILENO))
			DisplayedPrompt();
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
