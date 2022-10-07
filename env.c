/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:50:13 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/07 14:58:51 by mviinika         ###   ########.fr       */
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
	{
		return (-1);
	}
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (execve(exec, input, env) == -1)
		{
			error_print(exec, E_EXE);
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
	int		len;
	int		k;

	i = 0;
	ret = 1;
	len = 0;
	k = 0;
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
				while (env[k])
				{
					if (ft_strncmp(env[k], "OLDPWD=", 7) == 0)
					{
						ft_strdel(&env[k]);
						env[k] = env[k + 1];
						while(env[k])
						{
							env[k] = env[k + 1];
							k++;
						}
					}
					k++;
				}
				if (execute_command(input, path_, env))
					return (1);
				ft_strdel(&exec);
				ft_strdel(&path_);
				closedir(dir);
				return 0;
			}
			else if (access(input[0], F_OK) == 0)
			{
				execute_command(input, input[0], env);
				closedir(dir);
				return 0;
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
	if (!strarr)
		return (NULL);
	while(strarr[++i])
		len++;
	fresh = (char **)malloc(sizeof(char *) * (len + 1));
	if (!fresh)
		return (NULL);
	i = -1;
	while (strarr[++i])
		fresh[i] = ft_strdup(strarr[i]);
	fresh[i] = NULL;
	return (fresh);
}

char **strarrcpy(char **dest, char **strarr)
{
	int	i;

	i = -1;
	if (!strarr)
		return (NULL);
	while(strarr[++i])
		dest[i] = strarr[i];
	return (dest);
}

// char **strarrcat(char **dest, char **strarr)
// {
// 	int	i;

// 	i = -1;
// 	if (!strarr)
// 		return (NULL);
// 	while(strarr[++i])
// 		dest[i] = strarr[i];
// 	return (dest);
// }

int do_env(char **input, t_env *env)
{
	int		i;
	int		k;
	int		arr_len;
	int		var_len;
	int		added;
	char	*exec;

	i = 1;
	k = -1;
	added = 0;
	arr_len = 0;
	var_len = 0;
	exec = NULL;
	update_env(env->env, input[0], "_");
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
				;// ft_printf("minishell: env: %s: no such file or folder\n", input[i]);
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
	}
	do_unsetenv(input, env);
	update_env(env->env, input[ft_linecount(input) - 1], "_");
	return (0);
}
