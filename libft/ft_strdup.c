/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:43:28 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/12 14:03:40 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!str)
		exit(1);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
