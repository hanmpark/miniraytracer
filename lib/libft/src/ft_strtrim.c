/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:24:24 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:24:26 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s1;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len_s1 = ft_strlen(s1);
	while (len_s1 && ft_strchr(set, s1[len_s1]))
		len_s1--;
	return (ft_substr(s1, 0, len_s1 + 1));
}
