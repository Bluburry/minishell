/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:26:34 by remarque          #+#    #+#             */
/*   Updated: 2022/11/11 17:59:05 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d should be 0\n", ft_isdigit(' '));
	printf("%d should be 0\n", ft_isdigit('!'));
	printf("%d should be 0\n", ft_isdigit('g'));
	printf("%d should be 0\n", ft_isdigit('V'));
	printf("%d should be 1\n", ft_isdigit('1'));
	printf("%d should be 1\n", ft_isdigit('9'));
}
// cc ft_isdigit.c
*/