/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_raytracing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:05:03 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 23:15:01 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

static double	light_intensity(t_mrt *v, t_hit hit)
{
	t_ray	lightray;
	t_fvec3	lightdir;
	double	intensity;

	lightdir = norm_fvec3(sub_fvec3(v->light.pos, hit.close_pos));
	lightray = setup_light_ray(lightdir, &hit);
	intensity = 0.0;
	if (cast_light_ray(v, lightray, hit))
	{
		intensity = acos(dot_fvec3(hit.close_normal, lightdir));
		if (intensity > (PI / 2.0))
			intensity = 0.0;
		else
			intensity = (1.0 - (2.0 * intensity / PI));
	}
	return (intensity);
}

t_fvec3	raytracing_color(t_mrt *v, t_hit hit)
{
	t_fvec3	color_light;
	t_fvec3	amb;
	t_fvec3	pix;

	color_light = mult_double_fvec3(v->light.rgb, light_intensity(v, hit));
	amb = add_fvec3(v->amb.rgb, color_light);
	pix = color_to_byte(color_cap(mult_fvec3(hit.close_obj->color, amb)));
	return (pix);
}
