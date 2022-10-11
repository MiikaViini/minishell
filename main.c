/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:07:23 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 23:27:52 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	free_parsed_input(char **p_input)
{
	int i;

	i = -1;
	if (!p_input || !p_input[0])
		return ;
	while (p_input[++i])
		ft_strdel(&p_input[i]);
}

static int	minishell(t_env *env, char **builtins)
{
	int		rb;
	char	buf[MAX_LINE + 1];
	char	**parsed_input;

	rb = 1;
	ft_memset(buf, '\0', MAX_LINE + 1);
	parsed_input = NULL;
	if (rb != 0)
	{
		rb = read(0, &buf, MAX_LINE);
		if (rb == -1)
			exit(1);
		if (check_quotes(buf))
			error_print(NULL, NULL, E_QUOT);
		else
		{
			if(rb != 0)
				parsed_input = parse_input(buf, env->env);
			rb = check_exec(parsed_input, rb, builtins, env);
		}
		ft_memset(buf, '\0', 4096);
		free_parsed_input(parsed_input);
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
	if (!var)
		return ;
	while(env[++i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
		{
			temp = ft_strndup(env[i], len + 1);
			ft_strdel(&env[i]);
			env[i] = ft_strjoin(temp, input);
			ft_strdel(&temp);
			return ;
		}
	}
	temp = ft_strjoin(var, "=");
	env[i] = ft_strjoin(temp, input);
	ft_strdel(&temp);
}

void set_shell_lvl(t_env *env)
{
	int		num;
	char	*temp;
	int		i;
	
	i = -1;
	temp = NULL;
	while (env->env[++i])
	{
		if (ft_strncmp(env->env[i], "SHLVL=", 6) == 0)
		{
			num = ft_atoi(env->env[i] + 6);
			num++;
			if (num >= 1000)
				num = 0;
			temp = ft_itoa(num);
			ft_strdel(&env->env[i]);
			env->env[i] = ft_strjoin("SHLVL=", temp);
			ft_strdel(&temp);
			return ;
		}
	}
	update_env(env->env, "1", "SHLVL");
}

static void	get_env(t_env *dest, char **environ, int argc, char **argv)
{
	int		i;
	int		k;
	int		size;
	
	(void)argc;
	(void)argv;
	size = 3 + ft_linecount(environ);
	i = 0;
	k = -1;
	dest->env = (char **)ft_memalloc(sizeof(char *) * (size));
	if (!dest->env)
		return ;
	while (environ[++k])
	{
		if (ft_strncmp(environ[k], "OLDPWD=", 7) == 0)
			k++;
		dest->env[i++] = ft_strdup(environ[k]);
	}
	dest->env[i] = NULL;
	set_shell_lvl(dest);
}

static char **initialize_and_set_builtins(void)
{
	static char *builtins[6] = { "echo", "cd", "setenv", "unsetenv", "env"};
	return (builtins);
}

int	main(int argc, char **argv, char **environ)
{
	t_env	*env;
	char	**builtins;
	int		rb;

	rb = 1;
	builtins = initialize_and_set_builtins();
	env = (t_env *)malloc(sizeof(t_env));
	get_env(env, environ, argc, argv);
	while (rb != 0)
	{
		ft_putstr("mish-1.0$ ");
		rb = minishell(env, builtins);
	}
	free_strarr(env->env);
	free_strarr(env->path);
	free(env);
	return (0);
}
