/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:39:35 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 12:50:05 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llstclear(t_llist **lst, void (*del)(void *))
{
	t_llist	*tmp;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_llstdelone(*lst, del);
		*lst = tmp;
	}
}
