/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:47 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list;
	t_list	*temp_l;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		temp_l = list->next;
		del(list->content);
		free(list);
		list = temp_l;
	}
	*lst = 0;
}

/*
#include <stdio.h>

void	del(void *c)
{
	return ;
}

int	main(void)
{
	t_list	*list;
	int		x;
	int		y;

	x = 20;
	y = 5;
	list = malloc(sizeof(t_list));
	list->next = malloc(sizeof(t_list));
	list->next->next = 0;
	list->content = &x;
	list->next->content = &y;
	printf("%d should be 20\n", *(int *)(list->content));
	printf("%d should be 5\n", *(int *)(list->next->content));
	ft_lstclear(&list, del);
	printf("%p should be (nil)\n", list);
}
// cc ft_lstclear.c
*/