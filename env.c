/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/03 22:05:37 by mviinika         ###   ########.fr       */
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
	int	ret;

	ret = stat(exec, &stat_);
	if (!S_ISREG(stat_.st_mode))
	{
		ft_printf("minishell: %s: isnt executable\n", exec);
		return (-1);
	}
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
	char	*exec;
	char	*path_;
	int		ret;

	i = 0;
	ret = 1;
	while (input[0] && path && path[i])
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
				ret = 0;
				break ;
			}
			else if (access(input[0], F_OK) == 0)
			{
				execute_command(input, input[0], env);
				ret = 0;
				break ;
			}
			entity = readdir(dir);
		}
		closedir(dir);
		i++;
	}
	return (ret);
}

char **strarrdup(char **strarr)
{
	int	i;
	int	len;
	char **fresh;

	i = -1;
	len = 0;
	while(strarr[++i])
		len++;
	fresh = (char **)malloc(sizeof(char *) * len + 1);
	if (!fresh)
		return (NULL);
	i = -1;
	while (strarr[++i])
		fresh[i] = ft_strdup(strarr[i]);
	fresh[i] = NULL;
	return (fresh);

}

int do_env(char **input, t_env *env)
{
	int		i;
	int		k;
	int		arr_len;
	int		var_len;
	int		added;
	char	**new_env;
	char	*exec;

	i = 1;
	k = -1;
	added = 0;
	arr_len = 0;
	var_len = 0;
	new_env = strarrdup(env->env);
	exec = NULL;
	if (!input[i])
		while(env->env[++k])
			ft_putendl(env->env[k]);
	else
	{
		while(input[i])
		{
			if (check_equalsign(input[i]))
				break ;
			i++;
		}
		if (input[i])
		{
			exec = input[i];
			input[i] = NULL;
			do_setenv(input, env);
			input[i] = exec;
			if (!check_command(&input[i], env->path, env->env))
				;
			else
				ft_printf("minishell: env: %s: command not found\n", input[i]);
		}
		else
		{
			do_setenv(input, env);
			k = -1;
			while(env->env[++k])
				ft_putendl(env->env[k]);
		}
		env->env = strarrdup(new_env);
	}
	free_strarr(new_env);
	return (0);
}
