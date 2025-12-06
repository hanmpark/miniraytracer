#include "mrt_render.h"

static void	hit_surface_normal(t_hit *hit, t_fvec3 ray, t_obj *o)
{
	t_fvec3	obj_normal;

	compute_planar_uv(hit, ray, PLANE);
	hit->pos = mult_mat4x4_fvec3(ray, o->fmat4x4[FORWARD]);
	obj_normal = new_fvec3(0.0, 0.0, 1.0);
	hit->normal = norm_fvec3(mult_mat3x3_fvec3(obj_normal, o->lintfm));
}

static bool	plane_root(t_hit *hit, t_fvec3 pos, t_fvec3 dir, t_obj *o)
{
	double	root;
	t_fvec3	ray;

	if (close_enough(dir.z, 0.0))
		return (false);
	root = pos.z / -dir.z;
	if (root < 0.0)
		return (false);
	ray = add_fvec3(pos, mult_double_fvec3(dir, root));
	hit_surface_normal(hit, ray, o);
	return (true);
}

bool	hit_plane(t_obj *object, t_ray ray, t_hit *hit)
{
	t_ray	backray;

	if (object->type != PLANE)
		return (false);
	backray = ray_apply_matrix(ray, object->fmat4x4[BACKWARD]);
	if (!plane_root(hit, backray.pos, backray.vec, object))
		return (false);
	set_closest_hit(ray.pos, hit, object);
	return (true);
}
