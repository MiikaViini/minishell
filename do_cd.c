/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:14:35 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/14 10:51:09 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	check_access(char *input, t_env *env, char *old_cwd)
{
	int			ret;
	struct stat	buf;

	ret = 0;
	(void)env;
	(void)old_cwd;
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

static void	env_dir(char *input, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (!input || ft_strncmp(input, "--", 2) == 0)
		{
			if (ft_strncmp(env[i], "HOME=", 5) == 0)
				if (!chdir(env[i] + 5))
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
	if ((!env[i] && !input) || (!env[i] && ft_strncmp(input, "--", 2) == 0))
		error_print("HOME", "cd", E_NULLVAR);
	else if (!env[i] && ft_strncmp(input, "-", 1) == 0)
		error_print("OLDPWD", "cd", E_NULLVAR);
}

int	do_cd(char **input, t_env *env)
{
	char		old_cwd[MAX_PATH + 1];
	char		cwd[MAX_PATH + 1];

	ft_memset(old_cwd, '\0', 1025);
	ft_memset(cwd, '\0', 1025);
	getcwd(old_cwd, MAX_PATH);
	if (input[1] && !(ft_strncmp(input[1], "-", 1) == 0)
		&& check_access(input[1], env, old_cwd))
		return (1);
	else if (!input[1] || ft_strncmp(input[1], "-", 1) == 0)
		env_dir(input[1], env->env);
	getcwd(cwd, MAX_PATH);
	if (ft_strcmp(cwd, old_cwd))
		update_env(env->env, old_cwd, "OLDPWD");
	update_env(env->env, cwd, "PWD");
	return (0);
}
