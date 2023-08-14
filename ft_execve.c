#include "simple_shell.h"

char *get_join_path_cmd(char *token, char *cmd)
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

char *fix_path(char *path)
{
	int x = 0, i = 0;
	char *f_path;

	f_path = malloc(_strlen(path) + 1);
	for (; path[i]; i++)
	{
		if (i > 4)
			f_path[x++] = path[i];
	}
	f_path[x] = 0;
	return (f_path);
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
	for (; environ[i]; i++)
	{
		if (!_strncmp("PATH", environ[i], 4))
			path = environ[i];
	}
	if (!path)
		return NULL;
	path = fix_path(path);
	token = strtow(path, ':');
	while (token[++c])
	{
		cmd_path = get_join_path_cmd(token[c], src->arg[0]);
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

void _execute(t_container *src)
{
	execve(src->cmd_path, src->arg, src->env);
	_free(src->arg, src->path, -1);
	exit(-1);
}

/**
 * _execve - Execute a command using execve
 * @line: Path to the command
 * @src->p_name: Argument vector containing the command
 *
 * This function attempts to execute the specified command
 * using the execve system call.
 * If the execution fails, it prints an error message indicating
 * that the command was not found.
 * It then exits with a status of -1.
 */
void _execve(t_container *src)
{
	int ps_id;

	if (_strlen(src->line) > 1)
		src->line[_strlen(src->line) - 1] = 0;
	else
		return;
	src->arg = strtow(src->line, ' ');
	src->path = malloc(_strlen(src->arg[0]) + 1);
	_strcpy(src->path, src->arg[0]);
	cmd_extracter(src->arg[0]);

	if ((src->cmd_path = check_PATH(src)) && _strcmp("env", src->arg[0])
		&& _strcmp("/bin/env", src->path))
	{
		ps_id = fork();
		if (!ps_id)
			_execute(src);
	}
	else if (!builtin(src))
	{
		write(1, src->p_name, _strlen(src->p_name));
		write(2, ": No such file or directory\n", 28);
	}
	if (ps_id)
		waitpid(ps_id, NULL, 0);
	free(src->cmd_path);
	_free(src->arg, src->path, -1);
}