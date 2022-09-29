/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/29 21:58:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int do_env(char **input, char **env)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (!input[1])
		while(env[k])
			ft_putendl(env[k++]);
	return (0);
}
