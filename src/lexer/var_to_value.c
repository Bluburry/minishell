/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:14:01 by ade-barr          #+#    #+#             */
/*   Updated: 2024/01/03 16:37:55 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_word_end(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		if (count == 2 || str[i] == '|' || !(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '$'))
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
	char	*word;

	i = 0;
	i = find_word_end((str));
	word = ft_substr(str, 1 , i - 1);
	return (word);
}

static char	*process_var(char *str, char *ret_str, t_env *env, t_data *data)
{
	char	*ret_val;
	char	*word;

	word = store_word(str);
	if (str[1] && str[1] == '?')
	{
		ret_val = ft_itoa(data->ret_status);
		ret_str = ft_strjoin(ret_str, ret_val);
		free(ret_val);
	}
	else if (str[1] && str[1] == ' ')
		ret_str = ft_strjoin(ret_str, ft_substr(str, 0, 1));
	else if (get_env_var(env, word))
		ret_str = ft_strjoin(ret_str, get_env_var(env, word));
	free(word);
	return (ret_str);
}

char	*var_to_value(char *str, t_env *env, t_data *data)
{
	auto char *ret_str = ft_calloc(sizeof(char), 1), *tmp_str, *tmp_ret;
	while (str[0])
	{
		if (str[0] && str[0] == '$')
		{
			if (str[1] && (str[1] == '?' || ft_isalpha(str[1]) ))
			{
				tmp_ret = ret_str;
				ret_str = process_var(str, tmp_ret, env, data);
				str += find_word_end(str);
			}
			else
			{
				tmp_str = ft_substr(str, 0, 1);
				tmp_ret = ret_str;
				ret_str = ft_strjoin(tmp_ret, tmp_str);
				free(tmp_ret);
				free(tmp_str);
				str++;
			}
		}
		else
		{
			tmp_str = ft_substr(str, 0, 1);
			tmp_ret = ret_str;
			ret_str = ft_strjoin(tmp_ret, tmp_str);
			free(tmp_ret);
			free(tmp_str);
			str++;
		}
	}
	return (ret_str);
}
