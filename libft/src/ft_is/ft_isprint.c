/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:26:37 by remarque          #+#    #+#             */
/*   Updated: 2022/11/11 18:00:47 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= ' ' && c <= '~')
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d should be 1\n", ft_isprint(' '));
	printf("%d should be 1\n", ft_isprint('!'));
	printf("%d should be 1\n", ft_isprint('g'));
	printf("%d should be 1\n", ft_isprint('V'));
	printf("%d should be 1\n", ft_isprint('1'));
	printf("%d should be 1\n", ft_isprint('9'));
	printf("%d should be 0\n", ft_isprint(12));
}
// cc ft_isprint.c
*/