/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/30 15:07:34 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char **get_path(char **env)
{
	int		i;
	char 	**path;

	i = -1;
	path = NULL;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path = ft_strsplit(env[i] + 5, ':');
	return (path);
}

int execute_command(char **input, char *exec, char **env)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (execve(exec, &input[1], env) == -1)
			return (-1);
	}
	else
		wait(&pid);
	return (0);
}

int	check_command(char **input, char **path, char **env)
{
	DIR		*dir;
	struct 	dirent *entity;
	int		i;
	int 	k;
	char	*exec;
	char	*path_;
	
	i = 0;
	k = 0;
	while (path[i])
	{
		dir = opendir(path[i]);
		if (dir == NULL)
		{
			ft_putstr("Error");
			return(1);
		}
		entity = readdir(dir);
		while (entity != NULL)
		{
			ft_printf("%s\n", input[1]);
			if (ft_strcmp(input[1], entity->d_name) == 0)
			{
				exec = ft_strjoin("/", input[1]);
				path_ = ft_strjoin(path[i], exec);
				execute_command(input, path_, env);
				return (0);
			}
			entity = readdir(dir);
		}
		i++;
	}
	return (1);
}

int do_env(char **input, char **env)
{
	int		i;
	int		k;
	char	**path;
	
	i = 0;
	k = 0;
	path = NULL;
	if (!input[i])
		while(env[k])
			ft_putendl(env[k++]);
	else
	{
		while (check_validity(&input[i]) == 0)
			i++;
		path = get_path(env);
		if (!check_command(&input[i], path, env))
			return (0);
		// while (path && path[i])
		// 	ft_printf("[%s]\n", path[i++]);
	}
	free_strarr(path);
	return (0);
}
