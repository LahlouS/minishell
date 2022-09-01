/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:16:07 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 15:37:20 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__cnt_tablen_str(char *str)
{
	int	cnt;

	cnt = 0;
	if (str && *str == '\0')
		cnt++;
	while (1)
	{
		while (*str == -1)
			str++;
		if (*str && *str != -1)
			cnt++;
		while (*str && *str != -1)
		{
			if (*str == -2)
				*str = '\'';
			if (*str == -3)
				*str = '\"';
			str++;
		}
		if (!*str)
			break ;
	}
	return (cnt);
}

int	__cnt_tablen(t_list *cmd_lst)
{
	int	len;

	len = 0;
	while (cmd_lst)
	{
		len += __cnt_tablen_str((char *)(cmd_lst->content));
		cmd_lst = cmd_lst->next;
	}
	return (len);
}

char	**__split_node(char *str, char **cmd_tab, int nb_wrd)
{
	int	i;

	while (nb_wrd)
	{
		i = 0;
		while (*str && *str == -1)
			str++;
		while (str[i] && str[i] != -1)
			i++;
		str[i] = '\0';
		*cmd_tab = ft_strdup(str);
		str += i + 1;
		cmd_tab++;
		nb_wrd--;
	}
	return (cmd_tab);
}

char	**__cmdtab_init(t_list *cmd_lst)
{
	int		tab_len;
	char	**cmd_tab;
	int		nb_wrd;

	if (!cmd_lst)
		return (NULL);
	tab_len = __cnt_tablen(cmd_lst);
	cmd_tab = ft_calloc(sizeof(char *), tab_len + 1);
	if (!cmd_tab)
		return (0);
	cmd_tab[tab_len] = NULL;
	while (cmd_lst)
	{
		nb_wrd = __cnt_tablen_str((char *)(cmd_lst->content));
		cmd_tab = __split_node((char *)(cmd_lst->content), cmd_tab, nb_wrd);
		cmd_lst = cmd_lst->next;
	}
	return (cmd_tab - tab_len);
}
