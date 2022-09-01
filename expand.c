/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:12:12 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/04 15:53:01 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__remove_quote(char *str)
{
	char	quote_flag;
	int		i;
	char	*start;

	if (!str)
		return (NULL);
	quote_flag = 0;
	i = 0;
	start = str;
	while (*(str + i))
	{
		while (*(str + i) && (quote_flag == 0 || quote_flag == *(str + i))
			&& ft_strchr_b("\'\"", *(str + i)))
		{
			quote_flag ^= ((*(str + i) == '\'') * '\'') + \
			((*(str + i) == '\"') * '\"');
			i++;
		}
		*str = *(str + i);
		if (*(str + i))
			str++;
	}
	*str = '\0';
	return (start);
}

char	*__expand_string_bis(
	char **str, char **start, char **env, int opt_quote)
{
	char	*expand;
	char	*end;
	int		tmp_start;

	tmp_start = *start - *str;
	end = ++(*start);
	if (!ft_isdigit(*end))
		while (*end && (ft_isalnum(*end) || *end == '_' || *end == '?'))
			end++;
	else
		end++;
	expand = __get_expand(*start, end - *start, env);
	*str = __add_exp_to_str(*str, start, end, expand);
	if (opt_quote == 0)
		__add_exp_split_str(*str, tmp_start, ft_strlen_p(expand));
	return (*str);
}

char	*__expand_string(char *str, char **env, int opt)
{
	char	quote_flag;
	char	*start;

	quote_flag = 0;
	start = str;
	while (start)
	{
		if (opt == 1)
			start = __is_hd_expandable(start);
		else
			start = __is_expandable(start, &quote_flag);
		if (start)
			str = __expand_string_bis(&str, &start, env, opt + quote_flag);
		else if (!start)
			quote_flag = 0;
	}
	return (str);
}

void	__expand_t_list(t_list *lst, char **env, int opt)
{
	char	buf[1];

	if (lst)
	{
		if (opt == 1 \
			&& !ft_strncmp((char *)lst->content, HD_EXP, ft_strlen_p(HD_EXP)))
			lst = lst->next;
		else if (opt == 1)
			return ;
		while (lst && lst->content)
		{
			if (opt == 2)
				buf[0] = ((char *)lst->content) \
				[ft_strlen(((char *)lst->content)) + 1];
			lst->content = __expand_string((char *)lst->content, env, opt);
			if (opt != 1)
				lst->content = __remove_quote((char *)lst->content);
			if (opt == 2)
				((char *)lst->content) \
				[ft_strlen(((char *)lst->content)) + 1] = buf[0];
			lst = lst->next;
		}
	}
}

t_splcmd	*__expand(t_splcmd *parser, char **env)
{
	t_splcmd	*parser_start;

	parser_start = parser;
	while (parser)
	{
		__expand_t_list(parser->in.stock, env, 2);
		__expand_t_list(parser->in.here_buffer, env, 1);
		__expand_t_list(parser->cmd.cmd_lst, env, 0);
		parser->cmd.cmd_words = __cmdtab_init(parser->cmd.cmd_lst);
		parser = parser->next;
	}
	return (parser_start);
}
