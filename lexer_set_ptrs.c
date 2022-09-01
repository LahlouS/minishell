/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_ptrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 17:32:57 by lchan             #+#    #+#             */
/*   Updated: 2022/07/22 19:53:18 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/***************************************************************************
 * skip all spaces and return the position of the first non space character
 */
static char	*set_ptrs_start(char *str, char *str_end)
{
	while (str != str_end && ft_strchr_b(" ", *str))
		str++;
	return (str);
}

/************************
 * find end case operator
 * 		skip bits while is an operator under some condition
 * 			the next meta has to be the same as the first one
 * 			the skiping can not excess 2
 */
static char	*find_end_operator(char *start, char *str_end)
{
	char	*end;
	char	*first_meta;

	end = start;
	first_meta = start;
	while (end != str_end && ft_strchr_b(METACHAR, *end))
		if (*++end != *first_meta
			|| (end - first_meta >= 2)
			|| (*end == '|'))
			break ;
	return (end);
}

/***************************************************************************
 * find end case word
 * 		skip bits until a metacharacter ("|&()<> ") is encountered
 * if a quote is encountered, skip bits until end of quote is encountered
 * 		end of quote do not necessarly imply end of token
 * 		returns NULL if no end of quote is encountered
 */
static char	*find_end_word(char *end, char *str_end)
{
	int		quote_flag;

	quote_flag = 0;
	while (end != str_end
		&& ft_strchr_b(METACHAR, *end) == 0 && ft_strchr_b(" ", *end) == 0)
	{
		if (*end == '"')
			quote_flag = '"';
		else if (*end == '\'')
			quote_flag = '\'';
		while (quote_flag && end++)
		{
			if (*end == quote_flag)
				quote_flag = 0;
			else if (*end == '\0')
				return (NULL);
		}
		end++;
	}
	return (end);
}

/***************************************************************************
 * return the end of token according to the start address
 */
static char	*set_ptrs_end(char *start, char *str_end)
{
	char	*end;

	if (ft_strchr_b(METACHAR, *start))
		end = find_end_operator(start, str_end);
	else
		end = find_end_word(start, str_end);
	return (end);
}

/**
 * @brief set the start and the end value of a token.
 *
 * @param start start of the token
 * @param end end of the token. if NULL, means unterminated quote has been found
 * @return int returns none NULL value in case a of unterminated quote
 */
int	lexer_set_ptrs(char **start, char **end)
{
	char	*str_end;

	str_end = *start + ft_strlen(*start);
	*start = set_ptrs_start(*start, str_end);
	*end = set_ptrs_end(*start, str_end);
	if (!*end || *end == *start)
		return (ERR_SET_PTR);
	return (0);
}
