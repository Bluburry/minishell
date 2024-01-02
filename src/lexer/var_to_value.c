/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:14:01 by ade-barr          #+#    #+#             */
/*   Updated: 2024/01/02 15:26:16 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_word_end(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && !ft_iswhitespace(str[i]))
	{
		if (str[i] == '$')
			count++;
		if (count == 2 || str[i] == '\\')
			break ;
		i++;
	}
	if (str[i - 1] && str[i - 1] == '$')
		i++;
	return (i);
}

static char	*store_word(char *str)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	i = find_word_end((str + i));
	word = malloc(sizeof(char) * i + 2);
	j = 0;
	str++;
	while (str[j] && j <= i && !ft_iswhitespace(str[j]))
	{
		if (str[j] == '"' || str[j] == '$' || str[j] == '\\')
			break ;
		word[j] = str[j];
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	*process_var(char *str, char *ret_str, t_env *env)
{
	if (str[1] && str[1] == '?')
		ret_str = ft_strjoin(ret_str, "EXIT_STATUS");
	else if (str[1] && str[1] == '$')
		ret_str = ft_strjoin(ret_str, "PRINT_PID");
	else if (str[1] && !ft_isalpha(str[1]))
	{
		ft_printf("Syntax_error\n");
		return (NULL);
	}
	else if (str[1] && str[1] == ' ')
		ret_str = ft_strjoin(ret_str, ft_substr(str, 0, 1));
	else if (get_env_var(env, store_word(str)))
		ret_str = ft_strjoin(ret_str, get_env_var(env, store_word(str)));
	return (ret_str);
}

char	*var_to_value(char *str, t_env *env)
{
	char	*ret_str;

	ret_str = ft_calloc(sizeof(char), 1);
	while (str[0])
	{
		if (str[0] && str[0] == '$')
		{
			if (!ft_iswhitespace(str[1]) && str[1])
			{
				ret_str = process_var(str, ret_str, env);
				str += find_word_end(str);
			}
			else
			{
				ret_str = ft_strjoin(ret_str, ft_substr(str, 0, 1));
				str++;
			}
		}
		else
		{
			ret_str = ft_strjoin(ret_str, ft_substr(str, 0, 1));
			str++;
		}
	}
	return (ret_str);
}
