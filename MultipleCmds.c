#include "simple_shell.h"

char **__GetExecuteMCmds(t_container *src, int *i)
{
	char **mc_arg;

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

int	is_multiple_cmds(t_container *src)
{
	char **mc_arg;
	int i = 0, p = 0;

	src->op = 0;
	mc_arg = __GetExecuteMCmds(src, &i);
	if (!src->line[i])
		SortCmdType(src->line, src);
	else
	{
		for (; mc_arg[p]; p++)
		{
			if (SortCmdType(mc_arg[p], src))
				break;
		}
		_free(mc_arg, NULL, 1);
	}
	return (0);  
}

void _comments_sanitizer(char *line)
{
	int i = -1;

	while (line[++i])
	{
		if (line && line[i] == '#')
			line[i] = 0;
	}
}

void split_cmd_line(char *line, t_container *src)
{
	int i = 0;
	char **cmds;

	_comments_sanitizer(line);
	cmds = strtow(line, ';');
	while (cmds[i])
	{
		src->cmd_counter++;
		src->line = malloc(_strlen(cmds[i]) + 1);
		_strcpy(src->line, cmds[i]);
		is_multiple_cmds(src);
		free(src->line);
		i++;
	}
	_free(cmds, NULL, 1);
}
