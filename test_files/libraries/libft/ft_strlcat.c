/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:27:11 by lchan             #+#    #+#             */
/*   Updated: 2021/12/08 16:04:59 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	l_dst;
	size_t	l_src;

	if (!dst && !src)
		return (0);
	i = 0;
	l_dst = ft_strlen(dst);
	l_src = ft_strlen(src);
	if (dstsize - 1 < l_dst || dstsize == 0)
		return (l_src + dstsize);
	while (src[i] && (l_dst + i) < (dstsize - 1))
	{
		dst[l_dst + i] = src[i];
		i++;
	}
	dst[l_dst + i] = '\0';
	return (l_dst + l_src);
}
