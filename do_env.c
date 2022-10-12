/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/12 15:58:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void try_execute(char **input, int *i, t_env *temp, t_env *env)
{
	char	*exec;
	
	exec = input[*i];
	input[*i] = NULL;
	if(do_setenv(input, temp))
		;
	input[*i] = exec;
	if (!check_command(&input[*i], env->path, temp->env))
		;
	else
		error_print(input[*i], "env", E_NOEX);
}

static void exec_w_env(char **input, t_env *env, int i, int k)
{
	t_env	temp;
	
	temp.env = ft_strarrndup(temp.env, env->env, ft_linecount(input));
	update_env(temp.env, input[0], "_");
	if (input[i])
		try_execute(input, &i, &temp, env);
	else
	{
		if(do_setenv(input, &temp))
			;
		else
			while(temp.env[++k])
				ft_putendl(temp.env[k]);
	}
	free_strarr(temp.env);
}

int do_env(char **input, t_env *env)
{
	int		i;
	int		k;

	i = 0;
	k = -1;
	if (!input[1])
		while(env->env[++k])
			ft_putendl(env->env[k]);
	else
	{
		while(input[++i])
			if (check_equalsign(input[i]))
				break ;
		k = -1;
		exec_w_env(input, env, i, k);
	}
	update_env(env->env, input[ft_linecount(input) - 1], "_");
	return (0);
}