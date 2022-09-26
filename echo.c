/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:00:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/26 15:49:54 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int do_echo(char **input, char **env)
{
	int	i;
	int	k;
	int len;

	i = 1;
	k = 0;
	len = 0;
	if (!input[i])
		write(1, "\n", 2);	
	else
	{
		while (input[i])
		{
			if (input[i][0] == '$' && input[i][1])
			{
				while (env[k])
				{
					len = (int)ft_strlen(&input[i][1]);
					if (ft_strncmp(env[k], &input[i][1], len) == 0 && env[k][len] == '=')
						ft_printf("%s ", env[k] + (len + 1));
					k++;
				}
				k = 0;
			}
			else
				ft_printf("%s ", input[i]);
			i++;
		}
		write(1, "\n", 2);
	}
	return 0;
}
