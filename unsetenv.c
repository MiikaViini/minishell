/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:30:06 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/03 15:27:25 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	do_unsetenv(char **input, t_env *env)
{
	int	i;
	int	k;
	int	len;

	i = -1;
	k = 0;
	len = 0;
	while(input[++i])
	{
		while (env->env[k])
		{
			len = ft_strlen(input[i]);
			if (ft_strncmp(env->env[k], input[i], len) == 0 && env->env[k][len] == '=')
			{
				ft_strdel(&env->env[k]);
				env->env[k] = env->env[k + 1];
				while(env->env[k])
				{
					env->env[k] = env->env[k + 1];
					k++;
				}
			}
			k++;
		}
		k = 0;
	}
	return (0);
}
