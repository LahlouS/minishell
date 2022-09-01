/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_visual.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:01:10 by lchan             #+#    #+#             */
/*   Updated: 2022/08/05 10:32:37 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__visual_print_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
		while (tab[++i])
			printf("%d : %s\n",i , tab[i]);
}

void	__visial_print_type(int type)
{
	const char	*type_str [] = {
	[TYPE_LEXER_WORD] = "word",
	[LEX_OP_LOGIC] = "op logical",
	[LEX_OP_REDIR] = "op redirect",
	[LEX_SYNTAX_ERR] = "syntax error"
	};

	printf("type = %s (%d)\n", type_str[type], type);
}


void	__visual_print_lexer(t_llist *lst)
{
	if (!lst)
		printf("lst address = %p\n", lst);
	while (lst)
	{
//		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		//printf("type = %d (%s)\n", ((t_lexer_token *)lst->content)->type);
		__visial_print_type(((t_lexer_token *)lst->content)->type);
//		printf("start = %p\n", ((t_lexer_token *)lst->content)->start);
//		printf("end = %p\n", ((t_lexer_token *)lst->content)->end);
//		printf("length = %ld\n", ((t_lexer_token *)lst->content)->length);
		write(1, "str = ", 7);
		write(1, "[", 1);
		write(1,  ((t_lexer_token *)lst->content)->start,
		((t_lexer_token *)lst->content)->end -  ((t_lexer_token *)lst->content)->start);
		write(1, "]", 1);
		printf("\n\n");
		lst = lst->next;
	}
}


void	__visual_print_read_lst(t_llist *usr_input)
{
	printf("usr_input str = [");
	while (usr_input)
	{
		printf("%s", (char *)usr_input->content);
		if (usr_input->next)
			printf(" ");
		usr_input = usr_input->next;
	}
	printf("]\n");
}


/*
void	__reverse_visual_print_lexer(t_llist *lst)
{
	if (!lst)
		printf("lst address = %p\n", lst);
	while (lst->next)
		lst = lst->next;
	while (lst)
	{
//		printf("index = %d\n", ((t_lexer_token *)lst->content)->index);
		printf("type = %d\n", ((t_lexer_token *)lst->content)->type);
//		printf("start = %p\n", ((t_lexer_token *)lst->content)->start);
//		printf("end = %p\n", ((t_lexer_token *)lst->content)->end);
//		printf("length = %ld\n", ((t_lexer_token *)lst->content)->length);
		write(1, "str = ", 7);
		write(1, "[", 1);
		write(1,  ((t_lexer_token *)lst->content)->start,
		((t_lexer_token *)lst->content)->end -  ((t_lexer_token *)lst->content)->start);
		write(1, "]", 1);
		printf("\n\n");
		lst = lst->prev;
	}
}
*/
void	__visual_print_input(t_llist **runner)
{
	if (*runner)
	{
		if (((t_lexer_token *)((*runner)->content))->type == LEX_OP_LOGIC)
		{
			printf("[%.*s] ",
			((int)((t_lexer_token *)((*runner)->content))->length),
			((t_lexer_token *)((*runner)->content))->start);
			*runner = (*runner)->next;
		}
		while ( *runner && ((t_lexer_token *)((*runner)->content))->type != LEX_OP_LOGIC)
		{
			printf("[%.*s] ",
			((int)((t_lexer_token *)((*runner)->content))->length),
			((t_lexer_token *)((*runner)->content))->start);
			*runner = (*runner)->next;
		}
		if (*runner && ((t_lexer_token *)((*runner)->content))->type == LEX_OP_LOGIC)
			{
				printf("[%.*s] ",
				((int)((t_lexer_token *)((*runner)->content))->length),
				((t_lexer_token *)((*runner)->content))->start);
			}
	}
}

/******************PARSER VISUAL***************************/

void	__vparser_print_type_io(int type)
{
	const char	*type_str [] = {
	//"STDIN",
	//"STDOUT",
	NULL,
	"IN _D",
	"HERE_D",
	"PIPE_IN",
	"OUT_D",
	"OUT_D_APP",
	"PIPE_OUT",
	};

	printf("	>>>type = %s(%d)<<<\n", type_str[type], type);
}

void	__vparser_print_type_cmd(int type)
{
	const char	*type_str [] = {
	"CMD_OUT",
	"CMD_ECHO",
	"CMD_CD",
	"CMD_PWD",
	"CMD_EXP",
	"CMD_UNSET",
	"CMD_ENV",
	"CMD_EXIT",
	"CMD_ERR"
	};

	printf("	>>>type = %s(%d)<<<\n", type_str[type], type);
}

void	__visual_print_splcmd(t_splcmd *head, t_llist *lexer)
{
	int block_ind = 0;
	char	*star = "*********************************************";

	while (head)
	{
		char **cmd_tab_tmp = head->cmd.cmd_words;
		t_list	*tmp_in_st = head->in.stock,
		*tmp_out_st = head->out.stock,
		*tmp_here_d = head->in.here_buffer;

		printf("\t*********************************splcmd [%d]*********************************%s\n", block_ind++, star);
		printf("\t\tin_addr: [%p] out_addr: [%p] cmd_addr: [%p]\n",
		&(head->in), &(head->out), &(head->cmd));
		printf("\t\tlexer: "); __visual_print_input(&lexer);

		printf("\n\n		----IN_STOCK ------------>"); __vparser_print_type_io(head->in.type);
		printf("\t\tfd = %d\n", head->in.fd);
		if (tmp_in_st){printf("\t\t");} for (int i = 0;(tmp_in_st);i++)
		{
			printf("arg[%d] --> %s  |  ", i, (char *)(tmp_in_st->content));
			tmp_in_st = tmp_in_st->next;
		}
		if (tmp_here_d){printf("\n");} for (int i = 0;(tmp_here_d);i++)
		{
			printf("\t\t"); printf("here_d[%d] --> %s", i, (char *)(tmp_here_d->content));
			tmp_here_d = tmp_here_d->next;
		}

		printf("\n\n		----OUT_STOCK ----------->"); __vparser_print_type_io(head->out.type);
		printf("\t\tfd = %d\n", head->out.fd);
		printf("\t\t"); for (int i = 0;(tmp_out_st);i++)
		{
			printf("arg[%d] --> %s ~ [%c]  |  ", i, (char *)(tmp_out_st->content), ((char *)(tmp_out_st->content))[ft_strlen((char *)(tmp_out_st->content)) + 1]);
			tmp_out_st = tmp_out_st->next;
		}

		t_list *tmp_cmd = head->cmd.cmd_lst; int size = head->cmd.size;
		printf("\n\n		----CMD_STOCK ----------->"); __vparser_print_type_cmd(head->cmd.type);
		printf("\t\t"); printf("size = %d\n", size);
		for (int i = 0; i < size;i++)
		{
			printf("\t\t"); printf("cmd_lst[%d] --> %s\n", i + 1,(char *)(tmp_cmd->content));
			tmp_cmd = tmp_cmd->next;
		}
		__visual_print_tab(cmd_tab_tmp);
		head = head->next;
		puts("\n");
	}
}
