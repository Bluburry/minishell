/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 18:44:15 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/05 19:04:01 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

void	ft_lstadd_back(t_stack **lst, t_stack *node)
{
	t_stack	*helper;

	if (!*lst && node)
		*lst = node;
	else if (*lst && node)
	{
		helper = ft_lstlast(*lst);
		helper->next = node;
	}
}
