/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:28:50 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/16 22:51:02 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_print(char *word, char *command, char *e_msg)
{
	ft_putstr_fd(MSHELL, 2);
	ft_putstr_fd(": ", 2);
	if (command)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(word, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(e_msg, 2);
}
