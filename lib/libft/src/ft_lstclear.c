/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:50:20 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/27 00:46:37 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list_temp;

	if (lst == NULL || del == NULL)
		return ;
	list_temp = *lst;
	while (*lst)
	{
		list_temp = list_temp->next;
		ft_lstdelone(*lst, del);
		*lst = list_temp;
	}
}
