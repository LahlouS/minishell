/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ulti_free2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:29:43 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 13:30:15 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__free_u_rl_history(t_data *msh_data)
{
	(void) msh_data;
	rl_clear_history();
}

void	__free_u_user_input(t_data *msh_data)
{
	ft_free_char(&msh_data->user_input);
}

void	__free_u_lexer(t_data *msh_data)
{
	lexer_free(&msh_data->lexer);
}

void	__free_u_parse(t_data *msh_data)
{
	__free_parse(&msh_data->parser);
}
