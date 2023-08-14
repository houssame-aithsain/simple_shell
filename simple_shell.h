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
	char	**arg;
	char	**env;
	char	*p_name;
	char	*line;
	char	*path;
	char	*HOME;
	char	*cmd_path;
	char	current_p[1024];
	char	last_p[1024];
	struct container *next;
} t_container;

# define TRUE 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

char	*_getline(int fd);
char	*_getline_utils(int fd, char *container);
char	*_strjoin(char *s1, char *s2);
int		_check_new_line(char *buffer);

void split_cmd_line(char *line, t_container *src);
void    _execve(t_container *src);
size_t	_strlen(char *s);
char **strtow(char *str, char c);
void _free(char **d_pointer, char *pointer, int flag);
char *_strcpy(char *dest, char *src);
int	_strncmp(const char *s1, const char *s2, size_t n);
int _atoi(char *s);
int builtin(t_container *src);
int _strcmp(char *s1, char *s2);
char	*_strdup(char *str);
char *get_HOME_dir(void);
char *fix_path(char *path);
int _env(t_container *src);
int _setenv(char *name, char *value, t_container *src);
int _unsetenv(t_container *src);
int _create_new_var(char *name, char *value, t_container *src);
int _var_check(char *name, char *value);
void set_env(t_container *src);
int unset_var(t_container *src);

#endif/*SIMPLE_SHELL*/
