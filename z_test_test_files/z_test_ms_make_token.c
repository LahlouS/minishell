/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 17:46:51 by lchan             #+#    #+#             */
/*   Updated: 2022/06/24 19:31:26 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*********************** FROM LIBFT *****************************/

/*static int	ft_strlen(char *str)
{
	int	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
}*/
/*
static int ft_strlen(char *str)
{
	char *tmp;

	tmp = str;
	while (*str)
		str++;
	return (str - tmp);
}
*/

int	ft_strchr_b(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (1);
		i++;
	}
	return (0);
}
/****************************************************************/

static int	__str_word_jump(char **str, const char *delim)
{
	int		quote_flag;
	char	*tmp;

	quote_flag = 0;
	tmp = *str;
	while (ft_strchr_b(delim, *tmp))
		tmp++;
	while (*tmp && ft_strchr_b(delim, *tmp) == 0)
	{
		if (*tmp == '"')
			quote_flag = '"';
		else if (*tmp == '\'')
			quote_flag = '\'';
		while (quote_flag && tmp++)
		{
			if (*tmp == quote_flag)
				quote_flag = 0;
			else if (*tmp == '\0')
				return (-1);
		}
		tmp++;
	}
	*str = tmp;
	return (1);
}
/* ***********************************************************************
 * Definition : a word has at its R and L side either nothing or a delim
 * In order :
 * 		first while: tmp++ until it reaches a non delim
 * 		second while: tmp++ until it reaches a delim
 * 			third while:	tmp++ untel we reach a quote
 * 							send -1 if no quote
 * **********************************************************************/

static int	__set_null_bytes(char *str, const char *delim, char *str_end)
{
	int	cnt;

	cnt = 0;
	while (str != str_end)
	{
		if (__str_word_jump(&str, delim) == -1)
			return (-1);
		if (ft_strchr_b(delim, *str) && ++cnt)
			*str = '\0';
		else if (str == str_end && !ft_strchr_b(delim, *(str - 1)))
				cnt++;
		if (str != str_end)
			str++;
		else
			break ;
	}
	return (cnt);
}
/* ****************************************************************
 * put one null byte at the end of each words.
 * return the number of null byte that the str contains in the end
 * ****************************************************************/

static char	*__save_ptr(char *str, const char *delim, char *str_end)
{
	while (str != str_end && (*str == '\0' || ft_strchr_b(delim, *str)))
		str++;
	if (*str)
		return (str);
	else
		return (NULL);
}

char	**__make_token(char *str, const char *delim)
{
	char	*str_end;
	int		cnt;
	int		i;
	char	**token_tab;

	str_end = str + ft_strlen(str);
	cnt = __set_null_bytes(str, delim, str_end);
	if (cnt == -1)
		return (NULL);
	token_tab = (char **) malloc(sizeof(char *) * (cnt + 1));
	if (token_tab)
	{
		i = -1;
		while (++i < cnt)
		{
			str = __save_ptr(str, delim, str_end);
			token_tab[i] = str;
			__str_word_jump(&str, delim);
		}
		token_tab[i] = NULL;
	}
	return (token_tab);
}
/* ****************************************************************
 * cnt = -1 means that the entry is incorrect (single ' or ");
 * ****************************************************************/
