/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:42:27 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:42:28 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lexer(char *input, t_env *env, t_data *data)
{
	char	**tokens;

	if (!input || !(*input))
		return (NULL);
	tokens = tokens_init(input, env, data);
	data->strlist = tokens;
	return (tokens);
}
