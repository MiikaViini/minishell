/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/05 14:51:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	check_builtins(char **input, char **builtins, t_env *env)
{
	int k;

	k = -1;
	while(builtins[++k])
	{
		if (ft_strequ(builtins[k], input[0]))
		{
			g_builtins[k](input, env);
			return (1);
		}
	}
	return (0);
}

int	check_exec(char **input, int rb, char **builtins, t_env *env)
{
	int	ret;

	ret = 0;
	if (!input[0] && rb)
		return (1);
	env->path = get_path(env->env);
	if (rb != 0)
		update_env(env->env, input[ft_linecount(input) - 1], "_");
	if (rb == 0 || !ft_strcmp(input[0], "exit"))
	{
		ft_putstr("exit\n");
		return (EXIT_SUCCESS);
	}
	else if (check_builtins(input, builtins, env))
		;
	else if (!check_command(input, env->path, env->env))
		;
	else
		ft_printf("minishell: %s: command not found\n", input[0]);
	free_strarr(env->path);
	return (1);
}