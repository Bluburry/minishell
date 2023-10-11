/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:37:17 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:25 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*cs;

	i = 0;
	cs = (char *) s;
	while (i < n)
	{
		cs[i] = c;
		i++;
	}
	return (s);
}

/*
#include <stdio.h>

int	main(void)
{
	int	test;

	test = 10;
	ft_memset(&test, ' ', 1);
	printf("%d should be 32\n", test);
	ft_memset(&test, ' ', 2);
	printf("%d should be 8224\n", test);
}
// cc ft_memset.c
*/