/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:20:19 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:25 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*cdest;
	char		*csrc;

	if (dest == src || n == 0)
		return (dest);
	cdest = (char *) dest;
	csrc = (char *) src;
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>

int	main(void)
{
	int	test;
	int	test2;

	test = 196609;
	ft_memcpy(&test2, &test, 2);
	printf("%d should be 1\n", test2);
}
// cc ft_memcpy.c
*/