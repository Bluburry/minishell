/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:35 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/12 18:46:05 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("syntax error near unexpected token `%c'\n", c);
	waiting_for_input();
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
			++i;
			if (flag == -1)
			{
				i++;
				str++;
			}
			while (*str && is_token_end(*str) != 0)
			{
				if (*str == '|' && flag == -1)
					syntax_error('|');
				else if (*str == '|')
				{
					flag = -1;
					i++;
				}
				str++;
			}
			if (is_token_end(*(str - 1)) == 1 && !(*str))
				i--;
		}
		else
			str++;
	}
	return (++i);
}

char	*create_token(const char *str, size_t len)
{
	char			*token;
	unsigned int	i;

	token = malloc((len + 1) * sizeof(char));
	if (token == 0)
		return (0);
	i = 0;
	while (i < len && *str)
	{
		token[i] = str[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

char	**token_split(char const *str)
{
	int		end;
	char	**tokens;
	char	**ptr;

	tokens = malloc((count_strs(str) + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*str)
	{
		while (*str && is_token_end(*str) == 1)
			str++;
		end = 0;
		while (str[end] && is_token_end(str[end]) == 0)
			end++;
		if (*str == '|')
			end++;
		if (end > 0)
		{
			*ptr = create_token(str, end);
			ptr++;
		}
		str = str + end;
	}
	*ptr = NULL;
	return (tokens);
}

void	parser(char *input)
{
	char	**tokens;

	if (!input || !(*input))
		return ;
	tokens = token_split(input);
/* 	if (ft_strnstrn(*tokens, "pwd", 4))
		pwd(envars) */
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}
