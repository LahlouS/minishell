/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:26:44 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 19:08:28 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__lexer_end_pipe_check(t_llist **lexer)
{
	t_llist	*tmp;

	tmp = ft_llstlast(*lexer);
	if (!tmp || *lexer == tmp)
		return ;
	if (((t_lexer_token *)tmp->content)->type == LEX_OP_LOGIC)
	{
		write(2, "minishell: unilateral pipe not supported\n", 41);
		__parser_update_status((t_data *)g_lob_ptr, 2);
		lexer_free(lexer);
	}
}

t_llist	*lexer(char *usr_input)
{
	t_llist	*lexer;

	lexer = NULL;
	lexer_make(&lexer, usr_input);
	if (lexer)
		__lexer_end_pipe_check(&lexer);
	return (lexer);
}
