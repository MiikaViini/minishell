/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:14:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/12 10:46:18 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	check_access(char *input, t_env *env, char *old_cwd)
{
	int ret;
	struct stat buf;

	ret = 0;
	if ((!lstat(input, &buf) && access(input, X_OK)) 
		|| (!lstat(input, &buf) && access(input, R_OK))) 
	{
		error_print(input, "cd", E_NOPERM);
		ret = 1;
	}
	else if (access(input, F_OK))
	{
		error_print(input, "cd", E_NOEX);
		ret = 1;
	}
	else if(chdir(input) == -1)
	{
		error_print(input, "cd", E_NODIR);
		ret = 1;
	}
	if (!ret)
		update_env(env->env, old_cwd, "OLDPWD");
	return (ret);
}

static void env_dir(char *input, char **env)
{
	int		i;

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
			{
				ft_putendl(env[i] + 7);
				if (!chdir(env[i] + 7))
					break ;
			}
		}
	}
	if((!env[i] && !input) || (!env[i] && ft_strncmp(input, "--", 2) == 0))
		error_print("HOME", "cd", E_NULLVAR);
	else if (!env[i] && ft_strncmp(input, "-", 1) == 0)
		error_print("OLDPWD", "cd", E_NULLVAR);
}



int do_cd(char **input, t_env *env)
{
	char		*old_cwd;
	char		*cwd;

	old_cwd = getcwd(NULL, 0);
	if (old_cwd == NULL)
		return (1);
	if(input[1] && !(ft_strncmp(input[1], "-", 1) == 0) && check_access(input[1], env, old_cwd))
	{
		free(old_cwd);
		return (1);
	}
	else if (!input[1] || ft_strncmp(input[1], "-", 1) == 0)
		env_dir(input[1], env->env);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(EXIT_FAILURE);
	update_env(env->env, cwd, "PWD");
	free(cwd);
	free(old_cwd);
	return (0);
}
