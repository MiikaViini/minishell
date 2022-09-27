/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/27 11:21:41 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static char	*word(char *input, int i, int *total, char **env)
{
	int		k;
	char	*word;
	int		d_quote;
	int		s_quote;
	int		closed;

	s_quote = 0;
	k = 0;
	d_quote = 0;
	closed = 0;
	word = ft_strnew(200);
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
		if ((ft_isspace(input[i]) && s_quote + d_quote == 0)
			|| (ft_isspace(input[i]) && closed))
		{
			*total += 1;
			break ;
		}
		if ((input[i] == '~' && input[i + 1] == '$') || (input[i] == '$' && input[i + 1] != '\0'))
		{
			//i--;
			ft_printf("input [%s]\n", &input[i]);
			ft_strcat(word, replace_expansion(&input[i], env, &input[i]));
			*total += ft_strlen(&input[i]);
			ft_printf("tama word [%s]\n", word);
			if (!s_quote && !d_quote)
				return (word);
			ft_printf("tama word [%s]\n", word);
			i += ft_strlen(word);
			ft_printf("input [%s]\n", &input[i]);
		}
		if ((input[i] && closed == 0) || (!ft_isspace(input[i + 1]) && closed))
		{
			word[k++] = input[i++];
			*total += 1;
		}
	}
	if (word[0] == '~' && !closed && word[1] != '$')
		word = replace_expansion(word, env, &input[i]);
	//ft_printf("tama word [%s]\n", word);
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
	k = 0;
	while (trimmed_inp[i])
	{
		parsed[k++] = word(trimmed_inp, i, &total, env);
		i = total;
	}
	parsed[k] = NULL;
	ft_strdel(&trimmed_inp);
	return (parsed);
}