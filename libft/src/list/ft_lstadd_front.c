/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:49 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_lst)
{
	if (!lst || !new_lst)
		return ;
	new_lst->next = *lst;
	*lst = new_lst;
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
	ft_lstadd_front(&list, malloc(sizeof(t_list)));
	list->content = &x;
	ft_lstadd_front(&list, malloc(sizeof(t_list)));
	list->content = &y;
	printf("%d should be 5\n", *(int *)(list->content));
	printf("%d should be 20\n", *(int *)(list->next->content));
}
// cc ft_lstadd_front.c
*/