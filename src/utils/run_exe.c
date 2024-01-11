/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:43:53 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:43:54 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_exe(char *path, char **args, t_env *env)
{
	pid_t	pid;

	if (!path || !*path)
		return (0);
	pid = fork();
	set_signals_fork();
	if (!pid)
	{
		execve(path, args, env->vars);
	}
	set_signals_base();
	return (true);
}
