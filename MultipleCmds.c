#include "simple_shell.h"

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

	mc_arg = NULL;
	while (src->line[*i])
	{
		if (!_strncmp(*i + src->line, "&&", 2))
		{
			mc_arg = strtow(src->line, '&');
			src->op = AND_CMDS;
			break;
		}
		if (!_strncmp(*i + src->line, "||", 2))
		{
			mc_arg = strtow(src->line, '|');
			src->op = OR_CMDS;
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
int	is_multiple_cmds(t_container *src)
{
	int i = 0, p = 0;

	src->op = 0;
	src->mc_arg = __GetExecuteMCmds(src, &i);
	if (!src->line[i])
		SortCmdType(src->line, src);
	else
	{
		for (; src->mc_arg[p]; p++)
		{
			if (SortCmdType(src->mc_arg[p], src))
				break;
		}
		_free(src->mc_arg, NULL, 1);
	}
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
		if (line && line[i] == '#')
			line[i] = 0;
	}
	if (!line[0])
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

	if (_comments_sanitizer(line))
		return;
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
