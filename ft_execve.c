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

char *check_PATH(char *cmd)
{
	char *path, **token, *cmd_path;
	int i = 0, c = -1;

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
		cmd_path = get_join_path_cmd(token[c], cmd);
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

void execute(char *path, char **arg)
{
	execve(path, arg, environ);
	_free(arg, path, -1);
	exit(-1);
}

/**
 * _execve - Execute a command using execve
 * @line: Path to the command
 * @argv: Argument vector containing the command
 *
 * This function attempts to execute the specified command
 * using the execve system call.
 * If the execution fails, it prints an error message indicating
 * that the command was not found.
 * It then exits with a status of -1.
 */
void _execve(char *line, char **argv)
{
	int ps_id;
	char **arg;
	char *path, *cmd_path;

	if (_strlen(line) > 1)
		line[_strlen(line) - 1] = 0;
	arg = strtow(line, ' ');
	path = malloc(_strlen(arg[0]) + 1);
	_strcpy(path, arg[0]);
	cmd_extracter(arg[0]);

	if ((cmd_path = check_PATH(arg[0])))
	{
		ps_id = fork();
		if (!ps_id)
			execute(cmd_path, arg);
	}
	else if (!builtin(line, arg))
	{
		write(1, argv[0], _strlen(argv[0]));
		write(1, ": No such file or directory\n", 28);
	}
	if (ps_id)
		waitpid(ps_id, NULL, 0);
	free(cmd_path);
	_free(arg, path, -1);
	setenv("a", "hello", 0);
}