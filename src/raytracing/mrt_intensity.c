#include "mrt_render.h"

double	light_intensity(t_mrt *v, t_light light, t_hit hit)
{
	t_ray	lightray;
	t_fvec3	lightdir;
	double	intensity;

	lightdir = norm_fvec3(sub_fvec3(light.pos, hit.close_pos));
	lightray = setup_light_ray(&hit, lightdir);
	intensity = 0.0;
	if (cast_light_ray(v, light, lightray, hit))
	{
		intensity = acos(dot_fvec3(hit.close_normal, lightdir));
		if (intensity > (PI / 2.0))
			intensity = 0.0;
		else
			intensity = (1.0 - (2.0 * intensity / PI));
	}
	return (intensity);
}

static double	find_specular(t_ray lightray, t_ray ray, t_hit *hit)
{
	t_fvec3	reflectiondir;
	t_fvec3	viewdir;
	double	dot;
	double	dot_nl;

	dot_nl = dot_fvec3(lightray.vec, hit->close_normal);
	if (dot_nl <= 0.0)
		return (0.0);
	reflectiondir = sub_fvec3(mult_double_fvec3(hit->close_normal, \
		2.0 * dot_fvec3(lightray.vec, hit->close_normal)), lightray.vec);
	reflectiondir = norm_fvec3(reflectiondir);
	viewdir = norm_fvec3(mult_double_fvec3(ray.vec, -1.0));
	dot = dot_fvec3(reflectiondir, viewdir);
	if (dot > 0.0)
		return (pow(dot, hit->close_obj->shininess));
	return (0.0);
}

double	specular_intensity(t_mrt *v, t_light light, t_ray inc_ray, t_hit hit)
{
	t_ray	lightray;
	t_fvec3	lightdir;
	double	intensity;

	if (v->fast_mode)
		return (0.0);
	lightdir = norm_fvec3(sub_fvec3(light.pos, hit.close_pos));
	lightray = setup_light_ray(&hit, lightdir);
	intensity = 0.0;
	if (cast_light_ray(v, light, lightray, hit))
		intensity = find_specular(lightray, inc_ray, &hit);
	return (intensity);
}
