
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:15:09 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/10 21:10:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

size_t	longest_var(char **env)
{
	size_t	longest;
	size_t len;
	size_t i;
	
	i = 0;
	longest = 0;
	len = 0;
	while(env[i])
	{
		len = ft_strlen(env[i]);
		if(len > longest)
			longest = len;
		i++;
	}
	return (longest);
}

// void	expand_and_concat(char *expanded, char **env, char *word, int *i)
// {
// 	int	len;
// 	int	k;
	
// 	len = 0;
// 	*i += 1;
// 	k = -1;
// 	while(ft_isalnum(word[len + *i]) || (!ft_isalnum(word[len + *i]) && word[len + *i] == '_'))
// 		len++;
// 	while(env[++k])
// 	{
// 		if (ft_strncmp(env[*k], &word[*i], len) == 0 && env[*k][len] == '=')
// 		{
// 			temp = ft_strjoin(expanded, env[k] + len + 1);
// 			ft_strdel(&expanded);
// 			expanded = ft_strdup(temp);
// 			ft_strdel(&temp);
// 		}
// 	}
// 	i += len;
// 	j = ft_strlen(expanded);
// 	len = 0;
// }





char	*expand_and_concat_tilde(char *expanded, char **env, char *word, int len)
{
	char	*temp;
	
	// temp = ft_strjoin(expanded, env[k] + len + 1);
	// ft_printf("temp [%s]\n",temp);
	// if (expanded)
	// 	ft_strdel(&expanded);
	// expanded = ft_strdup(temp);
	// ft_strdel(&temp);
	temp = ft_strdup(*env + len);
	if(expanded)
		ft_strdel(&expanded);
	expanded = ft_strjoin(temp, &word[1]);
	ft_strdel(&temp);
	return (expanded);
}

char	*replace_expansion(char *word, char **env, char *input)
{
	int		len;
	int		k;
	char 	*expanded;
	char 	*temp;
	
	expanded = ft_strnew(longest_var(env) + ft_strlen(input));
	(void)input;
	temp = NULL;
	len = 0;
	k = -1;
	// if (word[0] == '~' && word[1] == '$')
	// 	i++;
	// TILDE HANDLING //////////////***************************************************************
	if (word[0] == '~' && word[1] != '$')
	{
		if (word[1] == '/' || word[1] == '\0')
		{
			while (env[++k])
			{
				if (ft_strncmp(env[k], "HOME=", 5) == 0)
				{
					expanded = expand_and_concat_tilde(expanded, env + k, word, 5);
					//expand_and_concat(expanded, env, k, 4);
					// temp = ft_strdup(env[k] + 5);
					// ft_strdel(&expanded);
					// expanded = ft_strjoin(temp, &word[1]);
					// ft_strdel(&temp);
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
					expanded = expand_and_concat_tilde(expanded, env + k, &word[1],7);
					//expand_and_concat(expanded, env, k, 6);
					// temp = ft_strdup(env[k] + 7);
					// ft_strdel(&expanded);
					// expanded = ft_strjoin(temp, &word[2]);
					// ft_strdel(&temp);
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
					expanded = expand_and_concat_tilde(expanded, env + k, &word[1], 4);
					//expand_and_concat(expanded, env, k, 3);
					// temp = ft_strdup(env[k] + 4);
					// ft_strdel(&expanded);
					// expanded = ft_strjoin(temp, &word[2]);
					// ft_strdel(&temp);
					break ;
				}
			}
		}
		else
		{
			if (expanded)
				ft_strdel(&expanded);
			expanded = ft_strdup(user_expansion(word));
		}
	}
	// TILDE HANDLING ENDS//////////////***************************************************************
	else
		expanded = dollar_expansion(expanded, word, env, len);
	return (expanded);
}
