/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:47:18 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 23:54:09 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

t_fvec3	color_cap(t_fvec3 color)
{
	color.x = fmin(1.0, color.x);
	color.y = fmin(1.0, color.y);
	color.z = fmin(1.0, color.z);
	return (color);
}

t_fvec3	color_to_byte(t_fvec3 color)
{
	color.x = round(color.x * 255);
	color.y = round(color.y * 255);
	color.z = round(color.z * 255);
	return (color);
}
