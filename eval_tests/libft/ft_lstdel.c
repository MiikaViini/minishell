/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika < mviinika@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:33:10 by mviinika          #+#    #+#             */
/*   Updated: 2021/12/10 10:06:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*temp;
	t_list	*list;

	list = *alst;
	while (list != NULL)
	{
		temp = list->next;
		del((list)->content, (list)->content_size);
		free(list);
		list = temp;
	}
	*alst = NULL;
}
