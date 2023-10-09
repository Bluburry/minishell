#ifndef MINISHEL_H
# define MINISHEL_H

# include "../libft/libft.h"
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

typedef struct env_var
{
	char	*var;
	char	*val;
	void	*next;
}	t_envi;

typedef struct controller
{
	t_envi *env;
}	t_ctrl;

void	env_delone(t_envi *env);
void	env_clear(t_envi **env);
void	env_add_back(t_envi **env, t_envi *new);
t_envi	*env_last(t_envi *env);
t_envi	*get_env_var(char **envp);
t_envi	*env_new(char *var, char *val);


#endif