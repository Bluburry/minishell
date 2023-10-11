/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:03:12 by remarque          #+#    #+#             */
/*   Updated: 2023/10/08 06:01:57 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
#include <stdio.h>

int	main(void)
{
	char	s[30] = "abcdefghij";

	printf("%lu should be 10\n", ft_strlen(s));
}
// cc ft_strlen.c
*/