/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 15:01:56 by mviinika         ###   ########.fr       */
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

int check_validity_env(char **input)
{
	int	i;
	int equ_sign;

	equ_sign = 0;
	i = 0;
	while (input[++i])
	{
		equ_sign = check_equalsign(input[i]);
		if (equ_sign)
			return (1);
	}
	return (0);
}

int	execute_path_bin(char **input, char *path, char **env)
{
	char	*exec;
	char	*path_;
	exec = ft_strjoin("/", *input);
	path_ = ft_strjoin(path, exec);
	if (execute_command(input, path_, env))
		return (1);
	ft_strdel(&exec);
	ft_strdel(&path_);
	return 0;
}

int	tried_to_execute(char **input, char *f_name, char **path, char **env)
{
	if (ft_strcmp(input[0], f_name) == 0
		&& !execute_path_bin(input, *path, env))
		return 1;
	else if (access(input[0], F_OK) == 0 && !execute_command(input, input[0], env))
		return 1;
	return (0);
}

int	check_command(char **input, char **path, char **env)
{
	DIR		*dir;
	struct 	dirent *entity;
	int		i;
	int		k;

	i = -1;
	k = 0;
	while (input[0] && path && path[++i])
	{
		dir = opendir(path[i]);
		if (dir == NULL)
			return (1);
		entity = readdir(dir);
		while (entity != NULL)
		{
			if (tried_to_execute(input, entity->d_name, &path[i], env))
			{
				closedir(dir);
				return 0;
			}
			entity = readdir(dir);
		}
		closedir(dir);
	}
	return (1);
}

static void exec_w_env(char **input, t_env *env, int i, int k)
{
	t_env	temp;
	char	*exec;
	
	exec = NULL;
	temp.env = ft_strarrndup(temp.env, env->env, ft_linecount(input));
	update_env(temp.env, input[0], "_");
	if (input[i])
	{
		exec = input[i];
		input[i] = NULL;
		do_setenv(input, &temp);
		input[i] = exec;
		if (!check_command(&input[i], env->path, temp.env))
			;
		else
			error_print(input[i], "env", E_NOEX);
	}
	else
	{
		do_setenv(input, &temp);
		while(temp.env[++k])
			ft_putendl(temp.env[k]);
	}
	free_strarr(temp.env);
}

int do_env(char **input, t_env *env)
{
	int		i;
	int		k;

	i = 0;
	k = -1;
	if (!input[1])
		while(env->env[++k])
			ft_putendl(env->env[k]);
	else
	{
		while(input[++i])
			if (check_equalsign(input[i]))
				break ;
		k = -1;
		exec_w_env(input, env, i, k);
	}
	update_env(env->env, input[ft_linecount(input) - 1], "_");
	return (0);
}

// while (env[k])
// {
// 	if (ft_strncmp(env[k], "OLDPWD=", 7) == 0)
// 	{
// 		ft_strdel(&env[k]);
// 		env[k] = env[k + 1];
// 		while(env[k])
// 		{
// 			env[k] = env[k + 1];
// 			k++;
// 		}
// 	}
// 	k++;
// }