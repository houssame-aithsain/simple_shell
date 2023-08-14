#include "simple_shell.h"

void __exit(t_container *src)
{
    if (!_strcmp(src->path, src->arg[0]))
    {
        if (!_strcmp(src->path, "exit"))
        {
            if (src->arg[1])
                exit(_atoi(src->arg[1]));
            else
                exit(0);
        }
    }
}

int _cd(t_container *src)
{
    if (!_strcmp(src->path, src->arg[0]))
    {
        if (!_strcmp(src->path, "cd"))
        {
            if (src->arg[1])
            {
                if (!_strcmp(src->arg[1], "-"))
                {
                    if (chdir(src->last_p))
                        perror("chdir");
                }
                else
                {
                    if (chdir(src->arg[1]))
                        perror("chdir");
                }
            }
            if (!src->arg[1])
            {
                if (chdir(get_HOME_dir()))
                    perror("chdir");
            }
            _strcpy(src->last_p, src->current_p);
            if (!getcwd(src->current_p, sizeof(src->current_p)))
                perror("getcwd");
            _create_new_var("PWD", src->current_p, src);
            return (3);
        }
        return (0);
    }
	return (0);
}

int builtin(t_container *src)
{
    __exit(src);
    if (src->arg[1] && src->arg[2])
    {
        if (_setenv(src->arg[1], src->arg[2], src))
            return (1);
    }
    if (_unsetenv(src) || _cd(src) || _env(src))
        return (1);
    return (0);
}