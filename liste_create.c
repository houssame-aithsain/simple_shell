#include "simple_shell.h"

/*t_container *get_create_list(char **cmds)
{

}*/

void split_cmd_line(char *line, t_container *src)
{
    int i = 0;
    char **cmds;

    cmds = strtow(line, ';');
    while (cmds[i])
    {
        src->line = cmds[i];
        _execve(src);
        i++;
    }
    _free(cmds, NULL, 1);
}