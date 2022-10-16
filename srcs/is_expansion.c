/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:48 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/16 22:51:02 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_expansion(char *str, int i)
{
	int	ret;

	ret = 0;
	if ((str[i] == '$' && ft_isalnum(str[i + 1]))
		|| (str[i] == '$' && str[i + 1] == '_'))
		ret = 1;
	return (ret);
}
