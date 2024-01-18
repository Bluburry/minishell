/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:43:43 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/18 20:45:10 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_op_check(char **argv)
{
	int	i;

	if (argv[1][0] != '-' || ft_strncmp(argv[1], "-n", 2) != 0)
		return (1);
	i = 1;
	while (argv[1][i] == 'n')
		i++;
	if (!argv[1][i])
		return (0);
	return (1);
}

int	ft_echo(char **argv)
{
	int	i;
	int	n;

	if (!argv[1])
	{
		printf("\n");
		return (0);
	}
	n = echo_op_check(argv);
	i = 1;
	if (n == 0)
		i = 2;
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
