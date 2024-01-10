/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:41:04 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:41:05 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	redir_pipe_helper(t_data *d, int in, int out, int prev)
{
	dup2(out, STDOUT_FILENO);
	if (out != STDOUT_FILENO && out != d->stdout)
		close(out);
	dup2(in, STDIN_FILENO);
	if (in != STDIN_FILENO && in != d->stdin)
		close(in);
	if (d->pipe_state != p_last)
		d->fd_in = prev;
}

bool	redir_pipe(t_data *d)
{
	int	fd[2];
	int	in;
	int	out;

	if (d->pipe_state == p_last)
	{
		in = d->fd_in;
		out = d->stdout;
		d->fd_in = -1;
	}
	else
		if (pipe(fd) == -1)
			return (false);
	if (d->pipe_state == p_first)
	{
		in = d->stdin;
		out = fd[1];
	}
	else if (d->pipe_state == p_middle)
	{
		in = d->fd_in;
		out = fd[1];
	}
	redir_pipe_helper(d, in, out, fd[0]);
	return (true);
}

bool	exec_pipe(t_data *d)
{
	if (d->curr_pipe == 0)
		d->pipe_state = p_first;
	else if (d->curr_pipe == d->pipe_n)
		d->pipe_state = p_last;
	else
		d->pipe_state = p_middle;
	d->curr_pipe++;
	return (redir_pipe(d));
}
