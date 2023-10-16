/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:55:13 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:26 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	n;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	n = size;
	while (dst[i] && n--)
		i++;
	n = size - i;
	if (!n || !size || !dst || !src)
		return (ft_strlen(src) + i);
	j = 0;
	n--;
	while (src[j] && n--)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}

/*
#include<stdio.h>

size_t	strlcat(char *dst, const char *src, size_t siz)
{
	char *d = dst;
	const char *s = src;
	size_t n = siz;
	size_t dlen;

	while (n-- != 0 && *d != '\0')
		d++;
	dlen = d - dst;
	n = siz - dlen;

	if (n == 0)
		return(dlen + ft_strlen(s));
	while (*s != '\0') {
		if (n != 1) {
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';

	return(dlen + (s - src));
}

int	main(void)
{
	char	a[90] = "Test string", b[] = " has been modified.";
	char	c[] = "", d[90] = "Your life";
	char	e[90] = "Test string", f[] = " has been modified.";
	char	g[] = "", h[90] = "Your life";

	printf("ft_strlcat\n");
	printf("'%d' should be '%ld' \n", ft_strlcat(a, b, 0),
		strlcat(e, f, 0));
	printf("'%s' should be '%s'\n", a, e);
	printf("'%d' should be '%ld' \n", ft_strlcat(a, b, 5),
		strlcat(e, f, 5));
	printf("'%s' should be '%s'\n", a, e);
	printf("'%d' should be '%ld' \n", ft_strlcat(d, c, sizeof(c)),
		strlcat(h, g, sizeof(g)));
	printf("'%s' should be '%s'\n", d, h);
	printf("'%d' should be '%ld' \n", ft_strlcat(d, b, sizeof(b)),
		strlcat(h, f, sizeof(f)));
	printf("'%s' should be '%s'\n", d, h);
	printf("'%d' should be '%ld' \n", ft_strlcat(d, " Forever.", 90),
		strlcat(h, " Forever.", 90));
	printf("'%s' should be '%s'\n", d, h);
	return (0);
}
*/
