/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:46:13 by tpinto-e          #+#    #+#             */
/*   Updated: 2022/12/05 17:45:50 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_stack	*ft_lstnew(int value)
{
	t_stack	*list;

	list = (t_stack *) malloc(sizeof(t_stack));
	if (!list)
		return (NULL);
	list->value = value;
	list->next = NULL;
	return (list);
}
