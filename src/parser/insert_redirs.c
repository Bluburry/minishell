/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <tpinto-e@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:43:14 by tpinto-e          #+#    #+#             */
/*   Updated: 2024/01/11 20:43:15 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_REDIR "Syntax Error: No file for redirection\n"

static inline bool	helper2_redirs(t_cmda *c, char **l, uint32_t	*i,
	t_etok type)
{
	if (is_name(l[*i + 1]))
	{
		c->tks[c->size++] = (t_tok){type, ft_strdup(remc(l[++(*i)])), NULL};
		return (true);
	}
	else
		return (printf(ERR_REDIR), false);
}

static inline bool	helper1_redirs(t_cmda *cmds, char **list, uint32_t	*i)
{
	if (ft_strncmp(">>", list[*i], 2) == 0)
	{
		if (helper2_redirs(cmds, list, i, r_append) == false)
			return (false);
	}
	else if (ft_strncmp("<<", list[*i], 2) == 0)
	{
		if (helper2_redirs(cmds, list, i, r_heredoc) == false)
			return (false);
	}
	else if (ft_strncmp(">", list[*i], 1) == 0)
	{
		if (helper2_redirs(cmds, list, i, r_out) == false)
			return (false);
	}
	else if (ft_strncmp("<", list[*i], 1) == 0)
	{
		if (helper2_redirs(cmds, list, i, r_in) == false)
			return (false);
	}
	return (true);
}

bool	insert_redirs(t_cmda *cmds, char **list, uint32_t n)
{
	uint32_t	i;

	i = 0;
	while (i < n)
	{
		if (helper1_redirs(cmds, list, &i) == false)
			return (false);
		i++;
	}
	return (true);
}

/* bool	insert_redirs(t_cmda *cmds, char **list, uint32_t n)
{
	uint32_t	i;

	i = 0;
	while (i < n)
	{
		if (ft_strncmp(">", list[i], 1) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_out, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		else if (ft_strncmp("<", list[i], 1) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_in, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		else if (ft_strncmp(">>", list[i], 2) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_append, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		else if (ft_strncmp("<<", list[i], 2) == 0)
		{
			if (list[i + 1] != NULL)
				cmds->tks[cmds->size++] = (t_tok){r_heredoc, list[++i], NULL};
			else
				return (printf(ERR_REDIR), false);
		}
		i++;
	}
	return (true);
} */
