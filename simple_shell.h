#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

/*ANSI escape codes for text color*/
#define ANSI_COLOR_RED		"\x1b[91m"
#define ANSI_COLOR_GREEN	"\x1b[32m"
#define ANSI_COLOR_YELLOW	"\x1b[93m"
#define ANSI_COLOR_BLUE		"\x1b[34m"
#define ANSI_COLOR_MAGENTA	"\x1b[35m"
#define ANSI_COLOR_CYAN		"\x1b[36m"
#define ANSI_COLOR_RESET	"\x1b[0m"
#define ANSI_COLOR_GRAY		"\x1b[37m"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

# define MAIN 0
# define FD 2
# define TRUE 1
# define AND_CMDS 12
# define OR_CMDS 13
# define NAME 74
# define VALUE 75
# define EMPTY -777


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

extern char **environ;

/**
 * struct alias - Holds alias information
 * @name: Array of alias names
 * @value: Array of corresponding alias values
 */
typedef struct alias
{
	char **name;
	char **value;
} t_alias;

/**
 * struct container - Holds various information related to the shell
 * @splitedLines: Array to hold split command lines
 * @mc_arg: Array for multiple command arguments
 * @and_cmds: and_cmds.
 * @arg: Array to hold command arguments
 * @env: Array to hold environment variables
 * @cmd_path: Path of the current command being executed
 * @mainLine: Original main input line
 * @fdLine: Line read from a file descriptor
 * @p_name: Name of the shell process
 * @line: Current command line being processed
 * @path: Current working directory path
 * @HOME: Home directory path
 * @PWD: Current working directory path (longer version)
 * @OLDPWD: Previous working directory path
 * @exit_status: Exit status of the last command
 * @cmd_counter: Count of executed commands
 * @is_empty: Flag to indicate if a line is empty
 * @arg_lent: Length of the argument array
 * @op: Operator code for command chaining
 * @is_fd: Flag to indicate if processing a file descriptor
 * @alias: Structure to hold alias information
 */
typedef struct container
{
	char	**splitedLines;
	char	**and_cmds;
	char	**mc_arg;
	char	**arg;
	char	**env;
	char	*cmd_path;
	char	*mainLine;
	char	*fdLine;
	char	*p_name;
	char	*line;
	char	*path;
	char	*HOME;
	char	PWD[1024];
	char	OLDPWD[1024];
	int		exit_status;
	int		cmd_counter;
	int		is_empty;
	int		arg_lent;
	int		op;
	int		is_fd;
	t_alias	alias;
} t_container;

/*-------------Main-Utils---------------*/
void __var_init(t_container *src, int argc, char **argv);
void __main_free(t_container *src, int flag);
int __fd_status(char *filename);
void __new_line_sanitizer(char *str);
int __filename_input(char **argv, int fd);
/*-------------SortCmdTypeUtils---------*/
int __ifEmptyLine(char *line);
int	__CmdOrBuiltin(t_container *src);
void cmd_extracter(char *cmd);
char *check_PATH(t_container *src);
int __is_cmd_builtin(t_container *src, int flag);
/*-------------AliasCoreUtils-----------*/
int __is_alias_of_x(char *var);
void __IfAliasIsEmpty(char *str, t_container *src);
void __create_new_alias_name(char *str, t_container *src);
char *get_name_or_value(char *str, int flag);
void __new_alias_table(t_container *src, char **name, char **value);
int TDPCounter(char **arr);
/*-------------AliasBuiltin-----------*/
void create_new_alias(char *str, t_container *src);
int PrintAliasName(t_container *src, int flag, int i);
void _alias_error(t_container *src, int len, int i, int flag);
/*-------------getline---------------*/
char	*_getline(int fd);
char	*_strjoin(char *s1, char *s2);
int		_if_new_line(char *buffer);
/*-------------End-getline-----------*/
void	_expand(t_container *src);

void	split_cmd_line(char *line, t_container *src);
int		SortCmdType(char *line, t_container *src);
size_t	_strlen(char *s);
char	**strtow(char *str, char c);
void	_free(char **d_pointer, char *pointer, int flag);
char	*_strcpy(char *dest, char *src);
int		_strncmp(const char *s1, const char *s2, size_t n);
int		_atoi(char *s);
int		builtins(t_container *src);
int		_strcmp(char *s1, char *s2);
char	*_strdup(char *str);
char	*get_HOME_dir(t_container *src);
int		_env(t_container *src);
int		_setenv(t_container *src);
int		_unsetenv(t_container *src);
int		_create_new_var(char *name, char *value, t_container *src);
int		_var_check(char *name, char *value);
void	set_env(t_container *src);
int		unset_var(t_container *src);
int		_alias(t_container *src);
void	get_create_alias_name(char *str, t_container *src);
char	**get_join_alias_args(char **arg);
char	*_substr(char *s, int start, size_t len);
char	*__strjoin(char *s1, char *s2);
int		if_s_quote(char *arg);
int		__is_alias_of_x(char *var);
int		AliasLineEnhancer(t_container *src);
void	_putnbr(int number, int fd);
/*-------------print-errors----------*/
void    _cd_error(t_container *src);
void	_cmd_not_found(t_container *src, int flag);
void _execute(t_container *src);
char	*_itoa(int n);
/*-------------ExpandCore-----------*/
char *__var(char *str, char *value, int *i, t_container *src);
char *__ps_id(char *value, int *i);
char *__exit_status(char *value, int *i, t_container *src);
char *__string(char *str, char *value, int *i);
/*-------------ExpandUtils-----------*/
int GetVarLent(char *str);
char *get_exit_status(int exit_status);
char *get_str_format(char *str);
char *get_ps_id();
char *get_var_value(char *str, char **env);
char *SortStrType(char *str, t_container *src);
void _NPC_remover(t_container *src);
int GetVarLent_str(char *str);
int __exit(t_container *src);
int is_path(t_container *src);
void	__free_all(t_container *src);
int _comments_sanitizer(char *line);
void __exit_error(t_container *src, int exit_code, int flag);
int is_alpha(char *str);
char *GetDIrPath(char **path, t_container *src);
char *get_OLDPWD_dir(void);

#endif/*SIMPLE_SHELL*/
