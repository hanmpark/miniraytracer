/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_objects_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:04:40 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/06 15:08:21 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render_bonus.h"

void	set_closest_hit(t_fvec3 cam_pos, t_hit *hit, t_obj *o)
{
	double	dist_cam_obj;

	dist_cam_obj = len_fvec3(sub_fvec3(hit->pos, cam_pos));
	if (dist_cam_obj < hit->min_dist)
	{
		hit->close_pos = hit->pos;
		hit->min_dist = dist_cam_obj;
		hit->close_obj = o;
		hit->close_normal = hit->normal;
		hit->close_fuv = hit->fuv;
	}
}

bool	hit_object(t_obj *o, t_ray ray, t_hit *hit)
{
	return (hit_sphere(o, ray, hit) \
		|| hit_plane(o, ray, hit) \
		|| hit_cylinder(o, ray, hit) \
		|| hit_cone(o, ray, hit));
}
