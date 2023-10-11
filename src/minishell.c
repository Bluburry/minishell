/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:53:21 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/11 15:04:19 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	char	*rl;
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
	while (1)
	{
		rl = readline("minishell > ");
		printf("rl: %s\n", rl);
		parser(rl);
	}
	return (0);
}