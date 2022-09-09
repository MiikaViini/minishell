/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika < mviinika@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:07:24 by mviinika          #+#    #+#             */
/*   Updated: 2021/12/13 14:37:29 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **alst)
{
	t_list	*prv;
	t_list	*next;
	t_list	*curr;

	curr = *alst;
	prv = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prv;
		prv = curr;
		curr = next;
	}
	*alst = prv;
}
