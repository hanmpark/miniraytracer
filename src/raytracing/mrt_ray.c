#include "mrt_render.h"

t_ray	setup_light_ray(t_hit *hit, t_fvec3 lightdir)
{
	t_ray	lightray;
	t_fvec3	biased_close_pos;

	biased_close_pos = add_fvec3(hit->close_pos, \
		mult_double_fvec3(hit->close_normal, SHADOW_BIAS));
	lightray.pos = biased_close_pos;
	lightray.dir = add_fvec3(lightray.pos, lightdir);
	lightray.vec = sub_fvec3(lightray.dir, lightray.pos);
	return (lightray);
}

t_ray	ray_apply_matrix(t_ray ray_cpy, const t_fmat4x4 m_ptr)
{
	t_ray	new_ray;

	new_ray.pos = mult_mat4x4_fvec3(ray_cpy.pos, m_ptr);
	new_ray.dir = mult_mat4x4_fvec3(ray_cpy.dir, m_ptr);
	new_ray.vec = sub_fvec3(new_ray.dir, new_ray.pos);
	return (new_ray);
}

void	setup_camera_ray(t_mrt *v, t_ray *camray, double x, double y)
{
	static const double	scr_xinv2 = (1.0 / ((double)SCR_WID / 2.0));
	static const double	scr_yinv2 = (1.0 / ((double)SCR_HGH / 2.0));

	x = x * scr_xinv2 - 1.0;
	y = y * scr_yinv2 - 1.0;
	camray->pos = v->cam.pos;
	camray->dir = add_fvec3(\
					add_fvec3(\
						v->cam.prj_center, \
						mult_double_fvec3(v->cam.prj_u, x)), \
					mult_double_fvec3(v->cam.prj_v, y));
	camray->vec = sub_fvec3(camray->dir, camray->pos);
}

bool	cast_reflection_ray(t_mrt *v, t_ray ray, t_hit *hit)
{
	bool	found_obstruction;
	int		i;

	found_obstruction = false;
	hit->min_dist = INFINITY;
	i = -1;
	while (++i < v->nb_objs)
	{
		if (&v->objs[i] != hit->close_obj \
			&& hit_object(&v->objs[i], ray, hit))
			found_obstruction = true;
	}
	return (found_obstruction);
}

bool	cast_light_ray(t_mrt *v, t_light light, t_ray lightray, t_hit hit)
{
	bool	no_hit;
	double	objdist;
	double	lightdist;
	int		i;

	// if (v->fast_mode)
	// 	return (true);
	lightdist = len_fvec3(sub_fvec3(light.pos, hit.close_pos));
	no_hit = true;
	i = 0;
	while (no_hit == true && i < v->nb_objs)
	{
		if (&v->objs[i] != hit.close_obj \
			&& hit_object(&v->objs[i], lightray, &hit))
		{
			no_hit = false;
			objdist = len_fvec3(sub_fvec3(hit.pos, lightray.pos));
			if (objdist > lightdist)
				no_hit = true;
		}
		i++;
	}
	return (no_hit);
}
