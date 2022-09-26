/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/09/26 11:15:52 by mviinika         ###   ########.fr       */
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
#endif
