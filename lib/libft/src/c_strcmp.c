/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_strcmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:26:16 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/01 14:21:53 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Compares two strings
int	c_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - *s2);
}
