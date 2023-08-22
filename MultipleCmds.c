#include "simple_shell.h"

/**
 * ex_and_or - Execute AND/OR logic for multiple commands
 * @str: Input string containing multiple commands
 * @src: Pointer to the container struct
 *
 * Executes a sequence of commands separated by '&'
 * characters. Each command
 * is evaluated using SortCmdType, and if an exit status
 * other than 0 is
 * encountered, the function returns with an appropriate exit code.
 *
 * Return: 0 on success, -111 on failure due to exit status
 */
int ex_and_or(char *str, t_container *src)
{
	int count = 0;

	src->and_cmds = strtow(str, '&');
	for (; src->and_cmds && src->and_cmds[count]; count++)
	{
		if (_comments_sanitizer(src->and_cmds[count]))
			continue;
		SortCmdType(src->and_cmds[count], src);
		if (src->exit_status)
		{
			_free(src->and_cmds, NULL, 1);
			return (-111);
		}
	}
	_free(src->and_cmds, NULL, 1);
	return (0);
}

/**
 * __GetExecuteMCmds - Retrieves and classifies multiple command operators
 * @src: Shell container
 * @i: Pointer to the current position in the input line
 *
 * Retrieves and classifies multiple command operators (&& or ||).
 * Returns an array of strings containing the parsed commands.
 * Return: mc_arg.
 */
char **__GetExecuteMCmds(t_container *src, int *i)
{
	char **mc_arg;
	int count = 0;

	mc_arg = NULL;
	src->op = 0;
	while (src->line[*i])
	{
		if (!_strncmp(*i + src->line, "||", 2))
		{
			mc_arg = strtow(src->line, '|');
			break;
		}
		(*i)++;
	}
	return (mc_arg);
}

/**
 * is_multiple_cmds - Determines if the input line contains multiple commands
 * @src: Shell container
 *
 * Analyzes the input line in @src to determine if it multiple commands
 * connected with logical operators. Sets the 'op' field in @src accordingly.
 * Return: 0.
 */
int is_multiple_cmds(t_container *src)
{
	int i = 0, p = 0;

	src->and_cmds = NULL;
	src->mc_arg = __GetExecuteMCmds(src, &i);
	if (!src->line[i])
		ex_and_or(src->line, src);
	else
	{
		for (; src->mc_arg[p]; p++)
		{
			if (ex_and_or(src->mc_arg[p], src))
				continue;
			else
				break;
		}
	}
	_free(src->mc_arg, NULL, 1);
	return (0);
}

/**
 * _comments_sanitizer - Removes comments from a line of input
 * @line: Input line to sanitize
 *
 * Removes comments (lines starting with '#') from @line.
 * Return: -77 if the entire line is a comment, otherwise 0.
 */
int _comments_sanitizer(char *line)
{
	int i = -1;

	while (line[++i])
	{
		if (line[i] == 32 && line[i + 1] == '#')
		{
			line[i + 1] = 0;
			break;
		}
	}
	if (!line[0] || line[0] == '#')
		return (-77);
	return (0);
}

/**
 * split_cmd_line - Splits and processes a line of input into commands
 * @line: Input line to split
 * @src: Shell container
 *
 * Splits @line into separate commands and processes each command.
 */
void split_cmd_line(char *line, t_container *src)
{
	int i = 0;

	src->splitedLines = strtow(line, ';');
	while (src->splitedLines[i])
	{
		src->cmd_counter++;
		src->line = _strdup(src->splitedLines[i]);
		is_multiple_cmds(src);
		free(src->line);
		i++;
	}
	_free(src->splitedLines, NULL, 1);
}
