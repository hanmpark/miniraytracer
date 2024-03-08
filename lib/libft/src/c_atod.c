/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_atof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:26:15 by hanmpark          #+#    #+#             */
/*   Updated: 2024/02/28 09:37:44 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	c_atod(const char *str)
{
	double	res;
	double	fraction;
	double	sign;

	res = 0.0;
	fraction = 0.1;
	sign = 1.0;
	while (c_isspace(*str))
		str++;
	if (*str == '-' && str++)
		sign = -1.0;
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		res = res * 10.0 + (*str++ - '0');
	if (*str == '.' && str++)
	{
		while (ft_isdigit(*str))
		{
			res = res + (*str++ - '0') * fraction;
			fraction *= 0.1;
		}
	}
	return (sign * res);
}
