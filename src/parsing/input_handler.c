/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarval <jecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:16:35 by jecarval          #+#    #+#             */
/*   Updated: 2023/10/15 15:08:01 by jecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	scan_input_inout(char *input, t_input *in)
{
	if (*input == '<' && *(input + 1) != '<')
		in->s_red_in++;
	if (*input == '>' && *(input + 1) != '>')
		in->s_red_out++;
	if (*input == '<' && *(input + 1) == '<')
	{
		in->d_red_in++;
		return (2);
	}
	if (*input == '>' && *(input + 1) == '>')
	{
		in->d_red_out++;
		return (2);
	}
	return (1);
}

void	find_pipe_problems(char *input, t_input *in)
{
	int	flag;
	int	i;

	i = 0;
	while (i++ < in->pipe)
	{
		flag = 0;
		while (*input && *input != '|')
		{
			if (*input != '|' && is_token_end(*input) == 0)
				flag = 1;
			input++;
		}
		if (flag == 0)
			syntax_error('|');
		input++;
	}
}

void	find_input_problems(char *input, t_input *in)
{
	if (in->d_quote % 2 != 0 || in->d_quote % 2 != 0)
	{
		printf("Error: unclosed quotes\n");
		waiting_for_input();
	}
	find_pipe_problems(input, in);
	//!! FIND REDIRECT PROBLEMS. WHAT ARE THE PROBLEMS??
}

void	scan_input(char *input, t_input *in)
{
	t_input	*tmp;

	tmp = input;
	while (*input)
	{
		if (*input == '\"')
			in->d_quote++;
		if (*input == '\'')
			in->s_quote++;
		if (*input == '$')
			in->dollar++;
		if (*input == '|')
			in->pipe++;
		input = input + scan_input_inout(input, in);
	}
	find_input_problems(tmp, in);
}
