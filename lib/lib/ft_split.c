/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:32:17 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/01 21:49:54 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	calc_splits(char const *s, char c)
{
	size_t	num;
	int		size;

	if (!*s)
		return (0);
	size = (int) ft_strlen(s) - 1;
	num = 0;
	while (size >= 0)
	{
		if (size >= 0 && s[size] != c)
		{
			num++;
			while (size >= 0 && s[size] != c)
				size--;
		}
		if (size >= 0 && s[size] == c)
			size--;
	}
	return (num);
}

int	calcchars(char const *s, char c)
{
	int	num;

	num = 0;
	while (s[num] && s[num] != c)
		num++;
	return (num);
}

void	fillsplit(char **splits, char const *s, char c, size_t numofsplits)
{
	size_t	size;
	size_t	i;

	i = 0;
	while (i < numofsplits)
	{
		while (*s == c)
			s++;
		size = calcchars(s, c);
		splits[i] = (char *) malloc((size + 1) * sizeof(char));
		ft_memcpy(splits[i], s, size);
		splits[i][size] = 0;
		while (size--)
			s++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**splits;
	size_t	numofsplits;

	if (!s)
		return (NULL);
	numofsplits = calc_splits(s, c);
	splits = (char **) malloc((numofsplits + 1) * sizeof(char *));
	if (!splits)
		return (NULL);
	fillsplit(splits, s, c, numofsplits);
	splits[numofsplits] = 0;
	return (splits);
}
