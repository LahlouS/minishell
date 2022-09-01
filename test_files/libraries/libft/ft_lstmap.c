/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:20:34 by lchan             #+#    #+#             */
/*   Updated: 2021/12/07 19:16:21 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*tmp;

	tmp = NULL;
	if (!lst)
		return (NULL);
	new_l = ft_lstnew(lst->content);
	if (!new_l)
		del(new_l);
	lst = lst->next;
	tmp = new_l;
	while (lst)
	{
		ft_lstadd_back(&new_l, ft_lstnew(lst->content));
		lst = lst->next;
	}
	while (new_l)
	{
		new_l->content = f(new_l->content);
		new_l = new_l->next;
	}
	return (tmp);
}
