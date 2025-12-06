/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:45:01 by hanmpark          #+#    #+#             */
/*   Updated: 2025/12/05 22:58:30 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

void	compute_spheric_uv(t_hit *hit, t_fvec3 ray, t_type type)
{
	if (type == SPHERE)
	{
		hit->fuv.u = atan(sqrt(pow(ray.x, 2.0) + pow(ray.y, 2.0)) / ray.z) / \
			PI * SPHERE_CHECKER;
		hit->fuv.v = atan(ray.y / ray.x);
		if (ray.x < 0)
			hit->fuv.v += PI;
		hit->fuv.v /= PI / SPHERE_CHECKER;
	}
	else if (type == CYLINDER)
	{
		hit->fuv.u = atan2(ray.y, ray.x) * SPH_CYLINDER_CHECKER;
		hit->fuv.v = ray.z * SPH_CYLINDER_CHECKER;
	}
	else if (type == CONE)
	{
		hit->fuv.u = atan2(ray.y, ray.x) / (PI / 2.0) * SPH_CONE_CHECKER;
		hit->fuv.v = ray.z * 2.0 + 1.0;
		if (ray.x < 0)
			hit->fuv.v += PI;
		hit->fuv.v /= PI / SPH_CONE_CHECKER;
	}
}

void	compute_planar_uv(t_hit *hit, t_fvec3 ray, t_type type)
{
	if (type == PLANE)
	{
		hit->fuv.u = ray.x * PLANE_CHECKER;
		hit->fuv.v = ray.y * PLANE_CHECKER;
	}
	else if (type == CYLINDER)
	{
		hit->fuv.u = ray.x * PL_CYLINDER_CHECKER;
		hit->fuv.v = ray.y * PL_CYLINDER_CHECKER;
	}
	else if (type == CONE)
	{
		hit->fuv.u = ray.x * PL_CONE_CHECKER;
		hit->fuv.v = ray.y * PL_CONE_CHECKER;
	}
}
