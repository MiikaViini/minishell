/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/03 15:18:13 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
 #include <sys/stat.h>
# include <signal.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <pwd.h>
# include <unistd.h>

# define MAX_VAR 1024
# define MAX_PATH 1024

typedef struct s_env
{
	char	**env;
	char	**path;
}			t_env;

int	check_builtin(char **input, int rb, char *buf, t_env *env);
int	do_echo(char **input, t_env *env);
char **strarrdup(char **strarr);
size_t	ft_linecount(char **arr);
/*
**QUOTES
*/
int	is_single_quote(char c);
int	is_double_quote(char c);
int	is_quote(char c);
int	check_quotes(char *input);
int	is_expansion(char *str);

/*
**EXPANSIONS
*/
char	*replace_expansion(char *word, char **env, char *input);

/*
**PARSING
*/
char	**parse_input(char *input, char **env);
int	do_unsetenv(char **input, t_env *env);
int	do_setenv(char **input, t_env *env);
int do_env(char **input, t_env *env);
int do_cd(char **input, t_env *env);

void	free_strarr(char **strarr);
int check_validity(char **input);
int check_equalsign(char *input);
char **get_path(char **env);
int	check_command(char **input, char **path, char **env);
void update_env(char **env, char *input, char *var);
#endif
