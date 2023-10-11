/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:47:01 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:25 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*cs1;
	const unsigned char	*cs2;
	size_t				i;

	cs1 = s1;
	cs2 = s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	int	test[20];

	test[0] = 196609;
	test[1] = 5;
	test[2] = 1;
	printf("%d should be 0\n", ft_memcmp(&test[0], &test[2], 2));
	printf("%d should be 3\n", ft_memcmp(&test[0], &test[2], 4));
	printf("%d should be -4\n", ft_memcmp(&test[0], &test[1], 4));
	printf("%d should be 4\n", ft_memcmp(&test[1], &test[0], 4));
}
// cc ft_memcmp.c
*/