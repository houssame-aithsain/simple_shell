#include "simple_shell.h"

void _execute(t_container *src)
{
	execve(src->cmd_path, src->arg, src->env);
	_free(src->arg, src->path, -1);
	exit(1);
}

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
	{
		__filename_input(src, src->arg[0]);
		_cmd_not_found(src, 0);
	}
	if (!__is_cmd_builtin(src, 1))
	{
		free(src->cmd_path);
		_free(src->arg, src->path, -1);
		return (OR_CMDS + AND_CMDS);
	}
	_free(src->arg, src->path, -1);
	free(src->cmd_path);
	return (0);
}

/**
 * SortCmdType - Execute a command using execve
 * @line: Path to the command
 * @src->p_name: Argument vector containing the command
 *
 * This function attempts to execute the specified command
 * using the execve system call.
 * If the execution fails, it prints an error message indicating
 * that the command was not found.
 * It then exits with a status of -1.
 */
int SortCmdType(char *line, t_container *src)
{
	src->is_empty = 0;
	__new_line_sanitizer(line);
	if (__ifEmptyLine(line))
		return (0);
	src->arg = strtow(line, ' ');
	_expand(src);
	if (!is_path(src))
	{
		_free(src->arg, NULL, 1);
		return (0);
	}
	if (src->is_empty)
	{
		src->exit_status = 0;
		_free(src->arg, NULL, 1);
		return (0);
	}
	src->arg = get_join_alias_args(src->arg);
	src->path = _strdup(src->arg[0]);
	cmd_extracter(src->arg[0]);
	is_alias(src);
	if (__CmdOrBuiltin(src))
		return (-99);
	return (0);
}
/*ls -la; ls -la || ls ; echos hello && echo hello; sdf; echo hello*/