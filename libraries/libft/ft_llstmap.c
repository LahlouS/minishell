/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:20:34 by lchan             #+#    #+#             */
/*   Updated: 2022/07/13 12:39:08 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_llist	*ft_llstmap(t_llist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_llist	*new_l;
	t_llist	*tmp;

	tmp = NULL;
	if (!lst)
		return (NULL);
	new_l = ft_llstnew(lst->content);
	if (!new_l)
		del(new_l);
	lst = lst->next;
	tmp = new_l;
	while (lst)
	{
		ft_llstadd_back(&new_l, ft_llstnew(lst->content));
		lst = lst->next;
	}
	while (new_l)
	{
		new_l->content = f(new_l->content);
		new_l = new_l->next;
	}
	return (tmp);
}
