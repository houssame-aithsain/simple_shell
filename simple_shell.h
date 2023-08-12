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

extern char **environ;

typedef struct container{
	char	*p_name;
	char	*line;
	int		cd;
	char	current_p[1024];
	char	last_p[1024];
	char	**arg;
} t_container;

# define TRUE 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

char	*_getline(int fd);
char	*_getline_utils(int fd, char *container);
char	*_strjoin(char *s1, char *s2);
int		_check_new_line(char *buffer);

void    _execve(t_container *src);
size_t	_strlen(char *s);
char **strtow(char *str, char c);
void _free(char **d_pointer, char *pointer, int flag);
char *_strcpy(char *dest, char *src);
int	_strncmp(const char *s1, const char *s2, size_t n);
int _atoi(char *s);
int builtin(t_container *src);

#endif/*SIMPLE_SHELL*/
