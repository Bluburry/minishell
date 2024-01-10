/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:41:54 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:41:55 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	sig_handler_interrupt(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (sig == SIGINT)
	{
		g_sig = SIGINT;
		printf("\n");
		rl_replace_line("", 0);
		if (info->si_pid != 0)
			rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_fork(int sig)
{
	(void)sig;
	exit (0);
}

void	set_signals_base(void)
{
	struct sigaction	sa;

	sa = (struct sigaction){.sa_flags = SA_SIGINFO,
		.sa_sigaction = sig_handler_interrupt};
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_fork(void)
{
	signal(SIGINT, sig_handler_fork);
	signal(SIGQUIT, sig_handler_fork);
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
