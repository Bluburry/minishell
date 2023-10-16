/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:26:35 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/15 21:25:01 by jecarval         ###   ########.fr       */
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

char	**token_split(char *input, t_input *in)
{
	char	**tokens;
	char	**ptr;
	char	*tmp;
	int		len;

	tmp = ft_strtrim(input, " \a\b\t\n\v\f\r");
	input = tmp;
	len = 0;
	if (in->d_quote > 1 || in->s_quote > 1)
		split_quotes(input);
	return (tokens);
}

void	parser(char *input)
{
	char	**tokens;
	t_input	in;

	if (!input || !(*input))
		return ;
	in = (t_input){0};
	scan_input(input, &in);
	tokens = token_split(input, &in);
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}
