/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:14:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/04 13:36:51 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	check_access(char *input)
{
	int ret;
	struct stat buf;

	ret = 0;

	if (access(input, F_OK))
	{
		ft_printf("minishell: cd: %s: No such file or folder\n", input);
		ret = 1;
	}
	else if (access(input, X_OK) && stat(input, &buf))
	{
		ft_printf("minishell: cd: %s: Permission denied\n", input[1]);
		ret = 1;
	}
	else if(chdir(input) == -1)
		ft_printf("minishell: cd: %s: Is not a directory\n", input);
	return (ret);
}

int do_cd(char **input, t_env *env)
{
	//char		cwd[MAX_PATH + 1];
	int			i;

	i = -1;
	//ft_memset(cwd, '\0', MAX_PATH + 1);

	update_env(env->env, getcwd(NULL, 0), "OLDPWD");
	if(input[1] && check_access(input[1]))
		return (1);
	else if (!input[1])
	{
		while (env->env[++i])
			if (ft_strncmp(env->env[i], "HOME=", 5) == 0)
				if (!chdir(env->env[i] + 5))
					break ;
		if(!env->env[i])
			ft_printf("minishell: cd: HOME not set\n");
	}
	update_env(env->env, getcwd(NULL, 0), "PWD");
	return (0);
}
