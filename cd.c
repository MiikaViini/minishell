/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:14:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/03 09:48:20 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int do_cd(char **input, char **env)
{
	char		cwd[MAX_PATH + 1];
	struct stat buf;
	int			i;

	i = 0;
	ft_memset(cwd, '\0', MAX_PATH + 1);
	getcwd(cwd, MAX_PATH);
	update_env(env, cwd, "OLDPWD");
	if (stat(input[1], &buf) == -1 || !S_ISDIR(buf.st_mode) || input[2])
	{
		return (-1);
	}
	else
	{
		if (access(input[1], X_OK) == -1)
			ft_printf("minishell: %s: %s: permission denied", input[0], input[1]);
		else if(chdir(input[1]) == -1)
			ft_printf("minishell: %s: %s: failed for some reason", input[0], input[1]);
		else
		{
			getcwd(cwd, MAX_PATH);
			update_env(env, cwd, "PWD");
		}
	}
	return (0);
}
