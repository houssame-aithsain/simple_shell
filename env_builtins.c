#include "simple_shell.h"

int unset_var(t_container *src)
{
    int i = 0;

    for (; src->env[i]; i++)
    {
        if (!_strncmp(src->arg[1], src->env[i], _strlen(src->arg[1])))
            break;
    }
    if (!src->env[i])
        return (-11);
    free(src->env[i++]);
    while (src->env[i])
    {
        src->env[i - 1] = malloc(_strlen(src->env[i]) + 1);
        _strcpy(src->env[i - 1], src->env[i]);
        free(src->env[i]);
        i++;
    }
    src->env[i - 1] = NULL;
    return (0);
}

int _unsetenv(t_container *src)
{
    if (!_strcmp(src->path, src->arg[0]))
    {
        if (!_strcmp(src->path, "unsetenv"))
        {
            if (src->arg[1])
            {
                if (unset_var(src))
                {
                    errno = EINVAL;
                    perror("unsetenv");
                }
            }
            return (2);
        }
    }
    return (0);
}

int _setenv(char *name, char *value, t_container *src)
{
    if (!_strcmp(src->path, src->arg[0]))
    {
        if (!_strcmp(src->path, "setenv"))
        {
          if (_var_check(name, value))
            {
                errno = EINVAL;
                perror("setenv");
                return (-1);
            }
                _create_new_var(name, value, src);
            return (5);
        }
    }
    return (0);
}

int _env(t_container *src)
{
    int i = 0;

    if (!_strcmp(src->path, src->arg[0]))
    {
        if (!_strcmp(src->path, "env"))
        {
            for (; src->env[i]; i++)
            {
                write(1, src->env[i], strlen(src->env[i]));
                write(1, "\n", 1);
            }
            return (4);
        }
    }
    return (0);
}