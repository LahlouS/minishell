/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_io_save2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:55:37 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 11:56:22 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__save_io_arg(t_io *io)
{
	ft_lstadd_back(&(io->stock), ft_lstnew(io->arg));
}

void	__here_d_parse_lim(t_io *io)
{
	char	*tmp;
	int		quote_flag;

	tmp = io->arg;
	quote_flag = 0;
	while (*tmp)
	{
		if (ft_strchr_b("\"\'", *tmp++))
		{
			quote_flag++;
			break ;
		}
	}
	if (!quote_flag)
		ft_lstadd_back(&(io->here_buffer), ft_lstnew(ft_strdup(HD_EXP)));
	else
	{
		tmp = io->arg;
		io->arg = __here_d_unquote_limit(io->arg);
		free(tmp);
		ft_lstadd_back(&(io->here_buffer), ft_lstnew(ft_strdup(HD_NOT_EXP)));
	}
}
