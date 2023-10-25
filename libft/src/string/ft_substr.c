/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:00:28 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:26 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	size = ft_strlen(s);
	if ((size_t)start > size)
		return (ft_calloc(1, 1));
	else if (len <= size)
		str = malloc (len + 1);
	else
	{
		str = malloc (size + 1);
		len = size;
	}
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	char	s[30] = "abcdefghij";

	printf("%s\n", s);
	printf("%s\n", ft_substr(s, 3, 20));
}
// cc ft_substr.c ft_strlen.c ft_calloc.c ft_bzero.c ft_memset.c
*/
