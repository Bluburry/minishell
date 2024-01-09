#include "minishell.h"
#define PTH "/tmp/MS_HEREDOC"
#define ERR_STR "Warning: heredoc delimited by end of file instead of %s\n"

void	sig_handler_heredoc(int sig)
{
	close(STDIN_FILENO);
	printf("\n");
	g_sig = sig;
}

void	set_signals_heredoc(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){.sa_handler = sig_handler_heredoc};
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

static int	create_file(char *stop)
{
	auto int fl = open(PTH, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	auto char *s = NULL;
	if (fl == -1)
		return (printf("Error opening temp file for writing.\n"), 0);
	while (true)
	{
		s = readline("∙ ");
		if (g_sig == SIGINT)
			return (free(s), unlink(PTH), close(fl), 130);
		if (s == NULL)
		{
			printf(ERR_STR, stop);
			break ;
		}
		else if (!ft_strcmp(s, stop))
			break ;
		ft_putstr_fd(s, fl);
		ft_putstr_fd("\n", fl);
		free(s);
	}
	free(s);
	close(fl);
	return (0);
}

int	redir_heredoc(char *stop, t_data *d)
{
	auto int t = dup(1);
	dup2(d->stdout, STDOUT_FILENO);
	dup2(d->stdin, STDIN_FILENO);
	g_sig = -1;
	set_signals_heredoc();
	auto int ret = create_file(stop);
	set_signals_base();
	dup2(t, STDOUT_FILENO);
	close(t);
	if (ret == 130)
		return (130);
	auto int fl = open(PTH, O_RDONLY, 0);
	if (fl == -1)
		return (printf("Error opening temp file for reading.\n"), 0);
	return (unlink(PTH), dup2(fl, 0), close(fl), 0);
}
