#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

# define TRUE 1

extern char **environ;

void    ft_execve(char *line, char **argv);
int     _strlen(char *s);
char **strtow(char *str, char c);
void ft_free(char **d_pointer, char *pointer, int flag);
char *_strcpy(char *dest, char *src);
int	_strncmp(const char *s1, const char *s2, size_t n);

#endif/*SIMPLE_SHELL*/
