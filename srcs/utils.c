/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:33:07 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/17 12:42:00 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_linecount(char **arr)
{
	size_t count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void free_strarr(char **strarr)
{
	int i;

	i = 0;
	if (!strarr && !strarr[i])
		return;
	while (strarr[i])
		ft_strdel(&strarr[i++]);
	free(strarr);
}

int is_single_quote(char c)
{
	return (c == '\'');
}

int is_double_quote(char c)
{
	return (c == '"');
}

int is_quote(char c)
{
	return (c == '\'' || c == '"');
}
