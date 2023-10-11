/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remarque <remarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:12:40 by remarque          #+#    #+#             */
/*   Updated: 2023/04/17 19:53:23 by remarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
#include <stdio.h>

void	f(void *c)
{
	*(int *)c += 2;
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
	ft_lstiter(list, f);
	printf("%d should be 22\n", *(int *)(list->content));
	printf("%d should be 7\n", *(int *)(list->next->content));
}
// cc ft_lstiter.c
*/