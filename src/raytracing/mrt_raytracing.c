#include "mrt_render.h"

static t_fvec3	compute_specular_color(t_mrt *v, t_ray inc_ray, t_hit hit)
{
	t_fvec3	specular_color;
	double	intensity;
	int		i;

	specular_color = new_fvec3(0.0, 0.0, 0.0);
	i = -1;
	while (++i < v->nb_lights)
	{
		intensity = specular_intensity(v, v->lights[i], inc_ray, hit);
		specular_color = add_fvec3(specular_color, \
			mult_double_fvec3(v->lights[i].rgb, intensity));
	}
	return (specular_color);
}

static t_fvec3	compute_diffuse_color(t_mrt *v, t_hit hit)
{
	t_fvec3	diffuse;
	t_fvec3	color_light;
	int		i;

	diffuse = new_fvec3(0.0, 0.0, 0.0);
	i = -1;
	while (++i < v->nb_lights)
	{
		color_light = mult_double_fvec3(v->lights[i].rgb, \
			light_intensity(v, v->lights[i], hit));
		diffuse = add_fvec3(diffuse, color_light);
	}
	if (hit.close_obj->is_checker)
		return (mult_fvec3(add_fvec3(v->amb.rgb, diffuse), \
			color_apply_checker(hit.close_fuv)));
	return (mult_fvec3(add_fvec3(v->amb.rgb, diffuse), \
		hit.close_obj->color));
}

static t_fvec3	compute_reflection_color(t_th *clu, t_ray inc_ray, t_hit hit)
{
	t_fvec3	reflection_color;
	t_fvec3	reflection_vector;
	t_ray	reflection_ray;

	reflection_color = new_fvec3(0.0, 0.0, 0.0);
	reflection_vector = sub_fvec3(inc_ray.vec, \
		mult_double_fvec3(hit.close_normal, \
		2.0 * dot_fvec3(inc_ray.vec, hit.close_normal)));
	reflection_ray = setup_light_ray(&hit, reflection_vector);
	if (cast_reflection_ray(clu->v, reflection_ray, &hit) \
		&& clu->count_ref_rays < clu->v->max_ref_depth)
	{
		clu->count_ref_rays++;
		if (hit.close_obj->reflection > 0.0)
			reflection_color = raytracing_color(clu, reflection_ray, hit);
		else
			reflection_color = compute_diffuse_color(clu->v, hit);
	}
	return (reflection_color);
}

t_fvec3	raytracing_color(t_th *clu, t_ray incident_ray, t_hit hit)
{
	t_fvec3	diffuse_color;
	t_fvec3	reflection_color;
	t_fvec3	specular_color;
	t_fvec3	pix;
	t_hit	shade_hit;

	shade_hit = hit;
	if (dot_fvec3(shade_hit.close_normal, incident_ray.vec) > 0.0)
		shade_hit.close_normal = mult_double_fvec3(\
			shade_hit.close_normal, -1.0);
	diffuse_color = compute_diffuse_color(clu->v, shade_hit);
	specular_color = new_fvec3(0.0, 0.0, 0.0);
	reflection_color = new_fvec3(0.0, 0.0, 0.0);
	if (shade_hit.close_obj->reflection > 0.0)
		reflection_color = compute_reflection_color(\
			clu, incident_ray, shade_hit);
	pix = mult_double_fvec3(reflection_color, shade_hit.close_obj->reflection);
	pix = add_fvec3(pix, mult_double_fvec3(diffuse_color, \
		1 - shade_hit.close_obj->reflection));
	if (shade_hit.close_obj->shininess > 0.0)
		specular_color = compute_specular_color(\
			clu->v, incident_ray, shade_hit);
	pix = add_fvec3(pix, specular_color);
	return (pix);
}
