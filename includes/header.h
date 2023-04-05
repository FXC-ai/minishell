#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>

# define BUFFER_SIZE 1024

#define BUILTIN_ECHO 1
#define BUILTIN_CD 2
#define BUILTIN_PWD 3
#define BUILTIN_EXPORT 4
# define BUILTIN_UNSET 5
# define BUILTIN_ENV 6
#define BUILTIN_EXIT 7

typedef struct	s_sig
{
	int 	sig_int;
	int		sig_quit;
	int		ms_errno;
	int		program_in_process;
	pid_t	pid;
} t_sig;


void	rl_replace_line (const char *text, int clear_undo);

typedef struct s_data
{
	int	nb_instuction;
	int	last_fd;
}   t_data;

typedef struct pipe
{
	char	**cmd1;
	char	**cmd2;
	int		fdin;
	int		fdout;
}	t_pipe;

typedef struct s_redirect
{
	char	*left_str;
	char	*right_str;
}	t_redirect;

//MAIN.C
void	sig_init(void);
void disable_ctrl_chars();
int	check_entry(char *line);
void	wait_for_input(char *env[]);

//REDIRECTION.C
void	execute_command(char **parsed_args, int in_fd, int out_fd, char *env[]);
void	execute_command_2(char **parsed_args, int in_fd, int out_fd, char *env[]);
int process_delimiter(char *del);
int		process_redirection(char *str, char *env[], int mode);

//SIGNAL.C

void    signal_handler();

//PARSE_ARGS.C

//void    parsing(char **args, char *env[]);

//LEXER.C
int is_space(char c);
char	**lexer(char *str, char *env[]);
char	**ft_split_lexer(char const *str, char c);
int		count_chr(const char *str, char c);
void parse_dollar(char **tab_cmds, char *env[]);
char *find_env_variable (char *var_name, char *env[]);
char *ft_strndup(char *str, size_t n);
void normalize_with_space(char **str);

//FT_LEXER_NO_QUOTE.C
char	**ft_lexer_no_quote(char const *str, char c);

//UTILS.C
void	print_tab(char **tab);
int	get_max_length(char *str1, char *str2);
char *extract_command_name(const char *full_path);
void	ft_free_tabs(char **tab, int h);
int	size_tab(char **tab);
char	**create_tab_paths(char *env[]);
char	*create_path_cmd(char *path, char *cmd);
char	*cmd_exists(char *cmd, char *env[]);
char	*normalize_cmd(char* str, char *env[]);
int		is_builtins(char *str);
void	freemalloc(char **result, int j);


//MS_PIPE.C
void execute_last_cmd(int pipe_fd[2], char **tab_cmds, int nbr_cmds, char *env[]);
void execute_first_cmd(int pipe_fd[2], char **tab_cmds, char *env[]);
void redirection (char *input_cmd, int previous_pipe[2], int next_pipe[2], char *env[]);
void execution (char *input_cmd, char *env[]);
void ms_pipe2(char **tab_cmds, char *env[]);


//BUILTINS
void	echo_process(char **cmd);
void	cd_process(char **current_command, char *env[]);
void	pwd_process();
int		unset_process(char **parsed_args, char *env[]);
void	env_process(char **parsed_args, char *env[]);
void	export_process(char **current_command, char *env[]);
void add_to_env(char *ligne, char *value, char *env[]);
void    exit_process();
int		unset_process_str(char *key, char *env[]);


extern t_sig global_sig;

#endif