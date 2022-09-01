/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:49:21 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/01 11:34:57 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__parse_cmd_token(t_cmd *cmd, t_lexer_token *word)
{
	char	*arg;
	char	*tmp;

	arg = ft_calloc(sizeof(char), word->length + 1);
	if (!arg)
		return (-1);
	cmd->size += 1;
	tmp = word->start;
	while (tmp != word->end)
		*(arg++) = *(tmp++);
	*(arg) = '\0';
	arg -= word->length;
	ft_lstadd_back(&(cmd->cmd_lst), ft_lstnew(arg));
	return (0);
}

int	__pars_cmd(t_cmd *cmd, t_llist *lexer)
{
	while (lexer)
	{
		if (lexer && ((t_lexer_token *)lexer->content)->type == LEX_OP_REDIR)
			lexer = lexer->next->next;
		if (lexer && ((t_lexer_token *)lexer->content)->type == TYPE_LEXER_WORD)
		{
			if (__parse_cmd_token(cmd, ((t_lexer_token *)lexer->content)) == -1)
				return (-1);
			lexer = lexer->next;
		}
		if (lexer && ((t_lexer_token *)lexer->content)->type == LEX_OP_LOGIC)
			break ;
	}
	return (0);
}
