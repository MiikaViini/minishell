/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:48:51 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/10 13:30:22 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int check_equalsign(char *input)
{
	int i;

	i = -1;
	while (input[++i])
	{
		if(ft_strchr(&input[i], '='))
			return(0);
	}
	return (1);
}

int	is_valid_char(char c)
{
	return (!ft_isalnum(c)
		|| (ft_isalnum(c) && c != '_')
		|| (ft_isalnum(c) && c != '='));
}

int check_validity(char **input)
{
	int	i;
	int	k;
	int equ_sign;

	equ_sign = 0;
	i = 0;
	k = -1;
	if (input[1] && !ft_isalpha(input[1][0]))
	{
		error_print(input[i], "setenv",E_NOTVAL);
		return (1);
	}
	while (input[++i])
	{
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
		k = 0;
	}
	return (0);
}

int	do_setenv(char **input, t_env *env)
{
	int	i;
	int	k;
	int	var_len;
	int	added;
	//int ret = 0;
	// char **temp;

	i = 0;
	k = 0;
	added = 0;
	var_len = 0;

	// free_strarr(env->env);
	// temp = (char**)malloc(sizeof(char *) * 1000);

	// temp = strarrdup(env->env);
	// env->env = strarrdup(temp);
	if (check_validity(input))
		return (1);
	while(input[++i])
	{
		while(env->env[k])
		{
			//ft_printf("index k:%d, input :%s env :%s\n", k, input[i], env->env[k]);
			while(ft_strchr(&input[i][var_len], '='))
				var_len++;
			if (ft_strncmp(env->env[k], input[i], var_len) == 0 && env->env[k][var_len - 1] == '=')
			{
				ft_strdel(&env->env[k]);
				env->env[k] = ft_strdup(input[i]);
				added = 1;
				break ;
			}
			k++;
		}
		if (!added)
		{
			//ft_printf("%d", k);
			env->env[k++] = ft_strdup(input[i]);
			env->env[k] = NULL;
		}
		added = 0;
		var_len = 0;
		k = 0;
	}
	//env->env[k] = NULL;
	// exit(1);
	return 0;
}
