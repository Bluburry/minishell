#ifndef MINISHELL_H
# define MINISHELL_H


# include "libft.h"
# include "macros.h"
# include "structures.h"
# include <term.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <readline/readline.h>
# include <readline/history.h>

//# define CTRL_D __IOR(4, 4, int)


extern int	r_sig;

void	waiting_for_input(t_env *env);
void  	env(char **envp);
void  	parser(char *input);
void  	ft_echo(char **argv);
char	*pwd(void);
char	*find_exe_path(const char *path, const char *cmd);
int		check_path(char *path);
int		run_exe(char *path, char **args, t_env *env);

//Environment variables functions
int		var_to_print(char *str);
int 	get_env_start_size(char **envp);
int	  	num_invalid_env_vars(t_env *env);
int		index_of_str(t_env *env, const char *str);
int		str_cmp(const char *str1, const char *str2);
int  	add_new_env_var(t_env *env, const char *new);
int 	ordered_index(char **strs, int size, int prev);
int	  	env_already_exists(t_env *env, const char *new);
int		ft_strchrstr(const char *str, char c, const char *str_find);
double	total_size(char **mat, int size);
char	**env_string(t_env *env);
char  	**export_string(t_env *env);
char  	*str_after_char(char *str, char c);
char  	*get_env_var(t_env *env, const char *str);
void  	clear_env_struct(t_env *env);
void  	resize_env_struct(t_env *env);
void  	clear_chars(char **str, int size);
void	unset_env_var(t_env *env, char *var);
void  	alter_env_var(t_env *env, const char *new, int i);
void  	concatenate_matrix(char *str, char **mat, int size);
void  	copy_char_matrix(char **mat, char **new_mat, int size);
void  	copy_char_matrix_ordered(char **mat, char **new_mat, int size);
t_env 	*create_env_struct(char **envp);

//Signal functions
void	sig_handler(int sig, siginfo_t *info, void *ucontent);
void	init_signals(void);
void	init_child_signals(void);
void	sig_handler_child(int sig, siginfo_t *info, void *ucontent);




//Lexer functions
char	**lexer(char *input, t_env *env);
void	syntax_error(int type, char c);
void	dcp_cleaner(char **ptr);
int		is_space(char c);

//Lexer functions//Tokens
char	**tokens_init(char *input, t_env *env);
char	*create_token(const char *str, size_t len);
char	**split_quotes_tokens(char *input);
char	**split_inout_tokens(char **input);
char	**split_space_tokens(char **input);
char	**split_char_tokens(char **input, char c);
char	**expand_var_tokens(char **input, t_env *env);
char	*var_to_value(char *str, t_env *env);
char	**space_tokens_cleanup(char **input);
char	**merge_tokens_cleanup(char **input);
char	**check_for_quotes(char *input, char **ptr, int *flag);
int		is_token_end(char c);
int		move_in_str(char *str, char c);

// Change directory functions
int		cd(t_env *env, const char *path);
void	change_pwd(t_env *env, const char *path);
char	*calc_pwd(char *pwd, const char *path);
char	*relative_path(t_env *env, const char *path);

#endif
