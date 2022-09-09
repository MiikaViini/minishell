/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:47:26 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/09 18:04:24 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*fresh;
	int		i;

	i = 0;
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	fresh = ft_strnew(len);
	if (fresh == NULL)
		return (NULL);
	while (s1 && *s1 != '\0')
		fresh[i++] = *s1++;
	while (s2 && *s2 != '\0')
		fresh[i++] = *s2++;
	fresh[i] = '\0';
	return (fresh);
}
