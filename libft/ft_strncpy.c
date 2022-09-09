/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 08:46:45 by mviinika          #+#    #+#             */
/*   Updated: 2022/03/30 13:52:48 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (n == 0)
			return (dest);
		dest[i] = src[i];
		i++;
		n--;
	}
	while (n--)
		dest[i++] = '\0';
	return (dest);
}
