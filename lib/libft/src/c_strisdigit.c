/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_strisdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <yobouhle@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:45:30 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/06 06:51:37 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Checks if the string is only composed of digits
int	c_strisdigit(char *str)
{
	int	i;

	if (str[0] == '-')
		i = 0;
	else
		i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
