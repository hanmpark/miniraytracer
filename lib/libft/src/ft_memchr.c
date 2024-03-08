/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:20:47 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:20:50 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_n;
	unsigned char	c_conv;

	s_n = (unsigned char *)s;
	c_conv = (unsigned char)c;
	while (n--)
		if (*s_n++ == c_conv)
			return ((void *)--s_n);
	return (NULL);
}
