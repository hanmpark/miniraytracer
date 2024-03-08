/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:47:18 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 16:52:56 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

/*
 * color_cap
 * -------------
 * Clamps each component of a given color vector to a maximum of 1.0.
 * This function ensures that the RGB components of the color do not exceed
 * the maximum representable value (1.0) after lighting calculations.
 */
t_fvec3	color_cap(t_fvec3 color)
{
	color.x = fmin(1.0, color.x);
	color.y = fmin(1.0, color.y);
	color.z = fmin(1.0, color.z);
	return (color);
}

/*
 * color_to_byte
 * ----------------
 * Converts a color vector from normalized
 * float representation (0.0 to 1.0) to byte representation (0 to 255).
 */
t_fvec3	color_to_byte(t_fvec3 color)
{
	color.x = round(color.x * 255);
	color.y = round(color.y * 255);
	color.z = round(color.z * 255);
	return (color);
}
