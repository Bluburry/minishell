/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:48:21 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:25 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	if (dest == src || n == 0)
		return (dest);
	if ((size_t)dest - (size_t)src < n)
	{
		i = n -1;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}

/*
#include <stdio.h>

int	main(void)
{
	int		test;
	int		test2;
	char	*s;

	test = 196609;
	ft_memcpy(&test2, &test, 2);
	printf("%d should be 1\n", test2);
	s = (char *)&test;
	ft_memcpy(&s[2], &test, 2);
	printf("%d should be 65537\n", test);
}
// cc ft_memcpy.c ft_memmove.c
*/