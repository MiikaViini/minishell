/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 13:37:55 by mviinika          #+#    #+#             */
/*   Updated: 2022/08/17 18:25:52 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(long long n)
{
	unsigned char	len;

	len = 1;
	if (n < 0)
	{
		n = ~n;
		n++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
