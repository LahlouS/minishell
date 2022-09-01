/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_test_lexer_analyser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:59:16 by luc_chan          #+#    #+#             */
/*   Updated: 2022/07/13 12:54:48 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**********
 * FOR THE MOMENT, I CHANGED MY PLAN. THIS FILE MIGHT GIVE INSPIRATION FOR SOMETHING
 *			BUT WONT BE USED FOR THE MOMENT.
 * error case:
 * multiple operator node are following each other
 * combinaison of meta char is invalid
 * lexer is ending by a redirection metachar
 *
 * syntax error near unexpected token `newline'
*/
static int  is_word_or_operator(char *start, int len)
{
	char	*tmp;

	tmp = start + len;
	while (start != tmp)
	{

	}

}

/******************
 * set the type according to *start
 * return value : the type that has been set
 * 		usefull to check if we have
 */
static int	lexer_set_type(t_llist *lexer)
{
	if (ft_strchr_b(METACHAR, ((t_lexer_token *)(lexer->content))->start))
		((t_lexer_token *)lexer->content)->type = TYPE_LEXER_OPERATOR;
	else
		((t_lexer_token *)lexer->content)->type = TYPE_LEXER_WORD;
	return (((t_lexer_token *)lexer->content)->type);
}

int lexer_analyser(t_llist *lexer)
{
	int ret_type;

	while (lexer)
	{
		ret_type = lexer_set_type(lexer);
		if (ret_type)
			return (((t_lexer_token *)(lexer->content))->index); //returning the nod index containing the error;
		lexer = lexer->next;
	}
}
