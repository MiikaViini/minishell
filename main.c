/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/16 14:28:31 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void	sgn_handler(int num)
// {
// 	(void)num;
// 	// if (num == SIGINT)
// 	// 	ft_putendl("\n$> ");
// 	signal(SIGINT, sgn_handler);
// }

int	is_single_quote(char c)
{
	return (c == '\'');
}

int	is_double_quote(char c)
{
	return (c == '"');
}

int	check_quotes(char *input)
{
	int		i;
	int		s_quote;
	int		d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !s_quote && !d_quote)
			s_quote = 1;
		else if (input[i] == '\'')
			s_quote = 0;
		else if (input[i] == '\"' && !d_quote && !s_quote)
			d_quote = 1;
		else if (input[i] == '\"')
			d_quote = 0;
		i++;
	}
	return (s_quote + d_quote);
}

char	*word(char *input, int i)
{
	int		k;
	char	*word;
	int		s_open;
	int		d_open;

	k = 0;
	s_open = 1;
	d_open = 1;
	word = ft_strnew(100);
	// while (ft_isspace(input[i]))
	// 	i++;
	while (input[i])
	{
		while (is_single_quote(input[i]) || is_double_quote(input[i]))
		{
			// if (is_single_quote(input[i]) && !is_double_quote(input[i]))
			// 	s_open += 1;
			// else if (is_double_quote(input[i]) && !is_single_quote(input[i]))
			// 	d_open += 1;
			// else
			// {
			// 	s_open = 0;
			// 	d_open = 0;
			// }
			i++;
		}
		// else if (is_double_quote(input[i]))
		// 	i++;
		word[k++] = input[i++];
	}
	word[k] = '\0';
	return (word);
}

char	**parse_input(char *input)
{
	int		i;
	int		k;
	char	**parsed;

	parsed = (char **)malloc(sizeof(char *) * 150);
	i = 0;
	k = 0;
	while (input[i])
	{
		parsed[k] = word(input, i);
		i += ft_strlen(parsed[k++]);
		ft_putnbr((int)ft_strlen(parsed[k]));
	}
	parsed[k] = NULL;
	ft_putnbr(k);
	return (parsed);
}

int	get_input(void)
{
	int		rb;
	char	buf[4096];
	char	**parsed_input;

	rb = 1;
	ft_memset(buf, '\0', 4096);
	parsed_input = 0;
	if (rb != 0)
	{
		rb = read(0, &buf, 4096);
		if (rb == -1)
			exit(1);
		if (check_quotes(buf))
			ft_putstr("invalid quoting, try again\n");
		else
			parsed_input = parse_input(buf);
		// if (rb != 0 && !ft_isspace(buf[0]))
		// 	parsed_input = ft_strsplitws(buf);
		// rb = check_builtin(parsed_input, rb, buf);
		while (parsed_input && *parsed_input)
		{
			write(1, "1", 1);
			ft_putstr(*parsed_input);
			parsed_input++;
			write(1, "1 ", 1);
		}
		ft_memset(buf, '\0', 4096);
		ft_strdel(parsed_input);
	}
	return (rb);
}

int	check_builtin(char **input, int rb, char *buf)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (ft_isspace(buf[0]))
		return (1);
	if (rb == 0 || !ft_strcmp(input[0], "exit"))
	{
		ft_putstr("exit\n");
		return (EXIT_SUCCESS);
	}
	else if (!ft_strcmp(input[0], "echo"))
	{
		if (!input[i])
			write(1, "\n", 2);
		while (input[i])
		{
			ft_putstr(input[i++]);
			write(1, "\n", 2);
		}
	}
	else if (!ft_strcmp(input[0], "cd"))
		ft_putstr("entering directory\n");
	else if (!ft_strcmp(input[0], "setenv"))
		ft_putstr("setting environment\n");
	else if (!ft_strcmp(input[0], "unsetenv"))
		ft_putstr("unsetting environment\n");
	else if (!ft_strcmp(input[0], "env"))
		ft_putstr("printing environment\n");
	return (1);
}

size_t	ft_linecount(char **arr)
{
	size_t	count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		ft_strdel(&env[i++]);
	free(env);
}

char	**get_env(char **dest, char **environ, int argc, char **argv)
{
	int		i;

	(void)argc;
	(void)argv;
	i = 0;
	dest = (char **)malloc(sizeof(char *) * ft_linecount(environ) + 1);
	while (environ[i])
	{
		dest[i] = ft_strdup(environ[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int	main(int argc, char **argv, char **environ)
{
	char	**env;
	int		i;
	int		rb;

	i = -1;
	rb = 1;
	env = NULL;
	env = get_env(env, environ, argc, argv);
	while (rb != 0)
	{
		ft_putstr("mish-1.0$ ");
		rb = get_input();
	}
	free_env(env);
	return (0);
}
