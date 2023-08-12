#include "simple_shell.h"

int builtin(char *line, char **arg)
{
    static char buffer[1024];

    if (!strncmp(line, arg[0], 4))
        if (!strncmp(line, "exit", 4))
        {
            if (arg[1])
                exit(_atoi(arg[1]));
            else
                exit(0);
        }
    if (!strncmp(line, arg[0], 6))
        if (!strncmp(line, "setenv", 6))
        {
            if (arg[1] && arg[2])
                if (setenv(arg[1], arg[2], 1) == -1)
                {
                    errno = ENOMEM;
                    perror("setenv");
                }
            return (1);
        }
    if (!strncmp(line, arg[0], 8))
        if (!strncmp(line, "unsetenv", 8))
        {
            if (arg[1])
                if (unsetenv(arg[1]) == -1)
                {
                    errno = EINVAL;
                    perror("unsetenv");
                }
            return (2);
        }
    if (!strncmp(line, arg[0], 2))
        if (!strncmp(line, "cd", 2))
        {
            printf("buffer=[%s]\n", buffer);
            if (arg[1])
            {
                if (!_strncmp(arg[1], "-", 1))
                {
                    if (chdir(buffer))
                        perror("chdir");
                }
                else 
                {
                    if (chdir(arg[1]))
                        perror("chdir");
                }
            }
            if (!getcwd(buffer, sizeof(buffer)))
                    perror("getcwd");
            return (2);
        }
    return (0);
}