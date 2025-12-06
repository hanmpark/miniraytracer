/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 00:22:48 by hanmpark          #+#    #+#             */
/*   Updated: 2025/12/05 22:58:30 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

static void	hit_surface_normal(t_hit *hit, t_fvec3 ray, t_obj *o, int type)
{
	t_fvec3	obj_normal;

	hit->pos = mult_mat4x4_fvec3(ray, o->fmat4x4[FORWARD]);
	if (type == SIDE)
	{
		compute_spheric_uv(hit, ray, CYLINDER);
		obj_normal = new_fvec3(ray.x, ray.y, 0.0);
	}
	else
	{
		compute_planar_uv(hit, ray, CYLINDER);
		obj_normal = new_fvec3(0.0, 0.0, ray.z);
	}
	hit->normal = norm_fvec3(mult_mat3x3_fvec3(obj_normal, o->lintfm));
}

static double	side_isect(t_fvec3 pos, t_fvec3 dir, t_fvec3 *ray)
{
	double	root;

	root = solve_quadratic(\
		pow(dir.x, 2.0) + pow(dir.y, 2.0), \
		2.0 * (pos.x * dir.x + pos.y * dir.y), \
		pow(pos.x, 2.0) + pow(pos.y, 2.0) - 1.0, INFINITY);
	if (root == INFINITY)
		return (INFINITY);
	*ray = add_fvec3(pos, mult_double_fvec3(dir, root));
	if (fabs(ray->z) >= 1.0)
		return (INFINITY);
	return (root);
}

static double	cap_isect(t_fvec3 pos, t_fvec3 dir, t_fvec3 *ray)
{
	double	root;
	double	root1;
	double	root2;

	if (close_enough(dir.z, 0.0))
		return (INFINITY);
	root1 = (pos.z - 1.0) / -dir.z;
	root2 = (pos.z + 1.0) / -dir.z;
	if (root1 > 0.0 && root1 < root2)
		root = root1;
	else if (root2 > 0.0)
		root = root2;
	else
		return (INFINITY);
	*ray = add_fvec3(pos, mult_double_fvec3(dir, root));
	if (sqrt(pow(ray->x, 2.0) + pow(ray->y, 2.0)) >= 1.0)
		return (INFINITY);
	return (root);
}

static bool	cylinder_root(t_hit *hit, t_fvec3 pos, t_fvec3 dir, t_obj *o)
{
	double	root_cyl;
	double	root_cap;
	t_fvec3	new_cylray;
	t_fvec3	new_capray;

	root_cyl = side_isect(pos, dir, &new_cylray);
	root_cap = cap_isect(pos, dir, &new_capray);
	if (root_cyl == INFINITY && root_cap == INFINITY)
		return (false);
	if (root_cyl < root_cap)
		hit_surface_normal(hit, new_cylray, o, SIDE);
	else
		hit_surface_normal(hit, new_capray, o, CAP);
	return (true);
}

bool	hit_cylinder(t_obj *object, t_ray ray, t_hit *hit)
{
	t_ray	backray;
	t_fvec3	dir;

	if (object->type != CYLINDER)
		return (false);
	backray = ray_apply_matrix(ray, object->fmat4x4[BACKWARD]);
	dir = norm_fvec3(backray.vec);
	if (!cylinder_root(hit, backray.pos, dir, object))
		return (false);
	set_closest_hit(ray.pos, hit, object);
	return (true);
}
