/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 19:22:14 by lchan             #+#    #+#             */
/*   Updated: 2022/07/08 14:19:53 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
*/

size_t	ft_strlen(const char *s)
{
	char	*start;

	start = (char *)s;
	while (*s)
		s++;
	return (s - start);
}

/**
 * @brief compared to the original one, his strlen is protected
 *
 * @param s
 * @return size_t 0 if s = NULL, else returns len os s;
 */
size_t	ft_strlen_p(const char *s)
{
	char	*start;

	if (s)
	{
		start = (char *)s;
		while (*s)
			s++;
		return (s - start);
	}
	return (0);
}
