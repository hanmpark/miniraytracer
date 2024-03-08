/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:23:19 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/06 23:47:42 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render_bonus.h"

static t_fvec3	pixel_color(t_th *clu, t_ray camray)
{
	t_fvec3	color;
	t_hit	hit;
	int		i;

	color = new_fvec3(0.0, 0.0, 0.0);
	hit.min_dist = INFINITY;
	i = 0;
	while (i < clu->v->nb_objs)
	{
		if (hit_object(&clu->v->objs[i], camray, &hit))
			color = raytracing(clu, camray, hit);
		i++;
	}
	return (color);
}

static void	render_anti_aliasing(t_th *clu, int x, int y)
{
	t_fvec3	col;
	int		sample_count;

	col = new_fvec3(0.0, 0.0, 0.0);
	sample_count = -1;
	while (++sample_count < SAMPLES_PER_PIXEL)
	{
		clu->count_ref_rays = 0;
		setup_camera_ray(clu->v, &clu->camray, (double)x, (double)y);
		col = add_fvec3(col, pixel_color(clu, clu->camray));
	}
	col = color_to_byte(color_cap(col));
	mrt_mlx_put_pixel(clu->v, x, y, mrt_color_mlx(0, col.x, col.y, col.z));
}

static void	render_simple(t_th *clu, int x, int y)
{
	t_fvec3	col;

	clu->count_ref_rays = 0;
	setup_camera_ray(clu->v, &clu->camray, (double)x, (double)y);
	col = pixel_color(clu, clu->camray);
	col = color_to_byte(color_cap(col));
	mrt_mlx_put_pixel(clu->v, x, y, mrt_color_mlx(0, col.x, col.y, col.z));
}

void	*render(void *arg)
{
	t_th	*clu;
	int		x;
	int		y;

	clu = (t_th *)arg;
	y = clu->start_y;
	while (y < clu->end_y)
	{
		x = -1;
		while (++x < SCR_WID)
		{
			if (SAMPLES_PER_PIXEL > MIN_SAMPLES)
				render_anti_aliasing(clu, x, y);
			else
				render_simple(clu, x, y);
		}
		y++;
	}
	return (NULL);
}
