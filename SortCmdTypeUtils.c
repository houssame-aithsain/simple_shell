#include "simple_shell.h"

/**
 * __is_cmd_builtin - Check if command is built-in or external
 * @src: Pointer to the container struct
 * @flag: Operation flag
 *
 * Determines if the command in 'src' is a built-in command or external
 * command. If 'flag' is 0, checks for specific built-ins or external
 * commands like "env," "alias," and "..". If 'flag' is 1, handles
 * exit status and operation flags.
 *
 * Return: 0 if built-in or external, -1 otherwise
 */
int __is_cmd_builtin(t_container *src, int flag)
{
	if (!flag)
	{
		src->cmd_path = check_PATH(src);
		if (src->cmd_path && _strcmp("env", src->arg[0])
			&& _strcmp("alias", src->arg[0]) && _strcmp(src->arg[0], ".."))
			return (0);
		return (-1);
	}
	if ((!src->exit_status && src->op == OR_CMDS)
		|| (src->exit_status && src->op == AND_CMDS))
		return (0);
	return (-1);
}

/**
 * get_join_cmd_path - Get full command path
 * @token: Token from PATH environment
 * @cmd: Command name
 *
 * Combines 'token' and 'cmd' to create a full command path by appending
 * 'cmd' to 'token' with a "/" separator.
 *
 * Return: Pointer to the concatenated command path
 */
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

/**
 * check_PATH - Check command path in PATH environment
 * @src: Pointer to the container struct
 *
 * Checks the command path in the PATH environment variable by iterating
 * through its tokens and attempting to find the command in those paths.
 *
 * Return: Command path if found, NULL otherwise
 */
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
		return (NULL);
	_strcpy(path, path + 5);
	token = strtow(path, ':');
	while (token[++c])
	{
		cmd_path = get_join_cmd_path(token[c], src->arg[0]);
		if (!access(cmd_path, F_OK))
		{
			_free(token, path, -1);
			return (cmd_path);
		}
		free(cmd_path);
	}
	_free(token, path, -1);
	return (NULL);
}

/**
 * cmd_extracter - Extract command from full path
 * @cmd: Command path
 *
 * Extracts the command name from a full path by tokenizing it using "/"
 * as a delimiter and assigning the last token to 'cmd'.
 */
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


/**
 * __ifEmptyLine - Check if line is empty
 * @line: Input line
 *
 * Checks if 'line' is empty (contains only spaces).
 *
 * Return: -155 if line is empty, 0 otherwise
 */
int __ifEmptyLine(char *line)
{
	int i = 0;

	while (line[i] == 32)
		i++;
	if (!line[i])
		return (-155);
	return (0);
}
