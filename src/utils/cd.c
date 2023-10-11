/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 17:46:42 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/10 18:28:26 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cd(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		while (*envp)
		{
			if (!ft_strnstr(*envp, "HOME=", 4))
			{
				chdir(*envp + 4);
				return ;
			}
			envp++;
		}
	}
	if (argc > 2)
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (argv[1])
	{
		if (chdir(argv[1]) != 0)
			printf("cd: no such file or directory: %s\n", argv[1]);
	}
}
/* 
int main(int argc, char **argv, char **envp)
{
	cd(argc, argv, envp);
	return (0);
}  */