/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:14:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/05 10:56:40 by mviinika         ###   ########.fr       */
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
	else if (access(input, X_OK) && stat(input, &buf) == -1)
	{
		ft_printf("minishell: cd: %s: Permission denied\n", input[1]);
		ret = 1;
	}
	else if(chdir(input) == -1)
	{
		ft_printf("minishell: cd: %s: Is not a directory\n", input);
		ret = 1;
	}
	return (ret);
}

void env_dir(char *input, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!input || ft_strncmp(input, "--", 2) == 0)
		{
			if (ft_strncmp(env[i], "HOME=", 5) == 0)
				if(!chdir(env[i] + 5))
					break ;
		}
		else if (ft_strncmp(input, "-", 1) == 0)
		{
			if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
				if (!chdir(env[i] + 7))
					break ;
		}
	}
	if(!env[i])
		ft_putstr_fd("minishell: cd: variable doesnt have a value\n", 2);
}

int do_cd(char **input, t_env *env)
{
	char		*old_cwd;
	char		*cwd;

	old_cwd = getcwd(NULL, 0);
	if (old_cwd == NULL)
		return (1);
	if(input[1] && !(ft_strncmp(input[1], "-", 1) == 0) && check_access(input[1]))
	{
		free(old_cwd);
		return (1);
	}
	else if (!input[1] || ft_strncmp(input[1], "-", 1) == 0)
		env_dir(input[1], env->env);
	cwd = getcwd(NULL, 0);
	update_env(env->env, cwd, "PWD");
	update_env(env->env, old_cwd, "OLDPWD");
	free(cwd);
	free(old_cwd);
	return (0);
}
