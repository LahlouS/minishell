/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:13:14 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 16:31:37 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*g_lob_ptr;

char	*__readline_add_history(t_data *msh_data, char *prompt)
{
	char	*usr_input;

	usr_input = NULL;
	while (!usr_input)
	{
		usr_input = readline(prompt);
		if (!usr_input)
		{
			write(1, "exit\n", 5);
			__ultimate_free(msh_data, 0, 1);
		}
		else if (!*usr_input)
			ft_free_char(&usr_input);
	}
	add_history(usr_input);
	return (usr_input);
}

int	main(int ac, char **av, char **envp)
{
	t_data	msh_data;

	(void) ac;
	(void) av;
	signal(SIGINT, &__signal_handler);
	signal(SIGQUIT, SIG_IGN);
	__set_msh_data(&msh_data, envp);
	g_lob_ptr = &msh_data;
	while (1)
	{
		msh_data.user_input = __readline_add_history(&msh_data, FIRST_PROMPT);
		msh_data.lexer = lexer(msh_data.user_input);
		msh_data.parser = __parser(msh_data.lexer, &msh_data.parser);
		msh_data.parser = __expand(msh_data.parser, msh_data.env);
		__el_imperator(&msh_data, msh_data.parser);
		__ultimate_free(&msh_data, T_DATA_HALF, 0);
	}
	__ultimate_free(&msh_data, 0, 0);
}
