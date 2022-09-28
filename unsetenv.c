/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:30:06 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/28 21:13:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	do_unsetenv(char **input, char **env)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	k = -1;
	len = 0;
	while(input[++i])
	{
		while (env[++k])
		{
			len = ft_strlen(input[i]);
			if (ft_strncmp(env[k], input[i], len) == 0 && env[k][len] == '=')
			{
				ft_strdel(&env[k]);
				env[k] = env[k + 1];
				while(env[k])
				{
					env[k] = env[k + 1];
					k++;
				}
			}
		}
		k = 0;
	}
	return (0);
}
