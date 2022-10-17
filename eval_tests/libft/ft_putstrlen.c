/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 21:45:14 by mviinika          #+#    #+#             */
/*   Updated: 2022/05/09 18:08:42 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

size_t	ft_putstrlen(char const *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = ft_strlen(s);
	write(1, s, len);
	return (len);
}
