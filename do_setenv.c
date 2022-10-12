/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:48:51 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/12 14:57:49 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	sweep_input(char **input, int equ_sign)
{
	int	i;
	int	k;
	
	i = 0;
	while (input[++i])
	{
		k = -1;
		equ_sign = check_equalsign(input[i]);
		if (equ_sign)
		{
			error_print(input[i], "setenv",E_ARGNOTVAL);
			return (1);
		}
		while(input[i][++k])
		{
			if(!is_valid_char(input[i][k]))
			{
				error_print(input[i], "setenv", E_NOTALNUM);
				return(1);
			}
		}
	}
	return (0);
}

static int check_validity(char **input)
{
	int	ret;
	int equ_sign;
	int	i;

	i = 0;
	equ_sign = 0;
	ret = 0;
	while(input[++i])
	{
		if (input[i] && !ft_isalpha(input[i][0]))
		{
			error_print(input[0], "setenv",E_NOTVAL);
			return (1);
		}
	}
	ret = sweep_input(input, equ_sign);
	return (ret);
}

static int	find_env(char *input, t_env *env, int *added, int *k)
{
	int	var_len;
	
	var_len = 0;
	while(env->env[*k])
	{
		while(ft_strchr(&input[var_len], '='))
			var_len++;
		if (ft_strncmp(env->env[*k], input, var_len) == 0 
			&& env->env[*k][var_len - 1] == '=')
		{
			ft_strdel(&env->env[*k]);
			env->env[*k] = ft_strdup(input);
			*added = 1;
			break ;
		}
		*k += 1;
	}
	return (*added);
}

int	do_setenv(char **input, t_env *env)
{
	int	i;
	int	k;
	int	added;

	k = 0;
	i = 0;
	if (check_validity(input))
		return (1);
	while(input[++i])
	{
		added = 0;
		added = find_env(input[i], env, &added, &k);
		if (!added)
		{
			env->env[k++] = ft_strdup(input[i]);
			env->env[k] = NULL;
		}
	}
	return 0;
}
