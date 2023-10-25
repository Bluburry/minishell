/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque < remarque@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:40:31 by remarque          #+#    #+#             */
/*   Updated: 2023/10/24 13:51:24 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdint.h>

// an enum that decides wether the token is a name or an operator
typedef enum e_etok
{
	name,
	r_out,
	r_in,
	r_append,
	r_heredoc,
}	t_etok;

// a token read by the parser
typedef struct s_tok
{
	t_etok		type;
	uint32_t	left_s_idx;
	uint32_t	right_s_idx;
	uint32_t	left_e_idx;
	uint32_t	right_e_idx;
}	t_tok;

// dynamically allocated list of tokens
typedef struct s_tlist
{
	t_tok		*tokens;
	uint32_t	size;
	uint32_t	cap;
}	t_tlist;
