/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 21:44:34 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/28 19:52:20 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_gnl(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strrchr_gnl(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*(char *) s == (char) c)
		{
			return ((char *) s);
		}
		s++;
	}
	return (NULL);
}

void	*ft_memcpy_gnl(char *dest, const char *src, size_t n)
{
	void	*ptr;

	ptr = dest;
	if (!dest && !src)
		return (NULL);
	dest[n] = 0;
	while (n--)
	{
		*(char *)dest++ = *(char *)src++;
	}
	return (ptr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	i = ft_strlen_gnl(s1);
	j = ft_strlen_gnl(s2);
	string = (char *) malloc((i + j + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ft_memcpy_gnl(string, s1, i);
	ft_memcpy_gnl(string + i, s2, j);
	string[i + j] = 0;
	return (string);
}
