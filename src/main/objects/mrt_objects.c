/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:04:40 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 12:38:51 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

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
	}
}

bool	hit_object(t_obj *object, t_ray ray, t_hit *hit)
{
	return (hit_sphere(object, ray, hit) \
		|| hit_plane(object, ray, hit) \
		|| hit_cylinder(object, ray, hit));
}
