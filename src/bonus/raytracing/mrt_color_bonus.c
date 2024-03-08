/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_color_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:47:18 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 14:20:53 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render_bonus.h"

/*
 * color_cap
 * -------------
 * Clamps each component of a given color vector to a maximum of 1.0.
 * This function ensures that the RGB components of the color do not exceed
 * the maximum representable value (1.0) after lighting calculations.
 */
t_fvec3	color_cap(t_fvec3 color)
{
	color.x = fmax(0.0, fmin(1.0, color.x / SAMPLES_PER_PIXEL));
	color.y = fmax(0.0, fmin(1.0, color.y / SAMPLES_PER_PIXEL));
	color.z = fmax(0.0, fmin(1.0, color.z / SAMPLES_PER_PIXEL));
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

/*
 * color_apply_checker
 * ----------------
 * Converts a color to a predefined checker
 * float color is considered between (0 to 255)
 * the checker compute only black and white for the grid.
 */
t_fvec3	color_apply_checker(const t_fuv fuv_cpy)
{
	t_fvec3	checker_color;

	if ((int)(floor(fuv_cpy.u) + floor(fuv_cpy.v)) % 2 == 0)
	{
		checker_color.x = 0;
		checker_color.y = 0;
		checker_color.z = 0;
	}
	else
	{
		checker_color.x = 1;
		checker_color.y = 1;
		checker_color.z = 1;
	}
	return (checker_color);
}
