/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:40:14 by remarque          #+#    #+#             */
/*   Updated: 2024/01/10 14:48:23 by jecarval         ###   ########.fr       */
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
