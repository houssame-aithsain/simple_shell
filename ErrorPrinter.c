#include "simple_shell.h"

/**
 * _fileNameError - Display error message for file opening failure
 * @src: Pointer to the container struct
 * @fileName: Name of the file that couldn't be opened
 *
 * This function displays an error message indicating that the specified
 * file couldn't be opened. It then exits the program with an exit status
 * of 127.
 */
void _fileNameError(t_container *src, char *fileName)
{
	write(2, src->p_name, _strlen(src->p_name));
	write(2, ": 0: Can't open ", 17);
	write(2, fileName, _strlen(fileName));
	write(2, "\n", 1);
	exit(127);
}

/**
 * __exit_error - Print error message for invalid exit code
 * @src: Pointer to the container struct
 * @exit_code: The provided exit code value
 * @flag: Flag to indicate specific error condition
 *
 * Prints an error message for an invalid exit code or other
 * related conditions.
 */
void __exit_error(t_container *src, int exit_code, int flag)
{
	src->exit_status = 2;
	if (flag == 1)
	{
		write(2, src->p_name, _strlen(src->p_name));
		write(2, ": ", 2);
		_putnbr(src->cmd_counter, 2);
		write(2, ": ", 2);
		write(2, "exit: Illegal number: ", 22);
		write(2, src->arg[1], _strlen(src->arg[1]));
		write(2, "\n", 1);
		return;
	}
	write(2, src->p_name, _strlen(src->p_name));
	write(2, ": ", 2);
	_putnbr(src->cmd_counter, 2);
	write(2, ": ", 2);
	write(2, "exit: Illegal number: ", 22);
	_putnbr(exit_code, 2);
	write(2, "\n", 1);
}

/**
 * _alias_error - Handles errors related to alias commands.
 * @src: Container holding command and argument data.
 * @len: Length parameter.
 * @i: Index parameter.
 * @flag: Flag indicating the type of error.
 */
void _alias_error(t_container *src, int len, int i, int flag)
{
	if (!flag && src->arg[i][0] == '=')
	{
		src->exit_status = 1;
		write(2, "alias: ", 7);
		write(2, src->arg[i], _strlen(src->arg[i]));
		write(2, " not found\n", 11);
	}
	if (flag && (!src->alias.name || !src->alias.name[len]))
	{
		write(2, "alias: ", 7);
		write(2, src->arg[i], _strlen(src->arg[i]));
		write(2, " not found\n", 11);
		src->exit_status = 1;
	}
}

/**
 * _cd_error - Handles errors related to 'cd' command.
 * @src: Container holding command and argument data.
 */
void _cd_error(t_container *src)
{
	write(2, src->p_name, _strlen(src->p_name));
	write(2, ": ", 2);
	_putnbr(src->cmd_counter, 2);
	write(2, ": ", 2);
	write(2, "cd: can't cd to ", 16);
	write(2, src->arg[1], _strlen(src->arg[1]));
	write(2, "\n", 1);
	src->exit_status = 2;
}

/**
 * _cmd_not_found - Handles 'command not found' errors.
 * @src: Container holding command and argument data.
 * @flag: Flag indicating a specific condition.
 */
void _cmd_not_found(t_container *src, int flag)
{
	src->exit_status = 127;
	if (!_strcmp(src->arg[0], "..") || flag)
	{
		write(2, src->p_name, _strlen(src->p_name));
		write(2, ": ", 2);
		_putnbr(src->cmd_counter, 2);
		write(2, ": ", 2);
		write(2, src->path, _strlen(src->path));
		write(2, ": Permission denied", 19);
		write(2, "\n", 1);
		if (flag)
			src->exit_status = 126;
		return;
	}
	write(2, src->p_name, _strlen(src->p_name));
	write(2, ": ", 2);
	_putnbr(src->cmd_counter, 2);
	write(2, ": ", 2);
	write(2, src->path, _strlen(src->path));
	write(2, ": not found", 11);
	write(2, "\n", 1);
}
