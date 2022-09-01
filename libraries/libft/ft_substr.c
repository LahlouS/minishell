/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 15:10:33 by lchan             #+#    #+#             */
/*   Updated: 2021/12/11 00:59:10 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	len_daddy;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_daddy = 0;
	len_s = ft_strlen(s);
	if ((len > len_s) && start < len_s)
		len_daddy = ft_strlen(&s[start]);
	else if (start < len_s)
		len_daddy = len;
	new_s = (char *)malloc((len_daddy + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, &s[start], len_daddy + 1);
	new_s[len_daddy] = '\0';
	return (new_s);
}
