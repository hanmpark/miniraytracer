/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 21:40:26 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/08 15:38:24 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

static void	render_scene(t_mrt *v, int x, int y)
{
	t_fvec3	color;
	t_hit	hit;
	int		i;

	hit.min_dist = INFINITY;
	i = 0;
	while (i < v->nb_objs)
	{
		if (hit_object(&v->objs[i], v->cam.ray, &hit))
		{
			color = raytracing_color(v, hit);
			mrt_mlx_put_pixel(v, x, y, \
				mrt_color_mlx(0, color.x, color.y, color.z));
		}
		i++;
	}
}

int	render_screen(t_mrt *v)
{
	int	x;
	int	y;

	mrt_mlx_clear(v);
	y = 0;
	while (y < SCR_HGH)
	{
		x = 0;
		while (x < SCR_WID)
		{
			setup_camera_ray(v, (double)x, (double)y);
			render_scene(v, x, y);
			x++;
		}
		y++;
	}
	mrt_mlx_refresh(v);
	return (0);
}
