/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:15:09 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/30 09:33:35 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*replace_expansion(char *word, char **env, char *input)
{
	int		i;
	int		k;
	char 	*expanded;
	int		len;
	char 	*temp;
	int		j;

	expanded = ft_strnew(300);
	(void)input;
	j = 0;
	temp = NULL;
	i = 0;
	k = -1;
	len = 0;
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
					temp = ft_strdup(env[k] + 5);
					ft_strdel(&expanded);
					expanded = ft_strjoin(temp, &word[1]);
					ft_strdel(&temp);
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

					temp = ft_strdup(env[k] + 7);
					ft_strdel(&expanded);
					expanded = ft_strjoin(temp, &word[2]);
					ft_strdel(&temp);
					//exit(1);
					break ;
				}
				k++;
			}
		}
		else if (word[1] == '+')
		{
			while (env[++k])
			{
				if (ft_strncmp(env[k], "PWD=", 4) == 0)
				{
					temp = ft_strdup(env[k] + 4);
					ft_strdel(&expanded);
					expanded = ft_strjoin(temp, &word[2]);
					ft_strdel(&temp);
					break ;
				}
				k++;
			}
		}
		else
			expanded = ft_strdup(word);
	}
	// TILDE HANDLING ENDS//////////////***************************************************************
	else
	{
		while(word[i])
		{
			if (!is_expansion(&word[i]))
				expanded[j++] = word[i++];
			else
			{
				i++;
				while(ft_isalnum(word[len + i]))
					len++;
				while(env[++k])
				{
					if (ft_strncmp(env[k], &word[i], len) == 0 && env[k][len] == '=')
						ft_strcat(expanded, env[k] + len + 1);
				}
				i += len;
				j = ft_strlen(expanded);
				len = 0;
			}
			k = -1;
		}
	}
	return (expanded);
}
