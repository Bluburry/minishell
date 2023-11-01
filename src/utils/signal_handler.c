#include "minishell.h"
#include <signal.h>
#include <unistd.h>

int	r_sig;

void	init_child_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
}

void	init_signals(void)
{
	struct sigaction	sa;
	struct sigaction	ignore;

	ft_bzero(&sa, sizeof(sa));
	ft_bzero(&ignore, sizeof(ignore));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ignore, NULL);
	sigaction(SIGQUIT, &ignore, NULL);
}

void	sig_handler(int sig, siginfo_t *info, void *ucontent)
{
	(void)ucontent;
	(void)info;
	if (sig == SIGINT)
	{
		//r_sig = sig;
		write(1, "\n", 1);
		 kill (info->si_pid, SIGTERM);
	}
}

void	sig_handler_child(int sig, siginfo_t *info, void *ucontent)
{
	(void)ucontent;
	(void)info;
	if (sig == SIGINT)
	{
		return;
	}
}
