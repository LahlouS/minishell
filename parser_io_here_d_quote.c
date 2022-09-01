/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_here_d_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:34:47 by lchan             #+#    #+#             */
/*   Updated: 2022/07/22 18:51:10 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__get_dollar_cnt(char *arg, int dollar_cnt)
{
	if (dollar_cnt)
		dollar_cnt = 0;
	if (*arg != '$')
		dollar_cnt = 0;
	else if (!dollar_cnt)
		while (*(arg + dollar_cnt) == '$')
			dollar_cnt++;
	return (dollar_cnt);
}

static void	__quote_content_cpy(char **src, char **dst)
{
	int	quote;

	quote = **src;
	*src = *src + 1;
	while (quote && **src)
	{
		if (**src == quote)
		{
			quote = 0;
			*src = *src + 1;
		}
		else
		{
			**dst = **src;
			*src = *src + 1;
			*dst = *dst + 1;
		}
	}
}

static int	__is_odd_nbr(int nbr)
{
	if ((nbr == 1 || nbr == -1) || (nbr % 2 != 0))
		return (1);
	return (0);
}

char	*__here_d_unquote_limit(char *arg)
{
	int		dollar_cnt;
	char	*limit;
	char	*start_limit;

	dollar_cnt = 0;
	limit = ft_calloc(sizeof(char), ft_strlen(arg) + 1);
	start_limit = limit;
	while (limit && *arg)
	{
		while (*arg && !ft_strchr_b("\"\'$", *arg))
			*(limit++) = *(arg++);
		if (*arg == '$')
		{
			dollar_cnt = __get_dollar_cnt(arg, dollar_cnt);
			while (*arg && *arg == '$')
				*(limit++) = *(arg++);
			if (__is_odd_nbr(dollar_cnt) && ft_strchr_b("\"\'", *arg))
				limit--;
		}
		if (*arg && ft_strchr_b("\"\'", *arg))
			__quote_content_cpy(&arg, &limit);
	}
	*limit = '\0';
	return (start_limit);
}
