/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:11:28 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 14:56:58 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strjoin(char const *s1, char const *s2) //old ft_strjoin
{
	char	*joined;
	size_t	index;

	index = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (s1 && *s1 != '\0')
	{
		joined[index] = *s1;
		s1++;
		index++;
	}
	while (s2 && *s2 != '\0')
	{
		joined[index] = *s2;
		s2++;
		index++;
	}
	joined[index] = '\0';
	return (joined);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = s2[--len_s2];
		while (len_s1)
		*(--joined) = s1[--len_s1];
	}
	return (joined);
}

/**
 * @brief	modified strjoin. Uses ft_strlen_p.
 * will segfault gets NULL in parameters
 *
 * @param s1
 * @param s2
 * @return pointer toward malloc of joined s1  and s2.
 * difference If !s1 || !s2 act as ft_strdup.
 * Also if !s1 && !s2, returns "\0"
 */
char	*ft_strjoin_free(char **s1, char **s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen_p(*s1);
	len_s2 = ft_strlen_p(*s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = (*s2)[--len_s2];
		while (len_s1)
		*(--joined) = (*s1)[--len_s1];
		ft_free_char(s1);
		ft_free_char(s2);
	}
	return (joined);
}

char	*ft_strjoin_free_s1(char **s1, char **s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen_p(*s1);
	len_s2 = ft_strlen_p(*s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = (*s2)[--len_s2];
		while (len_s1)
		*(--joined) = (*s1)[--len_s1];
		ft_free_char(s1);
	}
	return (joined);
}

char	*ft_strjoin_free_s2(char **s1, char **s2)
{
	int		len_s1;
	int		len_s2;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen_p(*s1);
	len_s2 = ft_strlen_p(*s2);
	joined = (char *)malloc((len_s1 + len_s2 + 1) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2;
		*joined = '\0';
		while (len_s2)
		*(--joined) = (*s2)[--len_s2];
		while (len_s1)
		*(--joined) = (*s1)[--len_s1];
		ft_free_char(s2);
	}
	return (joined);
}

/**
 * @brief strjoin but with a separator.
 * Segfault if NULL parameter. OK if *s = NULL
 *
 * @param s1
 * @param s2
 * @param sep
 * @return char*
 */
char	*ft_strjoin_free_sep(char **s1, char **s2, char sep)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*joined;

	i = 1;
	if (*s1 && *s2)
		i = 2;
	len_s1 = ft_strlen_p(*s1);
	len_s2 = ft_strlen_p(*s2);
	joined = (char *)malloc((len_s1 + len_s2 + i) * sizeof (char));
	if (joined)
	{
		joined += len_s1 + len_s2 + i - 1;
		*joined = '\0';
		while (len_s2)
		*(--joined) = (*s2)[--len_s2];
		if (i == 2)
			*(--joined) = sep;
		while (len_s1)
		*(--joined) = (*s1)[--len_s1];
		ft_free_char(s1);
		ft_free_char(s2);
	}
	return (joined);
}

/* //test main
int main()
{
	char	*test = "test1";
	char	*test2 = "test2";
	char	*m_test = ft_strdup(test);
	char	*m_test2 = ft_strdup(test2);
	char	*m_test3 = ft_strdup("test3");
	char	*m_test4 = ft_strdup("test4");
	char	*joined_free;
	char	*joined_free_sep;
	char	*joined_free_s1;
	char	*joined_free_s2;

	joined_free = ft_strjoin_free(&m_test ,&m_test);
	joined_free_sep = ft_strjoin_free_sep(&m_test2, &m_test2, ' ');
	joined_free_s1 = ft_strjoin_free_s1(&m_test3, &test);
	joined_free_s2 = ft_strjoin_free_s2(&test, &m_test4);
	printf("joined_free	= \"%s\"\n", joined_free);
	printf("joined_free_sep	= \"%s\"\n", joined_free_sep);
	printf("joined_free_s1	= \"%s\"\n", joined_free_s1);
	printf("joined_free_s2	= \"%s\"\n", joined_free_s2);

	ft_free_stdarg(4, joined_free, joined_free_sep, joined_free_s1, joined_free_s2);
}*/
