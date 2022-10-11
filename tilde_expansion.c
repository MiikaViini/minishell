/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:50:39 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 21:16:34 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*expand_and_concat_tilde(char *expanded, char **env, char *word, int len)
{
	char	*temp;

	temp = ft_strdup(*env + len);
	if(expanded)
		ft_strdel(&expanded);
	expanded = ft_strjoin(temp, &word[1]);
	ft_strdel(&temp);
	return (expanded);
}

char	*handle_home(char *word, char **env, char *expanded)
{
	int	k;
	
	k = -1;
	while (env[++k])
		if (ft_strncmp(env[k], "HOME=", 5) == 0)
			expanded = expand_and_concat_tilde(expanded, env + k, word, 5);
	return (expanded);
}

char	*handle_oldpwd(char *word, char **env, char *expanded)
{
	int	k;
	
	k = -1;
	while (env[++k])
		if (ft_strncmp(env[k], "OLDPWD=", 7) == 0)
			expanded = expand_and_concat_tilde(expanded, env + k, &word[1], 7);
	return (expanded);
}

char	*handle_pwd(char *word, char **env, char *expanded)
{
	int	k;
	
	k = -1;
	while (env[++k])
		if (ft_strncmp(env[k], "PWD=", 4) == 0)
			expanded = expand_and_concat_tilde(expanded, env + k, &word[1], 4);
	return (expanded);
}

char *tilde_expansion(char *word, char **env, char *expanded)
{
	if (word[1] == '/' || word[1] == '\0')
		expanded = handle_home(word, env, expanded);
	else if (word[1] == '-')
		expanded = handle_oldpwd(word, env, expanded);
	else if (word[1] == '+')
		expanded = handle_pwd(word, env, expanded);
	else
	{
		if (expanded)
			ft_strdel(&expanded);
		expanded = ft_strdup(user_expansion(word));
	}
	return (expanded);
}