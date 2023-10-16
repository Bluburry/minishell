/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quote_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:07:50 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/15 21:08:57 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens_quotes(char *input)
{
	int		len;
	char	c;

	len = 0;
	while (*input && *input != '\'' && *input != '\"')
	{
		if (is_token_end(*input) <= 0 && len != 1)
			len = 1;
		input++;
	}
	if (!(*input))
		return (len);
	c = *input++;
	while (*input && *input != c)
		input++;
	if (*input && *(input + 1))

		len += count_tokens_quotes(++input);
	len++;
	return (len);
}

int	quotes_end(char *input)
{
	int	end;

	end = 0;
	if (*input == '\'' || *input == '\"')
	{
		end++;
		while (input[end] && input[end] != *input)
			end++;
		end++;
	}
	else
	{
		while (input[end] && input[end] != '\'' && input[end] != '\"')
			end++;
	}
	return (end);
}

char	**split_quotes(char *input)
{
	char	**q_tokens;
	char	**ptr;
	int		end;

	q_tokens = malloc((count_tokens_quotes(input) + 1) * sizeof(char *));
	if (!q_tokens)
		return (NULL);
	ptr = q_tokens;
	while (*input)
	{
		end = 0;
		end = quotes_end(input);
		if (end != 0)
		{
			*ptr = create_token(input, end);
			ptr++;
		}
		input += end;
	}
	*ptr = NULL;
	return (q_tokens);
}
