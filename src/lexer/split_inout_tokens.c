/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_inout_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:40:29 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:48:38 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_inouts(char *str, char c)
{
	int	len;

	len = 0;
	while (*str)
	{
		str += move_in_str(str, c);
		if (*str == c && *(str + 1) == c)
		{
			syntax_error(1, c);
			return (-1);
		}
		if (*(str - 1) == c)
			len++;
		if (*(str - 1) == c && *str == c)
			str++;
	}
	return (len);
}

int	count_inout_tokens(char **input)
{
	char	*tmp;
	int		rtn;

	auto int len = 0;
	auto int i = -1;
	while (input[++i])
	{
		tmp = input[i];
		if (*tmp == '\'' || *tmp == '\"')
			len++;
		else
		{
			if (*tmp != '<' && *tmp != '>')
				len++;
			rtn = count_inouts(tmp, '<') + count_inouts(tmp, '>');
			if (rtn == -1)
				return (-1);
			if (rtn > 0)
				if (tmp[ft_strlen(tmp) - 1] != '<'
					&& tmp[ft_strlen(tmp) - 1] != '>')
					len++;
			len += rtn;
		}
	}
	return (len);
}

char	**tokenize_inout(char *input, char **ptr)
{
	int		end;
	char	*str;

	str = input;
	while (*str)
	{
		end = 0;
		if ((*str == '<' && *(str + 1) == '<')
			|| (*str == '>' && *(str + 1) == '>'))
			end = 2;
		else if (*str == '<' || *str == '>')
			end = 1;
		else
		{
			while (str[end] && str[end] != '<' && str[end] != '>')
				end++;
		}
		*ptr = create_token(str, end);
		if (**ptr)
			ptr++;
		else
			free(*ptr);
		str += end;
	}
	return (ptr);
}

char	**split_inout_tokens(char **input)
{
	char	**tokens;
	char	**ptr;
	int		flag;
	int		count;

	count = count_inout_tokens(input);
	if (count == -1)
		return (NULL);
	tokens = malloc((count + 1) * sizeof(char *));
	if (!tokens)
		return (0);
	ptr = tokens;
	while (*input)
	{
		flag = 0;
		ptr = check_for_quotes(*input, ptr, &flag);
		if (flag == 0)
			ptr = tokenize_inout(*input, ptr);
		input++;
	}
	*ptr = NULL;
	return (tokens);
}
