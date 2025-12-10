#include "mrt_render.h"

static void	hit_surface_normal(t_hit *hit, t_fvec3 ray, t_obj *o, t_type type)
{
	t_fvec3	obj_normal;

	hit->pos = mult_mat4x4_fvec3(ray, o->fmat4x4[FORWARD]);
	if (type == SIDE)
	{
		compute_spheric_uv(hit, ray, CONE);
		obj_normal = new_fvec3(ray.x, ray.y, \
			sqrt((ray.x * ray.x) + (ray.y * ray.y)));
	}
	else
	{
		compute_planar_uv(hit, ray, CONE);
		obj_normal = new_fvec3(0.0, 0.0, -1.0);
	}
	hit->normal = norm_fvec3(mult_mat3x3_fvec3(obj_normal, o->lintfm));
}

static double	side_isect(t_fvec3 pos, t_fvec3 dir, t_fvec3 *ray)
{
	double	root;

	root = solve_quadratic(\
		(dir.x * dir.x) + (dir.y * dir.y) - (dir.z * dir.z), \
		2.0 * (pos.x * dir.x + pos.y * dir.y - pos.z * dir.z), \
		(pos.x * pos.x) + (pos.y * pos.y) - (pos.z * pos.z), INFINITY);
	if (root == INFINITY)
		return (INFINITY);
	*ray = add_fvec3(pos, mult_double_fvec3(dir, root));
	if (ray->z <= -1.0 || ray->z >= 0.0)
		return (INFINITY);
	return (root);
}

static double	cap_isect(t_fvec3 pos, t_fvec3 dir, t_fvec3 *ray)
{
	double	root;

	if (close_enough(dir.z, 0.0))
		return (INFINITY);
	root = (pos.z + 1.0) / -dir.z;
	if (root <= 0.0)
		return (INFINITY);
	*ray = add_fvec3(pos, mult_double_fvec3(dir, root));
	if (sqrt((ray->x * ray->x) + (ray->y * ray->y)) >= 1.0)
		return (INFINITY);
	return (root);
}

static bool	cone_root_normal(t_hit *hit, t_fvec3 pos, t_fvec3 dir, t_obj *o)
{
	double	root_cone;
	double	root_cap;
	t_fvec3	new_coneray;
	t_fvec3	new_capray;

	root_cone = side_isect(pos, dir, &new_coneray);
	root_cap = cap_isect(pos, dir, &new_capray);
	if (root_cone == INFINITY && root_cap == INFINITY)
		return (false);
	if (root_cone < root_cap)
		hit_surface_normal(hit, new_coneray, o, SIDE);
	else
		hit_surface_normal(hit, new_capray, o, CAP);
	return (true);
}

bool	hit_cone(t_obj *object, t_ray ray, t_hit *hit)
{
	t_ray	backray;
	t_fvec3	dir;

	if (object->type != CONE)
		return (false);
	backray = ray_apply_matrix(ray, object->fmat4x4[BACKWARD]);
	dir = norm_fvec3(backray.vec);
	if (!cone_root_normal(hit, backray.pos, dir, object))
		return (false);
	set_closest_hit(ray.pos, hit, object);
	return (true);
}
