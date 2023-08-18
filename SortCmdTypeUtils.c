#include "simple_shell.h"

int __is_cmd_builtin(t_container *src, int flag)
{
	if (!flag)
	{
		if ((src->cmd_path = check_PATH(src)) && _strcmp("env", src->arg[0])
			&& _strcmp("alias", src->arg[0]) && _strcmp(src->arg[0], ".."))
			return (0);
		return (-1);
	}
	if ((!src->exit_status && src->op == OR_CMDS)
		|| (src->exit_status && src->op == AND_CMDS))
			return (0);
	return (-1);
}

char *get_join_cmd_path(char *token, char *cmd)
{
	char *cmd_path;
	int i = 0, c = 0;

	cmd_path = malloc(_strlen(token) + _strlen(cmd) + 2);
	for (; token[i]; i++)
		cmd_path[i] = token[i];
	cmd_path[i++] = '/';
	for (; cmd[c]; c++)
		cmd_path[i++] = cmd[c];
	cmd_path[i] = 0;
	return (cmd_path);
}

char *check_PATH(t_container *src)
{
	char *path, **token, *cmd_path;
	int i = 0, c = -1;

	if (_strcmp(src->path, src->arg[0]))
	{
		if (!access(src->path, F_OK))
			return (_strdup(src->path));
		else
			return (NULL);
	}
	path = NULL;
	for (; src->env[i]; i++)
	{
		if (!_strncmp("PATH", src->env[i], 4))
			path = _strdup(src->env[i]);
	}
	if (!path)
		return NULL;
	_strcpy(path, path + 5);
	token = strtow(path, ':');
	while (token[++c])
	{
		cmd_path = get_join_cmd_path(token[c], src->arg[0]);
		if (!access(cmd_path, F_OK))
		{
			_free(token, path, -1);
			return cmd_path;
		}
		free(cmd_path);
	}
	_free(token, path, -1);
	return (NULL);
}

void cmd_extracter(char *cmd)
{
	char **cmd_ex = strtow(cmd, '/');
	int i = 0;

	while (cmd_ex && cmd_ex[i])
		i++;
	if (i)
		_strcpy(cmd, cmd_ex[i - 1]);
	_free(cmd_ex, NULL, 1);
}

int __ifEmptyLine(char *line)
{
	int i = 0;

	while (line[i] == 32)
		i++;
	if (!line[i])
		return -155;
	return (0);
}
