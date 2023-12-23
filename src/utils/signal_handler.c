#include "minishell.h"

int	g_sig;

/* void	init_child_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
} */

void	init_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	sig_handler(int sig, siginfo_t *info, void *ucontent)
{
	(void)ucontent;
	(void)info;
	//printf("weeeeeeee\n");
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		if (info->si_pid)
			rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT && !info->si_pid)
	{
		exit(0); // ! replace????
	}
}

/* void	sig_handler_child(int sig, siginfo_t *info, void *ucontent)
{
	(void)ucontent;
	(void)info;
	if (sig == SIGINT)
	{
		return;
	}
} */
