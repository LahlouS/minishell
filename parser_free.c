/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:12:02 by slahlou           #+#    #+#             */
/*   Updated: 2022/08/04 15:39:33 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__t_list_free(t_list **lst)
{
	t_list	*runner;

	if (*lst)
	{
		runner = *lst;
		while (runner)
		{
			if ((*lst)->content)
				free((*lst)->content);
			runner = runner->next;
			free(*lst);
			*lst = runner;
		}
	}
	*lst = NULL;
}

void	__free_io(t_io *io_struct)
{
	if (io_struct->stock)
		__t_list_free(&io_struct->stock);
	if (io_struct->here_buffer)
		__t_list_free(&io_struct->here_buffer);
}

void	__free_cmd(t_cmd cmd_struct)
{
	t_list	*tmp;

	if (cmd_struct.cmd_words)
	{
		ft_free_strtab(cmd_struct.cmd_words);
		cmd_struct.cmd_words = NULL;
	}
	if (cmd_struct.cmd_lst)
	{
		while (cmd_struct.cmd_lst)
		{
			tmp = cmd_struct.cmd_lst;
			cmd_struct.cmd_lst = cmd_struct.cmd_lst->next;
			free(tmp->content);
			free(tmp);
		}
		cmd_struct.cmd_lst = NULL;
	}
}

void	__free_parse(t_splcmd **head)
{
	t_splcmd	*runner;

	runner = *head;
	if (*head)
	{
		while (runner)
		{
			__free_io(&runner->in);
			__free_cmd(runner->cmd);
			runner = runner->next;
			free(*head);
			*head = runner;
		}
		*head = NULL;
	}
}
