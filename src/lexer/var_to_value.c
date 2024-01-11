/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:42:56 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:42:57 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 0 = leave as is
// 1 = expand
// 2 = $?
// 3 = remove $ and following char (ex: echo $1)
static int	valid_expand(char *str, int pos)
{
	if (pos - 1 >= 0 && str[pos - 1] && str[pos - 1] == '\'')
		return (0);
	else if (str[pos + 1] && str[pos + 1] == '?')
		return (2);
	else if (str[pos + 1] && ft_isdigit(str[pos + 1]))
		return (3);
	else if (str[pos + 1] && ft_isalpha(str[pos + 1]))
		return (1);
	return (0);
}

static char	*fng_env_var(char *str, t_env *env)
{
	char	*env_str;
	char	*new_str;
	int		i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	new_str = (char *) malloc(sizeof(char) * i + 1);
	ft_memcpy(new_str, str, i);
	new_str[i] = 0;
	env_str = get_env_var(env, new_str);
	return (free(new_str), env_str);
}

// only possible options here are 3 (remove $ and following char) 
// and 1 (expand), the latter can happen where there is no 
// environmental variable with that name (ex: echo $PAT!H)
static char	*new_str_skip(char *str, int *pos, int option)
{
	auto size_t s = ft_strlen(str);
	auto char *new_str = (char *) malloc(sizeof(char) * (s));
	auto int i = *pos + 1;
	ft_memcpy(new_str, str, *pos);
	if (option == 3)
	{
		if (!str[*pos + 2])
		{
			new_str[s - 2] = 0;
			*pos = i - 3;
			return (free(str), new_str);
		}
		ft_memcpy(new_str + *pos, str + *pos + 2, s - *pos - 2);
		new_str[s - 2] = 0;
		*pos = i - 2;
		return (free(str), new_str);
	}
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	ft_memcpy(new_str + *pos, str + i, s - i);
	new_str[s - (i - *pos)] = 0;
	*pos = *pos - 1;
	if (str[i])
		*pos = i - (i - *pos);
	return (free(str), new_str);
}

// so as not to go over chars in the new string that i don't need to
// the address of i is passed and altered according to the size of append
// (or close enough at least)
static char	*new_str_vtv(char *str, char *appnd, int *pos, int option)
{
	auto size_t s = ft_strlen(str), t = ft_strlen(appnd);
	auto int i = *pos + 1;
	auto char *ret_str;
	if (appnd == NULL)
		return (new_str_skip(str, pos, option));
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	if (option == 2)
		i = *pos + 2;
	ret_str = (char *) malloc(sizeof(char) * (s + t - (i - *pos) + 1));
	ft_memcpy(ret_str, str, *pos);
	ft_memcpy(ret_str + *pos, appnd, t);
	ft_memcpy(ret_str + *pos + t, str + i, s - i + 1);
	ret_str[s + t - (i - *pos)] = 0;
	i = *pos + t - 1;
	*pos = i;
	return (free(appnd), free(str), ret_str);
}

char	*var_to_value(char *str, t_env *env, t_data *data)
{
	auto int i = -1, op = 0;
	auto char *new_str = ft_strdup(str), *change;
	while (new_str[++i])
	{
		if (new_str[i] == '$')
			op = valid_expand(new_str, i);
		else
			continue ;
		if (op == 1)
			change = ft_strdup(fng_env_var(new_str + i + 1, env));
		else if (op == 2)
			change = ft_itoa(data->ret_status);
		else if (op == 3)
			change = NULL;
		if (op)
			new_str = new_str_vtv(new_str, change, &i, op);
		if (i < 0 || i >= (int) ft_strlen(new_str))
			i = 0;
	}
	return (new_str);
}
