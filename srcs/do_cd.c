/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:14:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/20 08:47:37 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_access(char *input)
{
	int ret;
	struct stat buf;

	ret = 0;
	if (!stat(input, &buf) && access(input, X_OK))
	{
		error_print(input, "cd", E_NOPERM);
		ret = 1;
	}
	else if (access(input, F_OK))
	{
		error_print(input, "cd", E_NOEX);
		ret = 1;
	}
	else if (chdir(input) == -1)
	{
		error_print(input, "cd", E_NODIR);
		ret = 1;
	}
	return (ret);
}

static int check_env_var(char *input, char **env)
{
	if ((!*env && !input) || (!*env && ft_strncmp(input, "--", 2) == 0))
	{
		error_print("HOME", "cd", E_NULLVAR);
		return (1);
	}
	else if (!*env && ft_strncmp(input, "-", 1) == 0)
	{
		error_print("OLDPWD", "cd", E_NULLVAR);
		return (1);
	}
	return (0);
}

static int env_dir(char *input, char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!input || ft_strncmp(input, "--", 2) == 0)
		{
			if (ft_strncmp(env[i], "HOME=", 5) == 0)
				if (!chdir(env[i] + 5))
					break;
		}
		else if (ft_strncmp(input, "-", 1) == 0)
		{
			if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
			{
				ft_putendl(env[i] + 7);
				if (!chdir(env[i] + 7))
					break;
			}
		}
	}
	if (check_env_var(input, &env[i]))
		return (1);
	return (0);
}

int do_cd(char **input, t_env *env)
{
	char old_cwd[MAX_PATH + 1];
	char cwd[MAX_PATH + 1];

	ft_memset(old_cwd, '\0', 1025);
	ft_memset(cwd, '\0', 1025);
	getcwd(old_cwd, MAX_PATH);
	if (input[1] && !(ft_strncmp(input[1], "-", 1) == 0) 
		&& check_access(input[1]))
		return (1);
	else if (!input[1] || ft_strncmp(input[1], "-", 1) == 0)
	{
		if (env_dir(input[1], env->env))
			return (1);
	}
	getcwd(cwd, MAX_PATH);
	if (cwd[0] == '\0')
		update_env(env->env, input[1], "PWD");
	else
		update_env(env->env, cwd, "PWD");
	update_env(env->env, old_cwd, "OLDPWD");
	return (0);
}
