/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:16:17 by mviinika          #+#    #+#             */
/*   Updated: 2021/12/20 14:00:44 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh;
	size_t			size;
	unsigned int	i;

	i = 0;
	size = ft_strlen((char *)s);
	fresh = (char *)malloc(sizeof(char) * (size + 1));
	if (fresh == NULL)
		return (NULL);
	while (s[i])
	{
		fresh[i] = f(i, (char)s[i]);
		i++;
	}
	fresh[i] = '\0';
	return (fresh);
}
