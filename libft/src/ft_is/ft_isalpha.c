/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:24:39 by remarque          #+#    #+#             */
/*   Updated: 2022/11/11 17:56:08 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z'))
		return (0);
	return (1);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d should be 0\n", ft_isalpha(' '));
	printf("%d should be 0\n", ft_isalpha('!'));
	printf("%d should be 1\n", ft_isalpha('g'));
	printf("%d should be 1\n", ft_isalpha('V'));
	printf("%d should be 0\n", ft_isalpha('1'));
}
// cc ft_isalpha.c
*/