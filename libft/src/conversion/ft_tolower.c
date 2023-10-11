/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:22:32 by remarque          #+#    #+#             */
/*   Updated: 2022/11/11 18:03:48 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ' ');
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%c should be a\n", ft_tolower('A'));
	printf("%c should be b\n", ft_tolower('b'));
	printf("%c should be c\n", ft_tolower('C'));
	printf("%c should be 1\n", ft_tolower('1'));
	printf("%c should be !\n", ft_tolower('!'));
	printf("%c should be {\n", ft_tolower('{'));
	printf("%c should be h\n", ft_tolower('h'));
}
// cc ft_tolower.c
*/