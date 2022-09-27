/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:15:09 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/27 13:16:34 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*replace_expansion(char *word, char **env, char *input)
{
	int		i;
	int		k;
	char 	*expanded;
	int		len;

	expanded = NULL;
	i = 1;
	k = -1;
	(void)input;
	len = 1;
	if (word[0] == '~' && word[1] == '$' && len++)
		i++;
	// TILDE HANDLING //////////////***************************************************************
	if (word[0] == '~' && word[1] != '$')
	{
		
		if (word[1] == '/' || word[1] == '\0')
		{
			while (env[++k])
			{
				if (ft_strncmp(env[k], "HOME=", 5) == 0)
				{
					expanded = ft_strdup(env[k] + 5);
					expanded = ft_strjoin(expanded, &word[1]);
					break ;
				}
			}
		}
		else if (word[1] == '-')
		{
			while (env[++k])
			{
				if (ft_strncmp(env[k], "OLDPWD=", 7) == 0)
				{
					expanded = ft_strdup(env[k] + 7);
					expanded = ft_strjoin(expanded, &word[2]);
					break ;
				}
				k++;
			}
			return (word);
		}
		else if (word[1] == '+')
		{
			while (env[++k])
			{
				if (ft_strncmp(env[k], "PWD=", 4) == 0)
				{
					expanded = ft_strdup(env[k] + 4);
					expanded = ft_strjoin(expanded, &word[2]);
					break ;
				}
				k++;
			}
		}
		else
			return (word);
	}
	// TILDE HANDLING ENDS//////////////***************************************************************
	else
	{
		ft_printf("[%s]\n", &word[len]);
		while(word[len + i] && !ft_isspace(word[len + i]) && !is_quote(word[len + i]))
			len++;
		ft_printf("%d\n",len);
		while (env[++k])
		{
			if (ft_strncmp(env[k], &word[i], len) == 0 && env[k][len] == '=')
			{
				expanded = ft_strdup(env[k] + len + 1);
				ft_printf("%s\n",expanded);
				expanded = ft_strjoin(expanded, &word[len]);
				return (expanded);
			}
		}
		expanded = ft_strnew(1);
	}
	//free(word);
	return (expanded);
}