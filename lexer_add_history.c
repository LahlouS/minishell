/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_add_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:07:17 by lchan             #+#    #+#             */
/*   Updated: 2022/07/22 18:57:02 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_t_llist_strlen(t_llist *read_lst, int *nbr_space)
{
	int	joined_len;
	int	separator;

	joined_len = 0;
	separator = 0;
	while (read_lst)
	{
		joined_len += ft_strlen((char *)read_lst->content);
		if (read_lst->next)
			separator++;
		read_lst = read_lst->next;
	}
	*nbr_space = separator;
	return (joined_len + separator);
}

static char	*lexer_t_llist_join(t_llist *read_lst, char sep)
{
	int		len;
	int		nbr_space;
	char	*joined;
	char	*ptr_reader;

	len = lexer_t_llist_strlen(read_lst, &nbr_space);
	joined = malloc(sizeof(char) * len + 1);
	while (read_lst)
	{
		ptr_reader = (char *)read_lst->content;
		while (*ptr_reader)
			*(joined++) = *(ptr_reader++);
		if (nbr_space--)
			*(joined++) = sep;
		read_lst = read_lst->next;
	}
	*(joined) = '\0';
	return (joined - len);
}

void	lexer_add_history(t_llist *read_lst)
{
	char	*joined;

	joined = lexer_t_llist_join(read_lst, ' ');
	add_history(joined);
	free(joined);
}
