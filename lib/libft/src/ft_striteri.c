/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:26:34 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:26:36 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*p_n;

	if (s == NULL || f == NULL)
		return ;
	p_n = s;
	while (*p_n)
	{
		(*f)((p_n - s), p_n);
		p_n++;
	}
}
