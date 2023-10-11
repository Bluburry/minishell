/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:46:17 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:25 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	const char		*cs;

	i = 0;
	cs = s;
	while (i < n)
	{
		if (cs[i] == (char)c)
			return ((char *) &cs[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", (char *)ft_memchr("test string", 'r', 15));
}
// cc ft_memchr.c
*/