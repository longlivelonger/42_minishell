/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stanislavkomin <stanislavkomin@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:10:47 by stanislavko       #+#    #+#             */
/*   Updated: 2021/10/12 15:30:10 by stanislavko      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*temp;	

	if (lst == 0)
		return (0);
	newlst = ft_lstnew(f(lst->content));
	if (newlst == 0)
		return (0);
	lst = lst->next;
	temp = newlst;
	while (lst != 0)
	{
		temp->next = ft_lstnew(f(lst->content));
		if (temp->next == 0)
		{
			ft_lstclear(&newlst, del);
			return (0);
		}
		lst = lst->next;
		temp = temp->next;
	}
	return (newlst);
}
