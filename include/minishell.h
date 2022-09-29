/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/29 09:11:37 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <pwd.h>

// typedef struct s_env
// {
// 	char	**env;
// }			t_env;

int	check_builtin(char **input, int rb, char *buf, char **env);
int	do_echo(char **input, char **env);
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


int	do_unsetenv(char **input, char **env);
int	do_setenv(char **input, char **env);
#endif
