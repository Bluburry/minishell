/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:20 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/10 16:01:22 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void pwd(char **envp)
{
	while(*envp)
	{
		if (ft_strnstr(*envp, "PWD=", 4) && *envp[4])
			break;
		envp++;
	}
	printf("%s\n", *envp + 4);
}

/* int main (int argc, char **argv, char **envp)
{
	pwd(envp);
	(void)argc;
	(void)argv;
	return (0);
} */