/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:28 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/12 17:25:06 by jecarval         ###   ########.fr       */
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
int		index_of_str(t_env *env, const char *str);
int		env_already_exists(t_env *env, const char *new);
int		ft_strchrstr(const char *str, char c, const char *str_find);
char	*str_after_char(char *str, char c);
char	*get_env_var(t_env *env, const char *str);
void	pwd(char **envp);
void	env(char **envp);
void	waiting_for_input();
void	parser(char *input);
void	ft_echo(char **argv);
void	clear_env_struct(t_env *env);
void	resize_env_struct(t_env *env);
void	clear_chars(char **str, int size);
void	unset_env_var(t_env *env, char *var);
void	cd(int argc, char **argv, char **envp);
void	add_new_env_var(t_env *env, const char *new);
void	alter_env_var(t_env *env, const char *new, int i);
void	copy_char_matrix(char **mat, char **new_mat, int size, int skip);
t_env	*create_env_struct(char **envp);

#endif
