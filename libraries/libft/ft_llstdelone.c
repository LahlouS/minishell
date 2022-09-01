/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:39:07 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 11:52:41 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llstdelone(t_llist *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free (lst);
	lst = NULL;
}
