/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:15:09 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/16 13:39:10 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static size_t	longest_var(char **env)
{
	size_t	longest;
	size_t	len;
	size_t	i;

	i = 0;
	longest = 0;
	len = 0;
	while (env[i])
	{
		len = ft_strlen(env[i]);
		if (len > longest)
			longest = len;
		i++;
	}
	return (longest);
}

static char	*replace_expansion(char *word, char **env, char *input)
{
	char	*expanded;
	int		len;

	len = 0;
	expanded = ft_strnew(longest_var(env) + ft_strlen(input));
	if (word[0] == '~' && word[1] != '$')
		expanded = tilde_expansion(word, env, expanded);
	else
		expanded = dollar_expansion(expanded, word, env, len);
	return (expanded);
}

char	*handle_expansions(char *input, char **env, int *total, int *i)
{
	char	*expanded;

	expanded = replace_expansion(input, env, input);
	if (!expanded)
	{
		ft_strdel(&input);
		return (NULL);
	}
	*total += ft_strlen(&input[*i]);
	ft_strdel(&input);
	return (expanded);
}
