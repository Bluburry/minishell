#include "minishell.h"

bool	exec_pipe(t_data *d)
{
	int	fd[2];
	int	in;
	int	out;

	if (d->pipe_state == p_last)
	{
		in = prevfd;
		out = STDOUT_FILENO;
	}
	else
		if (pipe(fd) == -1)
			return (false);
	if (d->pipe_state == p_first)
	{
		in = STDIN_FILENO;
		out = fd[1];
	}
	else
	{
		in = d->fd_in;
		out = fd[1];
	}
	dup2(out, STDOUT_FILENO);
	close(out);
	dup2(in, STDIN_FILENO);
	close(in);
	d->fd_in = in;
	if (d->pipe_state == p_last)
	{
		close(d->fd_in);
		d->fd_in = -1;
	}
}
