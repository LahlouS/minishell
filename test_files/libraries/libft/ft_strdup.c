/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:49:05 by lchan             #+#    #+#             */
/*   Updated: 2022/05/21 23:39:52 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dup;

	if (s1)
		len = ft_strlen(s1);
	else
		len = 0;
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (s1 && *s1 != '\0')
	{
		*dup = *s1;
		s1++;
		dup++;
	}
	*dup = '\0';
	return (dup - len);
}
