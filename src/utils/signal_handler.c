#include "minishell.h"

void	sig_handler(int sig, siginfo_t *info, void *ucontent)
{
	(void)ucontent;
	(void)info;
	printf("weeeeeeee\n");
	if (sig == SIGQUIT)
	{
		printf("exit\n");
		exit(0);
	}
}
