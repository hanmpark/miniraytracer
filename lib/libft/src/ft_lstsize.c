/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 17:42:16 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/15 17:43:33 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len_lst;

	if (lst == NULL)
		return (0);
	len_lst = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		len_lst++;
	}
	return (len_lst);
}
