/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:53:21 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/12 17:55:10 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting_for_input()
{
	char	*rl;

	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
		parser(rl);
	}
}

int	main(int argc, char **argv, char **envp)
{
/* 	t_envi	*env; */

	(void)argc;
	(void)argv;
	(void)envp;
/* 	env = get_env_var(envp);
	while (env != NULL)
	{
		printf("%s=%s\n", env->var, env->val);
		env->next;
	} */
	waiting_for_input();
	return (0);
}
