/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:24:00 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d should be 0\n", ft_isalnum(' '));
	printf("%d should be 0\n", ft_isalnum('!'));
	printf("%d should be 1\n", ft_isalnum('g'));
	printf("%d should be 1\n", ft_isalnum('V'));
	printf("%d should be 1\n", ft_isalnum('1'));
}
// cc ft_isalnum.c ft_isalpha.c ft_isdigit.c
*/