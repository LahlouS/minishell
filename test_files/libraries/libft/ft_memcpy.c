/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 12:07:50 by lchan             #+#    #+#             */
/*   Updated: 2021/12/07 17:12:01 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;

	if (!src && !dest)
		return (dest);
	dest_ptr = (char *) dest;
	src_ptr = (char *) src;
	while (n > 0)
	{
		*(dest_ptr++) = *(src_ptr++);
		n--;
	}
	return (dest);
}
