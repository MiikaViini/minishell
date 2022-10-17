/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:39:14 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/17 11:57:18 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	set_shell_lvl(t_env *env)
{
	int		num;
	char	*temp;
	int		i;

	i = -1;
	temp = NULL;
	while (env->env[++i])
	{
		if (ft_strncmp(env->env[i], "SHLVL=", 6) == 0)
		{
			num = ft_atoi(env->env[i] + 6);
			num++;
			if (num >= 1000)
				num = 1;
			temp = ft_itoa(num);
			ft_strdel(&env->env[i]);
			env->env[i] = ft_strjoin("SHLVL=", temp);
			ft_strdel(&temp);
			return ;
		}
	}
	update_env(env->env, "1", "SHLVL");
}

void	get_env(t_env *dest, char **environ, int argc, char **argv)
{
	int		i;
	int		k;
	int		size;

	(void)argc;
	(void)argv;
	size = 3 + ft_linecount(environ);
	i = 0;
	k = -1;
	dest->env = (char **)ft_memalloc(sizeof(char *) * (size));
	if (!dest->env)
		exit(1);
	while (environ[++k])
	{
		if (ft_strncmp(environ[k], "OLDPWD=", 7) == 0)
			k++;
		dest->env[i++] = ft_strdup(environ[k]);
	}
	dest->env[i] = NULL;
	set_shell_lvl(dest);
}
