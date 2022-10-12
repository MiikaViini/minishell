/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:45:58 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/12 10:46:25 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*user_expansion(char *input)
{
	DIR		*dir;
	struct 	dirent *entity;
	char	*path;

	dir = opendir("/Users");
	path = NULL;
	if (dir == NULL)
		return (NULL);
	entity = readdir(dir);
	while(entity != NULL)
	{
		if (ft_strcmp(&input[1], entity->d_name) == 0)
		{
			path = ft_strjoin("/Users/", &input[1]);
			ft_strdel(&input);
			input = ft_strdup(path);
			ft_strdel(&path);
			break ;
		}
		entity = readdir(dir);
	}
	closedir(dir);
	return (input);
}