/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/26 16:04:22 by mviinika         ###   ########.fr       */
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
// char *check_user(char *word)
// {
// 	DIR				*dir_s;
// 	struct dirent	*entity;
// 	struct stat		buf;
// 	char			user_home[200];

// 	ft_memset(user_home, '\0', 200);
// 	ft_strcat(user_home, "/Users/")
// 	dir_s = opendir(user_home);
// 	if (!dir_s)
// 	{
// 		exit(1);
// 	}
// 	entity = readdir(dir_s);
// 	while (entity)
// 	{
// 		if (ft_strncmp(entity->d_name, word, ft_strlen(word)) == 0)
// 		{
// 			//free(word);
// 			ft_strcat(user_home, entity->d_name);
// 			lstat(user_home, &buf);
// 			ft_printf("%s\n", word);
// 			break ;
// 		}
// 		entity = readdir(dir_s);
// 	}
// 	return (word);
// }

char	*replace_expansion(char *word, char **env, char *input)
{
	int		i;
	int		k;
	char 	*expanded;
	int		len;

	expanded = NULL;
	i = 0;
	k = -1;
	(void)input;
	len = 0;
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
				k++;
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
		i = 2;
		ft_printf("%s\n",&word[i]);
		while(word[i] && !ft_isspace(word[i]))
		{
			len++;
			i++;
		}
		while (env[++k])
		{
			if (ft_strncmp(env[k], &word[i], len) == 0)
			{
				expanded = ft_strdup(env[k] + len + 1);
				ft_printf("%s\n",expanded);
				// exit(1);
			//	expanded = ft_strjoin(expanded, &word[2]);
				break ;
			}
			// else
			// 	return (word);
		}
		expanded = ft_strnew(1);
	}
	//free(word);
	return (expanded);
}
char	*word(char *input, int i, int *total, char **env)
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
		if ((input[i] && closed == 0) || (!ft_isspace(input[i + 1]) && closed))
		{
			word[k++] = input[i++];
			*total += 1;
		}
		if ((input[i] == '~' && input[i + 1] == '$') || input[i] == '$')
		{
			i--;
			ft_strcat(word, replace_expansion(&input[i], env, &input[i]));
			total += ft_strlen(word);
			//ft_printf("word %s\n", word);
			return (word);
		}
	}
	// if (word[0] == '~' && !closed)
	// 	word = replace_expansion(word, env, &input[i]);
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

void free_parsed_input(char **p_input)
{
	int i;

	i = -1;
	if (!p_input || !p_input[0])
		return ;
	while (p_input[++i])
		ft_strdel(&p_input[i]);
}

int	get_input(char **env)
{
	int		rb;
	char	buf[4096];
	char	**parsed_input;

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
			parsed_input = parse_input(buf, env);
			rb = check_builtin(parsed_input, rb, buf, env);
		}
		ft_memset(buf, '\0', 4096);
		free_parsed_input(parsed_input);
		if (parsed_input)
			free(parsed_input);
	}
	return (rb);
}

int	check_builtin(char **input, int rb, char *buf, char **env)
{
	int k;
	int	ret;

	ret = 0;
	k = 0;
	if (ft_isspace(buf[0]))
		return (-1);
	if (rb == 0 || !ft_strcmp(input[0], "exit"))
	{
		ft_putstr("exit\n");
		return (EXIT_SUCCESS);
	}
	else if (!ft_strcmp(input[0], "echo"))
		do_echo(input, env);
	else if (!ft_strcmp(input[0], "cd"))
		ft_putstr("entering directory\n");
	else if (!ft_strcmp(input[0], "setenv"))
		ft_putstr("setting environment\n");
	else if (!ft_strcmp(input[0], "unsetenv"))
		ft_putstr("unsetting environment\n");
	else if (!ft_strcmp(input[0], "env"))
	{
		while(env[k])
			ft_putendl(env[k++]);
	}
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
	if(!env || !env[0])
		return ;
	while (env && env[i])
		free(env[i++]);
	free(env);
}

char	**get_env(char **dest, char **environ, int argc, char **argv)
{
	int		i;
	int		k;

	(void)argc;
	(void)argv;
	i = 0;
	k = -1;
	dest = (char **)malloc(sizeof(char *) * ft_linecount(environ) + 1);
	while (environ[++k])
	{
		if (ft_strncmp(environ[k], "OLDPWD=", 7) == 0)
			k++;
		dest[i++] = ft_strdup(environ[k]);
	}
	dest[i] = NULL;
	i = -1;
	while (dest[++i])
		if (ft_strncmp(dest[i], "SHLVL=", 6) == 0)
			dest[i][6] += 1;
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
	//ft_putstr("\033[2J");
	//signal(SIGINT, sgn_handler(1));
	while (rb != 0)
	{
		ft_putstr("mish-1.0$ ");
		rb = get_input(env);
	}
	free_env(env);
	return (0);
}
