/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:07:32 by lchan             #+#    #+#             */
/*   Updated: 2021/12/07 17:14:06 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_ptr;
	char	*src_ptr;

	if (!dst && !src)
		return (dst);
	dst_ptr = (char *)dst;
	src_ptr = (char *)src;
	if (src < dst)
	{
		while (len-- > 0)
			dst_ptr[len] = src_ptr[len];
	}
	else
	{
		while (len-- > 0)
		{
			*dst_ptr = *src_ptr;
			dst_ptr++;
			src_ptr++;
		}
	}
	return (dst);
}
