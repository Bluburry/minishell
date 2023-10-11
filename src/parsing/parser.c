/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:35 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/11 15:57:17 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_token_end(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else if (c == '|')
		return (-1);
	return (0);
}

int	count_strs(char const *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (is_token_end(*str) != 0)
		{
			++i;
			while (*str && is_token_end(*str) != 0)
				str++;
		}
		else
			str++;
	}
	return (i);
}

char	**token_split(char const *s)
{
	int		i;
	int		start;
	int		end;
	char	**strs;

	if (!s)
		return (0);
	i = 0;
	start = 0;
	strs = malloc((count_strs(s) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	while (i < count_strs(s))
	{
		while (is_token_end(s[i]) != 0)
			start++;
		end = start;
		while (s[end] != c && s[end] != 0)
			end++;
		strs[i] = ft_substr(s, start, end - start);
		start = end;
		i++;
	}
	strs[i] = 0;
	return (strs);
}

void	parser(char *input)
{
	char	**tokens;

	tokens = token_split(input);
	if (ft_strncmp(tokens[0], "pwd", 4) == 0)
		pwd(tokens);
}
