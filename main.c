/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/03 09:58:58 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void	sgn_handler(int num)
// {
// 	//(void)num;
// 	if (num == SIGINT)
// 	{
// 		ft_putstr("\nmish-1.0$ ");
// 		signal(SIGINT, sgn_handler);
// 	}
// }


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

void	free_parsed_input(char **p_input)
{
	int i;

	i = -1;
	if (!p_input || !p_input[0])
		return ;
	while (p_input[++i])
		ft_strdel(&p_input[i]);
}

int	minishell(char **env)
{
	int		rb;
	char	buf[4096];
	char	**parsed_input;

	rb = 1;
	ft_memset(buf, '\0', 4096);
	parsed_input = NULL;
	if (rb != 0)
	{
		//signal(SIGINT, sgn_handler);
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

void update_env(char **env, char *input, char *var)
{
	int		i;
	char	*temp;
	int		len;

	i = -1;
	len = ft_strlen(var);
	while(env[++i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
		{

			temp = ft_strndup(env[i], len + 1);
			env[i] = ft_strjoin(temp ,input);
			ft_strdel(&temp);
			return ;
		}
	}
	temp = ft_strjoin(var, "=");
	env[i++] = ft_strjoin(temp, input);
	env[i] = NULL;
}

int	check_builtin(char **input, int rb, char *buf, char **env)
{
	int k;
	int	ret;
	char **path;


	ret = 0;
	k = 0;
	path = get_path(env);

	if (!input[0] && rb)
		return (-1);
	(void)buf;
	update_env(env, input[0], "_");
	if (rb == 0 || !ft_strcmp(input[0], "exit"))
	{
		ft_putstr("exit\n");
		return (EXIT_SUCCESS);
	}
	else if (!ft_strcmp(input[0], "echo"))
		do_echo(input, env);
	else if (!ft_strcmp(input[0], "cd"))
		do_cd(input, env);
	else if (!ft_strcmp(input[0], "setenv"))
		do_setenv(input, env);
	else if (!ft_strcmp(input[0], "unsetenv"))
		do_unsetenv(input, env);
	else if (!ft_strcmp(input[0], "env"))
		do_env(input, env);
	else if (!check_command(input, path, env))
		;
	else
		ft_printf("mish-1.0: %s: command not found\n", input[0]);
	free_strarr(path);
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

void	free_strarr(char **strarr)
{
	int	i;

	i = 0;
	if(!strarr || !strarr[0])
		return ;
	while (strarr && strarr[i])
		free(strarr[i++]);
	free(strarr);
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
	system("clear");
	while (rb != 0)
	{
		ft_putstr("mish-1.0$ ");
		rb = minishell(env);
	}
	free_strarr(env);
	return (0);
}
