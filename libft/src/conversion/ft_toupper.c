/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:22:25 by remarque          #+#    #+#             */
/*   Updated: 2022/11/11 18:04:34 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ' ');
	return (c);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%c should be A\n", ft_toupper('A'));
	printf("%c should be B\n", ft_toupper('b'));
	printf("%c should be C\n", ft_toupper('C'));
	printf("%c should be 1\n", ft_toupper('1'));
	printf("%c should be !\n", ft_toupper('!'));
	printf("%c should be {\n", ft_toupper('{'));
	printf("%c should be H\n", ft_toupper('h'));
}
// cc ft_toupper.c
*/