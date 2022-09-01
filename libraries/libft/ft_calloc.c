/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:42:38 by lchan             #+#    #+#             */
/*   Updated: 2021/11/27 19:00:11 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	calloc_size;
	void	*calloc_ptr;

	calloc_size = count * size;
	calloc_ptr = (void *)malloc(calloc_size);
	if (calloc_ptr == NULL)
		return (0);
	while ((calloc_size--) > 0)
		*((char *)calloc_ptr + calloc_size) = 0;
	return (calloc_ptr);
}
