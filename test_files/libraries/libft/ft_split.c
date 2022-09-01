/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 21:30:00 by lchan             #+#    #+#             */
/*   Updated: 2021/12/09 17:55:30 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] != c)
			&& (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_w_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	**ft_i_am_free(char **split, size_t index)
{
	size_t	i;

	i = 0;
	while (i <= index)
	{		
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**ft_split_half(char const *s, char c, int i, int j)
{
	char	**split;

	split = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			split[j] = (char *)malloc((ft_w_len(&s[i], c) + 1) * sizeof(char));
			if (!split[j])
				return (ft_i_am_free(split, j));
			ft_strlcpy(split[j], &s[i], ft_w_len(&s[i], c) + 1);
			j++;
		}
		i += ft_w_len(&s[i], c);
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	split = ft_split_half(s, c, i, j);
	return (split);
}
/* My function with 26 line. 
char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**split;

	i = 0;
	j = 0;
	if (s)
		split = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			split[j] = (char *)malloc((ft_w_len(&s[i], c) + 1) * sizeof(char));
			if (!split[j])
				return (ft_i_am_free(split, j));
			ft_strlcpy(split[j], &s[i], ft_w_len(&s[i], c) + 1);
			j++;
		}
		i += ft_w_len(&s[i], c);
	}
	split[j] = NULL;
	return (split);
}*/
