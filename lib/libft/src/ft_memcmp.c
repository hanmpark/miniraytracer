/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:20:56 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:21:13 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_n;
	unsigned char	*s2_n;

	s1_n = (unsigned char *)s1;
	s2_n = (unsigned char *)s2;
	while (n--)
		if (*s1_n++ != *s2_n++)
			return (*--s1_n - *--s2_n);
	return (0);
}
