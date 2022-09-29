/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:48:51 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/29 17:19:52 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int check_equalsign(char *input)
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

static int check_validity(char **input)
{
	int	i;
	int	k;
	int equ_sign;

	equ_sign = 0;
	i = 0;
	k = -1;
	if (!ft_isalpha(input[1][0]))
	{
		ft_putstr_fd("minishell: setenv: variable name must begin with a letter.\n", 2);
		return (1);
	}
	while (input[++i])
	{
		equ_sign = check_equalsign(input[i]);
		if (equ_sign)
		{
			ft_putstr_fd("minishell: setenv: please enter arguments in format 'name=value'.\n", 2);
			return (1);
		}
		while(input[i][++k])
		{
			if(!is_valid_char(input[i][k]))
			{
				ft_putstr_fd("minishell: setenv: variable name must contain alphanumeric characters.\n", 2);
				return(1);
			}
		}
		k = 0;
	}
	return (0);
}

int	do_setenv(char **input, char **env)
{
	int	i;
	int	k;
	int	arr_len;
	int	var_len;
	int	added;

	i = 0;
	k = -1;
	added = 0;
	arr_len = 0;
	var_len = 0;
	if (check_validity(input))
		return (1);
	while(env[++k])
		arr_len++;
	k = -1;
	while(input[++i])
	{
		while(env[++k])
		{
			while(ft_strchr(&input[i][var_len], '='))
				var_len++;
			if (ft_strncmp(env[k], input[i], var_len) == 0 && env[k][var_len - 1] == '=')
			{
				ft_strdel(&env[k]);
				env[k] = ft_strdup(input[i]);
				added = 1;
			}
		}
		if (!added)
			env[arr_len++] = ft_strdup(input[i]);
		k = 0;
		added = 0;
		var_len = 0;
	}
	env[arr_len] = NULL;
	return 0;
}
