/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:24:54 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/15 17:32:29 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_n;
	size_t	len_little;

	if (big == NULL && len == 0)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	big_n = (char *)big;
	len_little = ft_strlen(little);
	while (ft_strncmp(little, big_n, len_little) != 0)
	{
		if (*big_n == '\0' || len-- < 1)
			return (NULL);
		big_n++;
	}
	if (len_little > len)
		return (NULL);
	return (big_n);
}
