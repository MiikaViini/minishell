/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/12 18:18:56 by mviinika         ###   ########.fr       */
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
char **parse_input(char *input)
{
	int i;
	int	s_quote;
	int d_quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '"')
			s_quote += 1;
		else if (input[0] == "\"")
			d_quote += 1;
	}
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
		if (rb != 0 && !ft_isspace(buf[0]))
			parsed_input = ft_strsplitws(buf);
		rb = check_builtin(parsed_input, rb, buf);

		ft_memset(buf, '\0', 4096);
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
