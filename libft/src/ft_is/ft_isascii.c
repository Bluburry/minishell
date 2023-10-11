/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:26:31 by remarque          #+#    #+#             */
/*   Updated: 2022/11/11 17:57:45 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	return (1);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d should be 1\n", ft_isascii(' '));
	printf("%d should be 1\n", ft_isascii('!'));
	printf("%d should be 1\n", ft_isascii('g'));
	printf("%d should be 1\n", ft_isascii('V'));
	printf("%d should be 0\n", ft_isascii(128));
	printf("%d should be 0\n", ft_isascii(133));
}
// cc ft_isascii.c
*/