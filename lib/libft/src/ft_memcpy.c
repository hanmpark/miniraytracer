/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:19 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:21:21 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	pd = (unsigned char *)dest;
	ps = (unsigned const char *)src;
	if (pd != NULL || ps != NULL)
		while (n--)
			*pd++ = *ps++;
	return (dest);
}
