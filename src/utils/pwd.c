/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:20 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/11 15:15:24 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(char **tokens)
{
	while (*tokens)
	{
		if (ft_strnstr(*tokens, "PWD=", 4) && *tokens[4])
			break ;
		tokens++;
	}
	printf("%s\n", *tokens + 4);
}

/* int main (int argc, char **argv, char **envp)
{
	pwd(envp);
	(void)argc;
	(void)argv;
	return (0);
} */