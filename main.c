/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/21 15:20:27 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void	sgn_handler(int num)
// {
// 	(void)num;
// 	if (num == SIGINT)
// 		ft_putendl("\n$> ");
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

int is_quote(char c)
{
	return (c == '\'' || c == '"');
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
char *ft_sep(char *str, const char delim)
{
	int		i;
	int		k;
	int		delim_c;
	char	*separated;

	separated = ft_strnew(ft_strlen(str));
	i = 0;
	k = 0;
	delim_c = 0;
	while (str && str[i] && delim_c < 2)
	{
		if (str[i] == delim)
		{
			delim_c++;
			i++;
		}
		separated[k++] = str[i++];
	}
	return (separated);
}
/* Split string to words, whitespace, singlequote and doublequote
** works as separator
*/
char	*word(char *input, int i, int *total)
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
	while (ft_isspace(input[i]))
		i++;
//	ft_printf("word [%s]\n", &input[i]);
	while (input[i] && !closed)
	{
		if (is_quote(input[i]))
		{
		//	ft_printf("%c\n", input[i]);
		//	ft_printf("d %d\n", d_quote);
			//ft_printf("s %d\n", s_quote);
			while (is_double_quote(input[i]) && s_quote == 0)
			{
				d_quote += 1;
				i++;
			}
		//ft_printf("%d\n", d_quote);
			//ft_printf("%d\n", s_quote);
			while (is_single_quote(input[i]) && !d_quote)
			{
				s_quote += 1;
				i++;
			}
			if (s_quote == 2 || d_quote == 2)
				closed = 1;
		}
		if (ft_isspace(input[i]) && s_quote + d_quote == 0)
		{
			//(*total)--;
			//ft_printf("%d\n", s_quote + d_quote);
			break ;
		}
		if (input[i] && !closed && (*total)++)
			word[k++] = input[i++];
	}
	//ft_printf("word [%s]\n", word);
	return (word);
}

char	**parse_input(char *input)
{
	int		i;
	int		k;
	static int  total;
	char	*trimmed_inp;
	char	**parsed;

	i = 0;
	k = 0;
	total = 0;
	parsed = (char **)malloc(sizeof(char *) * 100);
	trimmed_inp = ft_strtrim(input);
	k = 0;
	while (trimmed_inp[i])
	{
		parsed[k++] = word(trimmed_inp, i, &total);
		i += total; //ft_strlen(parsed[k++]) + 1;
		if(k)
			total -= 1;
	}
	parsed[k] = NULL;
	ft_strdel(&trimmed_inp);
	return (parsed);
}

void free_parsed_input(char **p_input)
{
	int i;

	i = -1;
	if (!p_input || !p_input[0])
		return ;
	while(p_input[++i])
		ft_strdel(&p_input[i]);
}

int	get_input(void)
{
	int		rb;
	char	buf[4096];
	char	**parsed_input;
	//char	*temp;
	//int 	i = 0;

	rb = 1;
	ft_memset(buf, '\0', 4096);
	parsed_input = NULL;
	if (rb != 0)
	{
		rb = read(0, &buf, 4096);
		if (rb == -1)
			exit(1);
		if (check_quotes(buf))
			ft_putstr("invalid quoting, try again\n");
		else
		{
			parsed_input = parse_input(buf);
			rb = check_builtin(parsed_input, rb, buf);
		}
		// if (rb != 0 && !ft_isspace(buf[0]))
		//parsed_input = ft_strsplitws(temp)


		// while (parsed_input && parsed_input[i])
		// {
		// 	ft_putstr(parsed_input[i++]);
		// 	write(1, "\n", 1);
		// }
		ft_memset(buf, '\0', 4096);
		free_parsed_input(parsed_input);
		if (parsed_input)
			free(parsed_input);
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

	//(void)buf;
	// ft_putstr(input[0]);
	// write(1, "0", 1);
	if (rb == 0 || !ft_strcmp(input[0], "exit"))
	{
		ft_putstr("exit\n");
		return (EXIT_SUCCESS);
	}
	else if (!ft_strcmp(input[0], "echo"))
	{
		if (!input[i])
			write(1, "\n", 2);
		else
		{
			while (input[i])
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
	else
		ft_printf("mish-1.0: %s: command not found\n", input[0]);
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
	{
		free(env[i++]);
	}
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
	system("clear");
	//signal(SIGINT, sgn_handler(1));
	while (rb != 0)
	{
		ft_putstr("mish-1.0$ ");
		rb = get_input();
	}
	free_env(env);
	return (0);
}
