/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_sig_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:21:19 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/08 16:27:48 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__signal_handler3(int sig)
{
	if (sig == SIGQUIT)
		return ;
}

void	__signal_handler2(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	__signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
