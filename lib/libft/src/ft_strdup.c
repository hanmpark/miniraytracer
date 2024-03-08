/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:26:20 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/07 14:26:22 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s_o;
	char	*s_n;

	s_o = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (s_o == NULL)
		return (NULL);
	s_n = s_o;
	while (*s)
	{
		*s_n = *s;
		s_n++;
		s++;
	}
	*s_n = '\0';
	return (s_o);
}
