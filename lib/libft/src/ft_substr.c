/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:24:02 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/26 20:36:40 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s_o;
	char	*s_n;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) < (size_t)start)
		return (ft_calloc(sizeof(char), 1));
	if (ft_strlen(s) - (size_t)start < len)
		s_o = (char *)malloc((ft_strlen(s) - start + 1) * sizeof(char));
	else
		s_o = (char *)malloc((len + 1) * sizeof(char));
	if (s_o == NULL)
		return (NULL);
	s_n = s_o;
	while (start-- && *s)
		s++;
	while (*s && len--)
		*s_n++ = *s++;
	*s_n = '\0';
	return (s_o);
}
