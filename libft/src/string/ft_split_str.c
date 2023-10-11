/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:48:59 by remarque          #+#    #+#             */
/*   Updated: 2023/10/08 20:49:46 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	cmp(const char c, const char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (c == s[i])
			return (true);
	return (false);
}

static int	count_words(const char *str, char const *c)
{
	int		i;
	int		wc;
	bool	is_word;

	i = -1;
	wc = 0;
	is_word = false;
	while (str[++i])
	{
		if (!cmp(str[i], c) && !is_word)
		{
			is_word = true;
			wc++;
		}
		else if (cmp(str[i], c))
			is_word = false;
	}
	return (wc);
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

static inline char	**write_to_list(char const *s, char const *c, char **list)
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
		if (!cmp(s[i], c) && start < 0)
			start = i;
		else if ((cmp(s[i], c) || i == len) && start > -1)
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

char	**ft_split_str(char const *s, char const *c)
{
	char	**list;

	if (!s)
		return (0);
	list = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!list)
		return (0);
	return (write_to_list(s, c, list));
}
