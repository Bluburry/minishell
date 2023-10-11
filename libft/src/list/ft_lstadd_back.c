/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:52 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	t_list	*list;

	if (!lst || !new_lst)
		return ;
	if (!(*lst))
	{
		*lst = new_lst;
		return ;
	}
	list = *lst;
	while (list->next)
		list = list->next;
	list->next = new_lst;
}

/*
#include <stdio.h>

int	main(void)
{
	t_list	*list;
	int		x;
	int		y;

	x = 20;
	y = 5;
	list = 0;
	ft_lstadd_back(&list, malloc(sizeof(t_list)));
	list->content = &x;
	ft_lstadd_back(&list, malloc(sizeof(t_list)));
	list->next->content = &y;
	printf("%d should be 20\n", *(int *)(list->content));
	printf("%d should be 5\n", *(int *)(list->next->content));
}
// cc ft_lstadd_back.c
*/