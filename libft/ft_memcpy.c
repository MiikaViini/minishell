/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:47:37 by mviinika          #+#    #+#             */
/*   Updated: 2021/12/20 13:56:19 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*str = *(unsigned char *)src;
		str++;
		src++;
	}
	return (dest);
}
