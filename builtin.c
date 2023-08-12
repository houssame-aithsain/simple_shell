#include "simple_shell.h"

int builtin(t_container *src)
{
    if (!strncmp(src->line, src->arg[0], 4))
        if (!strncmp(src->line, "exit", 4))
        {
            if (src->arg[1])
                exit(_atoi(src->arg[1]));
            else
                exit(0);
        }
    if (!strncmp(src->line, src->arg[0], 6))
        if (!strncmp(src->line, "setenv", 6))
        {
            if (src->arg[1] && src->arg[2])
                if (setenv(src->arg[1], src->arg[2], 1) == -1)
                {
                    errno = ENOMEM;
                    perror("setenv");
                }
            return (1);
        }
    if (!strncmp(src->line, src->arg[0], 8))
        if (!strncmp(src->line, "unsetenv", 8))
        {
            if (src->arg[1])
                if (unsetenv(src->arg[1]) == -1)
                {
                    errno = EINVAL;
                    perror("unsetenv");
                }
            return (2);
        }
        /*
    if (!strncmp(src->line, src->arg[0], 2))
        if (!strncmp(src->line, "cd", 2))
        {
            printf("buffer=[%s]\n", src->buffer);
            if (src->arg[1])
            {
                if (!_strncmp(src->arg[1], "-", 1))
                {
                    if (chdir(src->buffer))
                        perror("chdir");
                    src->cd = 1;
                }
                else 
                {
                    if (chdir(src->arg[1]))
                        perror("chdir");
                    src->cd = 1;
                }
            }
            return (2);
        }*/
    return (0);
}