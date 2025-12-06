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
	t_fvec3	inc_ray;
	t_fvec3	r;
	double	dot;

	r = mult_double_fvec3(hit->close_normal, \
		2.0 * dot_fvec3(lightray.vec, hit->close_normal));
	reflectiondir = norm_fvec3(sub_fvec3(lightray.vec, r));
	inc_ray = norm_fvec3(ray.vec);
	dot = dot_fvec3(reflectiondir, inc_ray);
	if (dot > 0.0)
		return (hit->close_obj->reflection * pow(dot, \
			hit->close_obj->shininess));
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
