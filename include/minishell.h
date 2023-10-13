#ifndef MINISHEL_H
# define MINISHEL_H

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

int		get_env_start_size(char **envp);
void	clear_env_struct(t_env *env);
void	resize_env_struct(t_env *env);
void	clear_chars(char **str, int size);
void	add_new_env_var(t_env *env, char *new);
void	copy_char_matrix(char **mat, char **new_mat, int size);
t_env	*create_env_struct(char **envp);

#endif