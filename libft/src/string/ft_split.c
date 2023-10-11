/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:49:26 by remarque          #+#    #+#             */
/*   Updated: 2023/10/08 20:53:48 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	j;
	int	is_word;

	i = 0;
	j = 0;
	is_word = 0;
	while (str[i])
	{
		if (str[i] != c && !is_word)
		{
			is_word++;
			j++;
		}
		else if (str[i] == c)
			is_word = 0;
		i++;
	}
	return (j);
}

static char	**clean_list(char **list)
{
	int		i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		list[i] = 0;
		i++;
	}
	free(list);
	return (0);
}

static inline char	**write_to_list(char const *s, char c, char **list)
{
	int		i;
	int		j;
	int		start;
	int		len;

	i = -1;
	j = 0;
	start = -1;
	len = ft_strlen(s);
	while (++i <= len)
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == len) && start > -1)
		{
			list[j] = ft_strdup_sted(s, start, i);
			if (!list[j])
				return (clean_list(list));
			j++;
			start = -1;
		}
	}
	list[j] = 0;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;

	if (!s)
		return (0);
	list = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!list)
		return (0);
	return (write_to_list(s, c, list));
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		index;
	char	**split;
	(void)	argc;
	split = ft_split(argv[1], argv[2]);
	index = 0;
	while (split[index])
	{
		printf("%s\n", split[index]);
		index++;
	}
}
*/

/* 
Parameters
	s: The string to be split.
	c: The delimiter character.
Return value
	The array of new strings resulting from the split.
	NULL if the allocation fails.
External functs.
	malloc, free
Description
	Allocates (with malloc(3)) and returns an array
	of strings obtained by splitting ’s’ using the
	character ’c’ as a delimiter. The array must end
	with a NULL pointer.
 */