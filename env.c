/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 23:27:33 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"



// static int check_validity_env(char **input)
// {
// 	int	i;
// 	int equ_sign;

// 	equ_sign = 0;
// 	i = 0;
// 	while (input[++i])
// 	{
// 		equ_sign = check_equalsign(input[i]);
// 		if (equ_sign)
// 			return (1);
// 	}
// 	return (0);
// }

static void exec_w_env(char **input, t_env *env, int i, int k)
{
	t_env	temp;
	char	*exec;
	
	exec = NULL;
	temp.env = ft_strarrndup(temp.env, env->env, ft_linecount(input));
	update_env(temp.env, input[0], "_");
	if (input[i])
	{
		exec = input[i];
		input[i] = NULL;
		do_setenv(input, &temp);
		input[i] = exec;
		if (!check_command(&input[i], env->path, temp.env))
			;
		else
			error_print(input[i], "env", E_NOEX);
	}
	else
	{
		do_setenv(input, &temp);
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

// while (env[k])
// {
// 	if (ft_strncmp(env[k], "OLDPWD=", 7) == 0)
// 	{
// 		ft_strdel(&env[k]);
// 		env[k] = env[k + 1];
// 		while(env[k])
// 		{
// 			env[k] = env[k + 1];
// 			k++;
// 		}
// 	}
// 	k++;
// }