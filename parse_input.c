/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:14:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/12 14:47:25 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int	is_end_of_word(char c, t_quotes *quots)
{
	return((ft_isspace(c) && quots->s_quote + quots->d_quote == 0)
			|| (ft_isspace(c) && quots->closed));
}

static void	initialise_q_struct(t_quotes *quotes)
{
	quotes->s_quote = 0;
	quotes->d_quote = 0;
	quotes->closed = 0;
}

static void	rem_quote(t_quotes *quots, char *input, int *tot, int *i)
{
	if (is_quote(input[*i]))
	{
		while (is_double_quote(input[*i]) && quots->s_quote == 0)
		{
			quots->d_quote += 1;
			*i += 1;
			*tot += 1;
		}
		while (is_single_quote(input[*i]) && !quots->d_quote)
		{
			quots->s_quote += 1;
			*i += 1;
			*tot += 1;
		}
		if (quots->s_quote >= 2 || quots->d_quote >= 2)
			quots->closed = 1;
	}
}

static char	*word(char *input, int i, int *total, char **env)
{
	int			k;
	char		*word;
	int			expansion;
	t_quotes	quots;

	initialise_q_struct(&quots);
	expansion = 0;
	k = 0;
	word = ft_strnew(ft_strlen(input));
	while (ft_isspace(input[i]) && (*total)++)
		i++;
	while (input[i])
	{
		rem_quote(&quots, input, total, &i);
		if (is_expansion(&input[i]))
			expansion = 1;
		if (is_end_of_word(input[i], &quots) && (*total)++)
			break ;
		if (can_be_added(input[i], &quots))
			add_letter(word, input[i++], total, &k);
	}
	if (expansion && !quots.s_quote)
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
