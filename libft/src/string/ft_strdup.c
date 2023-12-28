/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:52:20 by remarque          #+#    #+#             */
/*   Updated: 2023/12/28 15:53:49 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*str;

	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (0);
	return (ft_strcpy(str, s));
}

/*
#include<stdio.h>

int	main(void)
{
	char	*str;

	str = ft_strdup("This is a test string.");
	printf("%s\n", str);
	free(str);
	str = 0;
}
*/
