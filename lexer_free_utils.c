/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:10:54 by luc_chan          #+#    #+#             */
/*   Updated: 2022/08/02 12:04:09 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	t_llist_free(t_llist **lexer)
{
	t_llist	*tmp;

	while (*lexer)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp->content);
		free(tmp);
	}
	*lexer = NULL;
}

void	lexer_free(t_llist **lexer)
{
	t_llist	*tmp;

	while (*lexer)
	{
		tmp = *lexer;
		*lexer = (*lexer)->next;
		free(tmp->content);
		free(tmp);
	}
	*lexer = NULL;
}
