/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:00:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/03 11:44:26 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int do_echo(char **input, t_env *env)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	(void)env;
	if (!input[i])
		write(1, "\n", 2);
	else
	{
		while (input[i])
		{
			ft_putstr(input[i++]);
			write(1, " ", 1);
		}
		write(1, "\n", 2);
	}
	return 0;
}
