/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 20:41:14 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 23:33:14 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static int execute_command(char **input, char *exec, char **env)
{
	int	pid;
	struct stat stat_;

	if (stat(exec, &stat_) != -1 && !S_ISREG(stat_.st_mode))
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (execve(exec, input, env) == -1)
		{
			error_print(exec, NULL, E_EXE);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&pid);
	return (0);
}

static int	execute_path_bin(char **input, char **path, char **env)
{
	char	*exec;
	char	*path_;
	DIR		*dir;
	struct 	dirent *entity;
	int		i;

	i = -1;
	while (input[0] && path && path[++i])
	{
		dir = opendir(path[i]);
		if (dir == NULL)
			return (1);
		entity = readdir(dir);
		while (entity != NULL)
		{
			if (ft_strcmp(input[0], entity->d_name) == 0)
			{
				exec = ft_strjoin("/", input[0]);
				path_ = ft_strjoin(path[i], exec);
				execute_command(input, path_, env);
				ft_strdel(&exec);
				ft_strdel(&path_);
				closedir(dir);
				return 0;
			}
			entity = readdir(dir);
		}
		closedir(dir);
	}
	error_print(input[0], NULL, E_NOTF);
	return 0;
}

static int	tried_to_execute(char **input, char **path, char **env)
{
	struct stat buf;

	if (ft_strchr(input[0], '/') && access(input[0], F_OK) == 0)
	{
		if (stat(input[0], &buf) == 0 && S_ISDIR(buf.st_mode))
		{
			error_print(input[0], NULL, E_ISDIR);
			return (1);
		}
		else if (!execute_command(input, input[0], env))
			return (1);
	}
	else if (!execute_path_bin(input, path, env))
		return 1;
	return (0);
}

int	check_command(char **input, char **path, char **env)
{
	//DIR		*dir;
	//struct 	dirent *entity;
	//int		i;
//	int		k;

	//i = -1;
	//k = 0;
	// while (input[0] && path && path[++i])
	// {
	// 	dir = opendir(path[i]);
	// 	if (dir == NULL)
	// 		return (1);
	// 	entity = readdir(dir);
	// 	while (entity != NULL)
	// 	{
	if (tried_to_execute(input, path, env))
		return 0;
			
		// 	entity = readdir(dir);
		// }
		//closedir(dir);
	
	return (1);
}