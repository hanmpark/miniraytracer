#include "mrt_parsing.h"

static bool	check_specular(const double shininess, const double reflection)
{
	return ((shininess >= 0.0 && shininess <= 256.0) \
		&& (reflection >= 0.0 && reflection <= 1.0));
}

bool	parse_sphere(t_mrt *v, char **args, int *o, int *l)
{
	int	len;

	(void)l;
	len = c_arraylen(args);
	if (len != NB_SPH_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	v->objs[*o].type = SPHERE;
	if (!set_sphere_data(&v->objs[*o], args) \
		|| !get_rgb(c_split_func(args[3], &c_iscomma), &v->objs[*o].color))
		return (error_clean_array("", args));
	if (len == NB_SPH_ARGS)
	{
		if (!get_double(args[4], &v->objs[*o].shininess, true) \
			|| !get_double(args[5], &v->objs[*o].reflection, true) \
			|| !get_boolean(args[6], &v->objs[*o].is_checker))
			return (error_clean_array("", args));
	}
	else
	{
		v->objs[*o].shininess = 0.0;
		v->objs[*o].reflection = 0.0;
		v->objs[*o].is_checker = false;
	}
	c_free_void_array((void **)args);
	if (!check_specular(v->objs[*o].shininess, v->objs[*o].reflection))
		return (error_bool(ERR_SPECULAR));
	(*o)++;
	return (true);
}

bool	parse_plane(t_mrt *v, char **args, int *o, int *l)
{
	int	len;

	(void)l;
	len = c_arraylen(args);
	if (len != NB_PLA_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	v->objs[*o].type = PLANE;
	if (!set_plane_data(&v->objs[*o], args) \
		|| !get_rgb(c_split_func(args[3], &c_iscomma), &v->objs[*o].color))
		return (error_clean_array("", args));
	if (len == NB_PLA_ARGS)
	{
		if (!get_double(args[4], &v->objs[*o].shininess, true) \
			|| !get_double(args[5], &v->objs[*o].reflection, true) \
			|| !get_boolean(args[6], &v->objs[*o].is_checker))
			return (error_clean_array("", args));
	}
	else
	{
		v->objs[*o].shininess = 0.0;
		v->objs[*o].reflection = 0.0;
		v->objs[*o].is_checker = false;
	}
	c_free_void_array((void **)args);
	if (!check_specular(v->objs[*o].shininess, v->objs[*o].reflection))
		return (error_bool(ERR_SPECULAR));
	(*o)++;
	return (true);
}

bool	parse_cylinder(t_mrt *v, char **args, int *o, int *l)
{
	int	len;

	(void)l;
	len = c_arraylen(args);
	if (len != NB_REV_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	v->objs[*o].type = CYLINDER;
	if (!set_revolution_data(&v->objs[*o], args) \
		|| !get_rgb(c_split_func(args[5], &c_iscomma), &v->objs[*o].color))
		return (error_clean_array("", args));
	if (len == NB_REV_ARGS)
	{
		if (!get_double(args[6], &v->objs[*o].shininess, true) \
			|| !get_double(args[7], &v->objs[*o].reflection, true) \
			|| !get_boolean(args[8], &v->objs[*o].is_checker))
			return (error_clean_array("", args));
	}
	else
	{
		v->objs[*o].shininess = 0.0;
		v->objs[*o].reflection = 0.0;
		v->objs[*o].is_checker = false;
	}
	c_free_void_array((void **)args);
	if (!check_specular(v->objs[*o].shininess, v->objs[*o].reflection))
		return (error_bool(ERR_SPECULAR));
	(*o)++;
	return (true);
}

bool	parse_cone(t_mrt *v, char **args, int *o, int *l)
{
	int	len;

	(void)l;
	len = c_arraylen(args);
	if (len != NB_REV_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	v->objs[*o].type = CONE;
	if (!set_revolution_data(&v->objs[*o], args) \
		|| !get_rgb(c_split_func(args[5], &c_iscomma), &v->objs[*o].color))
		return (error_clean_array("", args));
	if (len == NB_REV_ARGS)
	{
		if (!get_double(args[6], &v->objs[*o].shininess, true) \
			|| !get_double(args[7], &v->objs[*o].reflection, true) \
			|| !get_boolean(args[8], &v->objs[*o].is_checker))
			return (error_clean_array("", args));
	}
	else
	{
		v->objs[*o].shininess = 0.0;
		v->objs[*o].reflection = 0.0;
		v->objs[*o].is_checker = false;
	}
	c_free_void_array((void **)args);
	if (!check_specular(v->objs[*o].shininess, v->objs[*o].reflection))
		return (error_bool(ERR_SPECULAR));
	(*o)++;
	return (true);
}
