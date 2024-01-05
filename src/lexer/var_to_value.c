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
#include <stddef.h>

// 0 = leave as is
// 1 = expand
// 2 = $?
// 3 = remove $
static int	valid_expand(char *str, int pos)
{
	if (((str[pos - 1] && str[pos - 1] == '\'')) || \
		((str[pos + 1] && ft_iswhitespace(str[pos + 1]))) || \
		!str[pos + 1] || str[pos + 1] == '$')
		return (0);
	else if (str[pos + 1] && str[pos + 1] == '?')
		return (2);
	else if (str[pos + 1] && !ft_isalpha(str[pos + 1]))
		return (3);
	// if (ft_isdigit(str[pos + 1]) || str[pos + 1] == '"' || str[pos + 1] == '\'')
		// return (3);
	// pos++;
	// while (str[pos] && !ft_iswhitespace(str[pos]))
	// {
		// if
	// }
	return (1);
}

static char	*fng_env_var(char *str, t_env *env)
{
	char	*env_str;
	char	*helper;
	int		i;

	i = 0;
	// while (str[i] && !ft_iswhitespace(str[i]) && 
		// str[i] != '\'' && str[i] != '"')
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	helper = (char *) malloc(sizeof(char) * i + 1);
	ft_memcpy(helper, str, i);
	helper[i] = 0;
	env_str = get_env_var(env, helper);
	return (free(helper), env_str);
}

static char	*new_str_vtv(char *str, char *appnd)
{
	auto size_t s = ft_strlen(str), t = ft_strlen(appnd);
	auto int i = 0, j;
	auto char *ret_str;
	if (appnd == NULL)
		return (ft_strdup(str));
	while (str[i] && str[i] != '$')
		i++;
	while (str[i] && str[i] == '$')
		i++;
	j = i;
	// while (str[j] && !ft_iswhitespace(str[j]) && 
		// str[j] != '\'' && str[j] != '"')
	while (str[j] && (ft_isalpha(str[j]) || ft_isdigit(str[j])))
		j++;
	ret_str = (char *) malloc(sizeof(char) * (s + t - (j - i) + 1));
	ft_memcpy(ret_str, str, i);
	ft_memcpy(ret_str + i, appnd, t);
	ft_memcpy(ret_str + i + t, str + j, s - j + 1);
	return (free(appnd), ret_str);
}

char	*var_to_value(char *str, t_env *env, t_data *data)
{
	auto int i = -1, op = 0;
	auto char *helper, *helper2;
	while (str[++i] && op == 0)
		if (str[i] == '$')
			op = valid_expand(str, i);
	if (!str[i] || (str[i] && op == 0))
		return (ft_strdup(str));
	if (op == 2)
		helper = ft_itoa(data->ret_status);
	else
		helper = ft_strdup(fng_env_var(str + i, env));
	helper = new_str_vtv(str, helper);
	i = 0;
	while (helper[i] && helper[i] != '$')
		i++;
	if (!helper[i] || op == 0)
		return (helper);
	helper2 = var_to_value(helper, env, data);
	return (free(helper), helper2);
}
