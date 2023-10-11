/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:24:43 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/10 17:06:12 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **argv)
{
	int	i;
	int	n;

	if (!argv[1])
	{
		printf("\n");
		return ;
	}
	n = ft_strncmp(argv[1], "-n", 2);
	if (n == 0)
		i = 2;
	else
		i = 1;
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (n != 0)
		printf("\n");
}

/* int	main(int argc, char **argv)
{
	ft_echo(argv);
	(void)argc;
	return (0);
} */
