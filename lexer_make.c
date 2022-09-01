/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:25:32 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 19:10:13 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_syntax_checker(
	t_lexer_token *current_nod, t_lexer_token *previous_nod)
{
	if ((!previous_nod && current_nod->type == LEX_OP_LOGIC))
	{
		current_nod->type = LEX_SYNTAX_ERR;
		return (ERR_SYNTAX);
	}
	else if (previous_nod
		&& previous_nod->type != TYPE_LEXER_WORD
		&& current_nod->type != TYPE_LEXER_WORD
		&& previous_nod->type - current_nod->type != -1)
	{
		current_nod->type = LEX_SYNTAX_ERR;
		return (ERR_SYNTAX);
	}
	return (0);
}

/*********************
 * give the right start address, end address, lenght and set the type.
 * set the length;
 * return : non 0 value if problem, 0 if ok.
 */
static int	lexer_set_nod(t_lexer_token *tmp_nod)
{
	if (lexer_set_ptrs(&tmp_nod->start, &tmp_nod->end))
		return (ERR_SET_PTR);
	tmp_nod->length = tmp_nod->end - tmp_nod->start;
	if (ft_strchr_b(METACHAR, *(tmp_nod->start)))
	{
		if (ft_strchr_b(LOG_META, *(tmp_nod->start)))
			tmp_nod->type = LEX_OP_LOGIC;
		else
			tmp_nod->type = LEX_OP_REDIR;
	}
	else
		tmp_nod->type = TYPE_LEXER_WORD;
	return (0);
}

static t_lexer_token	*lexer_add_nod(t_llist **lexer, char *str)
{
	t_lexer_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_lexer_token));
	if (!new_token)
		return (NULL);
	new_token->start = str;
	new_token->end = str;
	if (!lexer_set_nod(new_token))
		ft_llstadd_back(lexer, ft_llstnew(new_token));
	else
	{
		if (new_token->end == NULL)
		{
			lexer_error(ERR_SOLO_QUOTE, NULL);
			lexer_free(lexer);
		}
		free(new_token);
		new_token = NULL;
	}
	return (new_token);
}

int	lexer_error(int error_id, t_lexer_token *current)
{
	if (!error_id)
		return (0);
	else
	{
		if (error_id == ERR_SOLO_QUOTE)
		{
			__parser_update_status((t_data *)g_lob_ptr, 2);
			ft_putstr_fd("minishell: unclosed quotation not supported\n", 2);
		}
		if (error_id == ERR_SYNTAX)
		{
			__parser_update_status((t_data *)g_lob_ptr, 2);
			ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
			write(2, current->start, (int)(current->length));
			write(2, "'\n", 2);
		}
	}
	return (error_id);
}

void	lexer_make(t_llist **lexer, char *str)
{
	t_lexer_token	*previous_nod;
	t_lexer_token	*current_nod;

	previous_nod = NULL;
	current_nod = NULL;
	while (1)
	{
		current_nod = (lexer_add_nod(lexer, str));
		if (!current_nod)
			return ;
		if (lexer_error
			(lexer_syntax_checker(current_nod, previous_nod), current_nod))
			return ;
		previous_nod = current_nod;
		str = previous_nod->end;
	}
}
