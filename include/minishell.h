#ifndef MINISHEL_H
# define MINISHEL_H

# include <term.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
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

typedef struct history
{
	char	*cmd;
	void	*prev;
	void	*next;
}	t_history;

typedef struct controller
{
	t_history *hst;
}	t_ctrl;

#endif