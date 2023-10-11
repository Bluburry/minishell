/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:03:40 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:26 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

/*
#include<stdio.h>
#include<string.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n);

int	main(void)
{
	printf("ft_strncmp\n");
	printf("%d should be %d \n", ft_strncmp("ab", "a ", 1),
		strncmp("ab", "a ", 1));
	printf("%d should be %d\n", ft_strncmp("a      ", "a ", 10),
		strncmp("a      ", "a ", 10));
	printf("%d should be %d\n", ft_strncmp("a", "a       ", 10),
		strncmp("a", "a       ", 10));
	printf("%d should be %d \n", ft_strncmp("ab", "a ", 2),
		strncmp("ab", "a ", 2));
	printf("%d should be %d \n", ft_strncmp("A", "a", 1),
		strncmp("A", "a", 1));
	printf("%d should be %d \n", ft_strncmp("a", "a", 1),
		strncmp("a", "a", 1));
	return (0);
}
*/