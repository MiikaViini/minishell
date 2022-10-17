/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:57:37 by mviinika          #+#    #+#             */
/*   Updated: 2021/12/20 13:55:51 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	t;

	t = (unsigned char)c;
	d = (unsigned char *)s;
	while (n--)
	{
		if (t == *d)
			return (d);
		d++;
	}
	return (NULL);
}
