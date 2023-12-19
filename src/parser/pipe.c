#include "minishell.h"
#include "structures.h"
#include <stdbool.h>

bool	redir_pipe(t_data *d)
{
	int	fd[2];
	int	in;
	int	out;

	if (d->pipe_state == p_last)
	{
		in = d->fd_in;
		out = STDOUT_FILENO;
		d->fd_in = -1;
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
	if (d->pipe_state != p_last)
		d->fd_in = fd[0];
	return (true);
}

bool	exec_pipe(t_data *d)
{
	if (d->curr_pipe == 0)
		d->pipe_state = p_first;
	else if (d->curr_pipe == d->pipe_n - 1)
		d->pipe_state = p_last;
	else
		d->pipe_state = p_middle;
	d->curr_pipe++;
	return (redir_pipe(d));
}
