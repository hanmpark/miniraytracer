/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:50:49 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 08:59:27 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing.h"

bool	parse_sphere(t_mrt *v, char **args, int *o)
{
	if (c_arraylen(args) != NB_SPH_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	v->objs[*o].type = SPHERE;
	if (!set_sphere_data(&v->objs[*o], args) \
		|| !get_rgb(c_split_func(args[3], &c_iscomma), &v->objs[*o].color))
		return (error_clean_array("", args));
	c_free_void_array((void **)args);
	(*o)++;
	return (true);
}

bool	parse_plane(t_mrt *v, char **args, int *o)
{
	if (c_arraylen(args) != NB_PLA_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	v->objs[*o].type = PLANE;
	if (!set_plane_data(&v->objs[*o], args) \
		|| !get_rgb(c_split_func(args[3], &c_iscomma), &v->objs[*o].color))
		return (error_clean_array("", args));
	c_free_void_array((void **)args);
	(*o)++;
	return (true);
}

bool	parse_cylinder(t_mrt *v, char **args, int *o)
{
	if (c_arraylen(args) != NB_CYL_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	v->objs[*o].type = CYLINDER;
	if (!set_cylinder_data(&v->objs[*o], args) \
		|| !get_rgb(c_split_func(args[5], &c_iscomma), &v->objs[*o].color))
		return (error_clean_array("", args));
	c_free_void_array((void **)args);
	(*o)++;
	return (true);
}
