/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 11:44:12 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	is_expansion(char *str)
{
	int ret;
	int	i;

	i = 0;
	ret = 0;
	if ((str[i] == '$' && ft_isalnum(str[i + 1])) || (str[i] == '$' && str[i + 1] == '_'))
		ret = 1;
	else if (str[i] == '~')
	{
		//if (str[i + 1] == '/' || str[i + 1] == '\0' || str[i + 1] == '+' || str[i + 1] == '-') //(str[i - 1] && str[i - 1] != '~')
			ret = 1;
	}
	return (ret);
}

static char *handle_expansions(char *input, char **env, int *total, int *i)
{
	char	*word;
	char	*expanded;

	word = ft_strnew(MAX_VAR);
	if (word == NULL)
		return (NULL);
	expanded = replace_expansion(input, env, input);
	ft_strcat(word, expanded);
	*total += ft_strlen(&input[*i]);
	ft_strdel(&expanded);
	ft_strdel(&input);
	return (word);
}

static char	*word(char *input, int i, int *total, char **env)
{
	int		k;
	char	*word;
	int		d_quote;
	int		s_quote;
	int		closed;
	int		expansion;

	expansion = 0;
	s_quote = 0;
	k = 0;
	d_quote = 0;
	closed = 0;
	word = ft_strnew(ft_strlen(input));
	(void)env;
	while (ft_isspace(input[i]) && (*total)++)
		i++;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			while (is_double_quote(input[i]) && s_quote == 0)
			{
				d_quote += 1;
				i++;
				*total += 1;
			}
			while (is_single_quote(input[i]) && !d_quote)
			{
				s_quote += 1;
				i++;
				*total += 1;
			}
			if (s_quote >= 2 || d_quote >= 2)
				closed = 1;
		}
		if (is_expansion(&input[i]))
			expansion = 1;
		if ((ft_isspace(input[i]) && s_quote + d_quote == 0)
			|| (ft_isspace(input[i]) && closed))
		{
			*total += 1;
			break ;
		}

		if ((input[i] && closed == 0) || (!ft_isspace(input[i]) && closed)) //((!ft_isspace(input[i + 1]) && closed) ||
		{
			word[k++] = input[i++];
			*total += 1;
		}
	}
	if (expansion && !s_quote)
		word = handle_expansions(word, env, total, &i);
	return (word);
}

char	**parse_input(char *input, char **env)
{
	int			i;
	int			k;
	static int	total;
	char		*trimmed_inp;
	char		**parsed;

	i = 0;
	k = 0;
	total = 0;
	parsed = (char **)malloc(sizeof(char *) * 100);
	trimmed_inp = ft_strtrim(input);
	if (!parsed || !trimmed_inp || !input)
		return (NULL);
	k = 0;
	while (trimmed_inp[i])
	{
		parsed[k++] = word(trimmed_inp, i, &total, env);
		if (!parsed[k - 1][0])
			ft_strdel(&parsed[--k]);
		i = total;
	}
	parsed[k] = NULL;
	ft_strdel(&trimmed_inp);
	return (parsed);
}
