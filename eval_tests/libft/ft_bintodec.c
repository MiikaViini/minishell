/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintodec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:43:09 by mviinika          #+#    #+#             */
/*   Updated: 2022/03/01 09:52:32 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bintodec(signed long long bin)
{
	int	result;
	int	bit;
	int	i;

	i = 0;
	result = 0;
	bit = 0;
	while (bin)
	{
		bit = bin % 10;
		bin /= 10;
		result += ft_pow(2, i) * bit;
		i++;
	}
	return (result);
}
