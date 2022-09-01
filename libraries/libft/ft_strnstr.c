/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:00:51 by lchan             #+#    #+#             */
/*   Updated: 2021/12/06 16:06:44 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*tmp_ptr;
	char	*tmp_needle;
	size_t	tmp_len;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len > ft_strlen(haystack))
		len = ft_strlen(haystack);
	while (len-- > 0)
	{
		if (*haystack == *needle)
		{
			if (*haystack == *needle && ft_strlen(needle) == 1)
				return ((char *)haystack);
			tmp_ptr = (char *)haystack;
			tmp_needle = (char *)needle;
			tmp_len = len;
			while (*(++tmp_ptr) == *(++tmp_needle) && tmp_len--)
				if (*(tmp_needle + 1) == '\0')
					return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
