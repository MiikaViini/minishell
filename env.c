/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/30 23:55:08 by mviinika         ###   ########.fr       */
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
		if (execve(exec, input, env) == -1)
			return (-1);
	}
	else
		wait(&pid);
	return (0);
}

int check_validity_env(char **input)
{
	int	i;
	int	k;
	int equ_sign;

	equ_sign = 0;
	i = 0;
	k = -1;
	while (input[++i])
	{
		equ_sign = check_equalsign(input[i]);
		if (equ_sign)
		{
			//ft_putstr_fd("minishell: setenv: please enter arguments in format 'name=value'.\n", 2);
			return (1);
		}
	}
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
			if (ft_strcmp(input[k], entity->d_name) == 0)
			{
				exec = ft_strjoin("/", input[k]);
				path_ = ft_strjoin(path[i], exec);
				execute_command(input, path_, env);
				ft_strdel(&exec);
				ft_strdel(&path_);
				return (0);
			}
			else if (access(input[k], F_OK) == 0)
			{
				execute_command(input, input[k], env);
				return (0);
			}
			entity = readdir(dir);
		}
		i++;
	}
	ft_printf("env: %s: command not found\n", input[k]);
	return (1);
}

int do_env(char **input, char **env)
{
	int		i;
	int		k;
	char	**path;

	i = 1;
	k = 0;
	path = NULL;
	if (!input[i])
		while(env[k])
			ft_putendl(env[k++]);
	else
	{
		while (check_equalsign(input[i]) == 0)
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
