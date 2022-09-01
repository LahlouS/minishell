/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:38:33 by lchan             #+#    #+#             */
/*   Updated: 2021/12/14 21:44:39 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s2;
	const char	*start;
	const char	*end;
	size_t		i;

	if (!s1)
		return (0);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	start = &s1[i];
	while (s1[i] && s1[i + 1] != '\0')
		i++;
	while (s1[i] && ft_strchr(set, s1[i]))
		i--;
	if (!s1[i])
		end = &s1[i];
	else
		end = &s1[i + 1];
	s2 = (char *)malloc((ft_strlen(start) - ft_strlen(end) + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, start, ft_strlen(start) - ft_strlen(end) + 1);
	return (s2);
}
