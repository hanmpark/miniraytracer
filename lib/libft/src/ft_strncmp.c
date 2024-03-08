/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:25:13 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:25:14 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_n;
	unsigned char	*s2_n;

	s1_n = (unsigned char *)s1;
	s2_n = (unsigned char *)s2;
	while (n--)
	{
		if (*s1_n != *s2_n)
			return ((int)(*s1_n - *s2_n));
		else if (*s1_n == '\0')
			return (0);
		s1_n++;
		s2_n++;
	}
	return (0);
}
