/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:28 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/10 17:07:20 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

void	pwd(char **envp);
void	ft_echo(char **argv);

#endif
