/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 13:37:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 11:11:36 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	check_builtins(char **input, char **builtins, t_env *env)
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
	if (rb && !input[0])
		return (1);
	env->path = get_path(env->env);
	if (rb)
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
		error_print(input[0], NULL, E_NOTF);
	free_strarr(env->path);
	return (1);
}
