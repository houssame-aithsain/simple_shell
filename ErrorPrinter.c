#include "simple_shell.h"

int is_path(t_container *src)
{
    int i = -1;
    DIR *dir;


    while (src->arg[0] && src->arg[0][++i])
    {
        if (src->arg[0][i] == '/')
        {
            if (dir = opendir(src->arg[0]))
            {
                closedir(dir);
                _cmd_not_found(src, 1);
                return (0);
            }
            else
                return (-8);
        }
    }
    return (-8);
}

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

void _cd_error(t_container *src)
{
    write(2, src->p_name, _strlen(src->p_name));
    write(2, ": ", 2);
    _putnbr(src->cmd_counter);
    write(2, ": ", 2);
    write(2, "cd: can't cd to ", 16);
    write(2, src->arg[1], _strlen(src->arg[1]));
    write(2, "\n", 1);
    src->exit_status = 2;
}

void _cmd_not_found(t_container *src, int flag)
{
    src->exit_status = 127;
    if (!_strcmp(src->arg[0], "..") || flag)
    {
        write(2, src->p_name, _strlen(src->p_name));
        write(2, ": ", 2);
        _putnbr(src->cmd_counter);
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
    _putnbr(src->cmd_counter);
    write(2, ": ", 2);
    write(2, src->path, _strlen(src->path));
    write(2, ": not found", 11);
    write(2, "\n", 1);
}