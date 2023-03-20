/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:13:06 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/20 10:37:53 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*it;
	t_list	*next;

	if (!lst || !del)
		return ;
	it = *lst;
	while (it)
	{
		next = it->next;
		ft_lstdelone(it, del);
		it = next;
	}
	*lst = NULL;
}
