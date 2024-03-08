/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_isdouble.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:21:29 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/03 19:27:09 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_max_len(char *str)
{
	int	count_integer;
	int	count_fractional;
	int	i;

	count_integer = 0;
	count_fractional = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '.')
		{
			while (str[++i])
				count_fractional++;
			break ;
		}
		count_integer++;
	}
	if (count_integer > 5 || count_fractional > 5)
		return (0);
	return (1);
}

int	c_isdouble(char *str)
{
	int	i;
	int	dot;
	int	digit;

	i = 0;
	dot = 0;
	digit = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		else if (!ft_isdigit(str[i]))
			return (0);
		else
			digit = 1;
		i++;
	}
	if (dot > 1 || !digit || !count_max_len(str))
		return (0);
	return (1);
}
