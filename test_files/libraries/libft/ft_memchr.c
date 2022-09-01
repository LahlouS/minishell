/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 22:36:24 by lchan             #+#    #+#             */
/*   Updated: 2022/04/12 14:00:31 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*chr;

	chr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (chr[i] == (unsigned char)c)
			return (&chr[i]);
		i++;
	}
	return (NULL);
}
