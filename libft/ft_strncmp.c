/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:57:00 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/05 21:50:47 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n <= 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2  && n - 1)
	{
		n--;
		s1++;
		s2++;
	}

	return ((unsigned char)*s1 - (unsigned char)*s2);
}
