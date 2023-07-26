/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:56:41 by mviinika          #+#    #+#             */
/*   Updated: 2023/07/26 14:39:07 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_equalsign(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (ft_strchr(&input[i], '='))
			return (0);
	}
	return (1);
}

int	is_valid_char(char c)
{
	return (ft_isalnum(c)
		|| c == '_'
		|| c == '='
        || c == '/');
}

void	add_letter(char *word, char c, int *total, int *k)
{
	word[*k] = c;
	*total += 1;
	*k += 1;
}

int	can_be_added(char c, t_quotes *quots)
{
	return ((c && quots->closed == 0)
		|| (!ft_isspace(c) && quots->closed));
}

int	is_end_of_word(char c, t_quotes *quots)
{
	return ((ft_isspace(c) && quots->s_quote + quots->d_quote == 0)
		|| (ft_isspace(c) && quots->closed));
}
