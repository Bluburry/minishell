/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:27:20 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/12 18:45:12 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **envars)
{
	while (*envars)
	{
		if (ft_strnstr(*envars, "PWD=", 4) && *envars[4])
			break ;
		envars++;
	}
	printf("%s\n", *envars + 4);
}

/* int main (int argc, char **argv, char **envp)
{
	pwd(envp);
	(void)argc;
	(void)argv;
	return (0);
} */