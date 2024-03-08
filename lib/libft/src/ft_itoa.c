/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:20:36 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:20:39 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_intstrlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p_o;
	size_t	len_n;

	len_n = ft_intstrlen(n);
	p_o = ft_calloc((len_n + 1), sizeof(char));
	if (p_o == NULL)
		return (NULL);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_strlcpy(p_o, "-2147483648", 12);
			return (p_o);
		}
		*p_o = '-';
		n *= -1;
	}
	p_o[len_n] = '\0';
	while (len_n--)
	{
		if (p_o[len_n] != '-')
			p_o[len_n] = (n % 10) + '0';
		n /= 10;
	}
	return (p_o);
}
