/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:45:44 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:20 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		n *= -1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int	is_negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		len;

	nbr = n;
	len = count(n) + is_negative(n);
	str = malloc(len + 1);
	if (!(str))
		return (0);
	if (n < 0)
		nbr *= -1;
	str[len] = '\0';
	while (--len >= 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*num;

	num = ft_itoa(256);
	printf("%s should be 256\n", num);
	num = ft_itoa(-2147483648);
	printf("%s should be -2147483648\n", num);
	num = ft_itoa(0);
	printf("%s should be 0\n", num);
}
// cc ft_itoa.c
*/