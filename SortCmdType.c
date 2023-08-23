#include "simple_shell.h"

/**
 * _execute - Execute specified command in the container
 * @src: Pointer to the container struct
 *
 * This function executes the command specified in 'src->cmd_path' with the
 * arguments in 'src->arg' and environment variables in 'src->env' using
 * 'execve'. After execution, memory is freed and the process exits.
 */
void _execute(t_container *src)
{
	execve(src->cmd_path, src->arg, src->env);
	_free(src->arg, src->path, -1);
	exit(1);
}


/**
 * __CmdOrBuiltin - Execute command or built-in
 * @src: Pointer to the container struct
 *
 * This function determines whether the command in 'src' is a built-in or
 * external command. If external, a new process is forked to execute it via
 * 'execve'. Built-in commands are executed using the 'builtins' function.
 * Handles command not found and invalid command path scenarios.
 *
 * Return: Combined operation flag indicating logical OR or AND operations.
 */
int	__CmdOrBuiltin(t_container *src)
{
	int ps_id, ex;

	if (!__is_cmd_builtin(src, 0))
	{
		ps_id = fork();
		if (!ps_id)
			_execute(src);
		waitpid(ps_id, &ex, 0);
		src->exit_status = (((ex) & 0xff00) >> 8);
	}
	else if (!builtins(src))
		_cmd_not_found(src, 0);
	_free(src->arg, src->path, -1);
	free(src->cmd_path);
	return (0);
}

/**
 * SortCmdType - Execute a command using execve
 * @line: Path to the command
 * @src: a struct that is holding the full data.
 * @src->p_name: Argument vector containing the command
 *
 * This function attempts to execute the specified command
 * using the execve system call.
 * If the execution fails, it prints an error message indicating
 * that the command was not found.
 * It then exits with a status of -1.
 * Return: 0 or -99.
 */
int SortCmdType(char *line, t_container *src)
{
	src->is_empty = 0;
	__new_line_sanitizer(line);
	if (__ifEmptyLine(line))
		return (0);
	src->arg = strtow(line, ' ');
	_expand(src);
	src->path = _strdup(src->arg[0]);
	if (!is_path(src))
	{
		_free(src->arg, src->path, -1);
		return (0);
	}
	if (src->is_empty)
	{
		src->exit_status = 0;
		_free(src->arg, src->path, -1);
		return (0);
	}
	src->arg = get_join_alias_args(src->arg);
	cmd_extracter(src->arg[0]);
	AliasLineEnhancer(src);
	if (__CmdOrBuiltin(src))
		return (-99);
	return (0);
}
