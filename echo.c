/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:00:43 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/28 14:34:05 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int do_echo(char **input, char **env)
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
			ft_printf("%s ", input[i++]);
		write(1, "\n", 2);
	}
	return 0;
}
