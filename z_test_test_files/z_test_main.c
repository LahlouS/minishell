/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:28 by lchan             #+#    #+#             */
/*   Updated: 2022/07/15 12:30:30 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/*
void	lexer_analyser(t_llist *lexer)
{
	if(!lexer)
	{
		printf("leaving lexer\n");
		exit(1);
	}
}
*/
void	lexer_readline(char **usr_input, char *prompt)
{
	while (!*usr_input)
	{
		*usr_input = readline(prompt);
		if (**usr_input == '\0')
		{
			free(*usr_input);
			*usr_input = NULL;
		}
	}
}

void	lexer_loop(t_lexer_data *lexer_data)
{
	char *usr_input;

	usr_input = NULL;
	if (lexer_data->read_lst == NULL)
		lexer_readline(&usr_input, FIRST_PROMPT);
	else
		lexer_readline(&usr_input, LEXER_PROMPT);
	ft_llstadd_back(&lexer_data->read_lst, ft_llstnew(usr_input));
	lexer_make(lexer_data, usr_input);
}

/*
void	lexer_add_history(t_llist *read_lst)
{
	char	*full_str;

	full_str = (char *)read_lst->content;
	read_lst = read_lst->next;
	while (read_lst)
	{
		full_str = ft_strjoin(full_str, (char *)read_lst->content);
		read_lst = read_lst->next;
	}
	add_history(full_str);
	free(full_str);
	//if (full_str != read_lst)
	//	free(full_str);
}
*/

int main (int ac, char **av, char **envp)
{
	//char *usr_input;
	(void) ac;
	(void) av;
	(void) envp;
	t_lexer_data	lexer_data;

	lexer_data.lexer = NULL;
	lexer_data.read_lst = NULL;
	//while (!lexer_data.lexer)
	lexer_loop(&lexer_data);
	//lexer_add_history(lexer_data.read_lst);
	__visual_print_lexer(lexer_data.lexer);
	__visual_print_read_lst(lexer_data.read_lst);
	if (lexer_data.read_lst)
		lexer_add_history(lexer_data.read_lst);
	lexer_data_free(&lexer_data);
}

