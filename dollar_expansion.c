/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:20:37 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/10 20:50:27 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char *dollar_expansion(char *expanded, char *word, char **env)
{
	int		i;
	int		j;
	int		k;
	int		len;
	
	i = 0;
	j = 0;
	k = -1;
	len = 0;
	while(word[i])
	{
		if (!is_expansion(&word[i]) || (word[i] == '~' && is_expansion(&word[i + 1])))
			expanded[j++] = word[i++];
		else
		{
			len = var_name_len(word, len, ++i);
			while(env[++k])
				if (ft_strncmp(env[k], &word[i], len) == 0 && env[k][len] == '=')
					expanded = expand_and_concat(expanded, env, k, len);
			i += len;
			j = ft_strlen(expanded);
			len = 0;
			k = -1;
		}
	}
	return (expanded);
}