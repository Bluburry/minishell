/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:28 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/25 05:41:00 by ade-barr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		get_env_start_size(char **envp);
int		ft_strchrstr(const char *str, char c, const char *str_find);
char	*str_after_char(char *str, char c);
char	*get_env_var(t_env *env, const char *str);
char	*var_to_value(char *str, t_env *env);
void	clear_env_struct(t_env *env);
void	resize_env_struct(t_env *env);
void	clear_chars(char **str, int size);
void	add_new_env_var(t_env *env, const char *new);
void	copy_char_matrix(char **mat, char **new_mat, int size);
t_env	*create_env_struct(char **envp);
void	pwd(char **envp);
void	ft_echo(char **argv);
void	env(char **envp);
void	cd(int argc, char **argv, char **envp);
void	parser(char *input);
void	waiting_for_input();

#endif
