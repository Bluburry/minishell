#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

void	waiting_for_input(void);

//Environment variables functions
int		get_env_start_size(char **envp);
int		ft_strchrstr(const char *str, char c, const char *str_find);
char	*str_after_char(char *str, char c);
char	*get_env_var(t_env *env, const char *str);
void	clear_env_struct(t_env *env);
void	resize_env_struct(t_env *env);
void	clear_chars(char **str, int size);
void	add_new_env_var(t_env *env, const char *new);
void	copy_char_matrix(char **mat, char **new_mat, int size);
t_env	*create_env_struct(char **envp);


//Instructions execution functions
void	ft_cd(int argc, char **argv, char **envp);
void	ft_echo(char **argv);
void	ft_pwd(char **envp);
void	ft_env(char **envp);


//Lexer functions
void	lexer(char *input);
void	syntax_error(int type, char *c);
void	dcp_cleaner(char **ptr);
int		is_space(char c);

//Lexer functions//Tokens
char	**tokens_init(char *input);
char	*create_token(const char *str, size_t len);
char	**split_quotes_tokens(char *input, char *flag);
char	**split_inout_tokens(char **input);
char	**split_space_tokens(char **input);
char	**split_char_tokens(char **input, char c);
char	**space_tokens_cleanup(char **input);
char	**merge_tokens_cleanup(char **input);
char	**check_for_quotes(char *input, char **ptr, int *flag);
int		is_token_end(char c);
int		move_in_str(char *str, char c);

#endif
