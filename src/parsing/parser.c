/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:35 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/11 17:46:39 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

int	is_token_end(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else if (c == '|')
		return (-1);
	return (0);
}
void	syntax_error(char c)
{
	printf("syntax error near unexpected token `%c'", c);
	exit (1);
}
int	count_strs(char const *str)
{
	int	i;
	int	flag;

	i = 0;
	while (*str)
	{
		flag = is_token_end(*str);
		if (flag != 0)
		{
			if (flag == -1)
				i++;
			++i;
			while (*str && is_token_end(*str) != 0)
			{
				str++;
				if (flag == -1 && *str == '|')
					syntax_error('|');
			}
		}
		else
			str++;
	}
	return (i);
}

char	**token_split(char const *str)
{
	int		end;
	char	**tokens;
	char	**ptr;

	if (!str)
		return (0);
	tokens = malloc((count_strs(str) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*str)
	{
		while (is_token_end(*str) == 1)
			str++;
		end = 0;
		while (str[end] && is_token_end(str[end]) == 0)
			end++;
		if (str[end])
			*ptr = ft_substr(str, 0, end);
		str = str + end;
		ptr++;
	}
	return (tokens);
}

void	parser(char *input)
{
	char	**tokens;

	tokens = token_split(input);
	if (ft_strncmp(tokens[0], "pwd", 4) == 0)
		pwd(tokens);
}
