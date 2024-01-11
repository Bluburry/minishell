/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:43:43 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:43:44 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	int	i;
	int	n;

	if (!argv[1])
	{
		printf("\n");
		return (0);
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
	return (0);
}

/* int	main(int argc, char **argv)
{
	ft_echo(argv);
	(void)argc;
	return (0);
} */
