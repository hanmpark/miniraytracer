/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_set_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:08:15 by hanmpark          #+#    #+#             */
/*   Updated: 2025/12/05 23:01:01 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing.h"

static void	set_orientation(t_fmat4x4 orient, t_fvec3 dir)
{
	t_fvec3	up_ref;
	t_fvec3	right;
	t_fvec3	up;

	up_ref = new_fvec3(0.0, 0.0, 1.0);
	if (fabs(dot_fvec3(dir, up_ref)) > 0.999)
		up_ref = new_fvec3(0.0, 1.0, 0.0);
	right = norm_fvec3(cross_fvec3(up_ref, dir));
	up = norm_fvec3(cross_fvec3(dir, right));
	orient[0][0] = right.x;
	orient[0][1] = up.x;
	orient[0][2] = dir.x;
	orient[1][0] = right.y;
	orient[1][1] = up.y;
	orient[1][2] = dir.y;
	orient[2][0] = right.z;
	orient[2][1] = up.z;
	orient[2][2] = dir.z;
}

static bool	set_mat(t_obj *obj, t_fvec3 pos, t_fvec3 dir, t_fvec3 scale)
{
	t_fmat4x4	orient;
	t_fmat4x4	scale_mat;
	int			i;

	i = -1;
	while (++i < 7)
		identity_mat4x4(obj->fmat4x4[i]);
	identity_mat4x4(orient);
	identity_mat4x4(scale_mat);
	translation_mat4x4(obj->fmat4x4[TRANSLATION], pos);
	set_orientation(orient, dir);
	scale_mat4x4(scale_mat, scale);
	mult_mat4x4(obj->fmat4x4[FORWARD], obj->fmat4x4[TRANSLATION]);
	mult_mat4x4(obj->fmat4x4[FORWARD], orient);
	mult_mat4x4(obj->fmat4x4[FORWARD], scale_mat);
	if (!inv_mat4x4(obj->fmat4x4[BACKWARD], obj->fmat4x4[FORWARD]) \
		|| !extract_linear_mat3x3(obj->lintfm, obj->fmat4x4[FORWARD]))
		return (error_bool(ERR_INV_MAT));
	return (true);
}

bool	set_sphere_data(t_obj *sphere, char **args)
{
	t_fvec3	pos;
	t_fvec3	diameter;

	if (!get_vector(c_split_func(args[1], &c_iscomma), &pos))
		return (false);
	if (!get_double(args[2], &diameter.x, false))
		return (false);
	diameter.y = diameter.x;
	diameter.z = diameter.x;
	return (set_mat(sphere, pos, new_fvec3(0.0, 0.0, 1.0), diameter));
}

bool	set_plane_data(t_obj *plane, char **args)
{
	t_fvec3	pos;
	t_fvec3	norm;

	if (!get_vector(c_split_func(args[1], &c_iscomma), &pos))
		return (false);
	if (!get_vector(c_split_func(args[2], &c_iscomma), &norm) \
		|| !check_norm(&norm))
		return (false);
	return (set_mat(plane, pos, norm, new_fvec3(1.0, 1.0, 1.0)));
}

bool	set_revolution_data(t_obj *cylinder, char **args)
{
	t_fvec3	pos;
	t_fvec3	axis;
	t_fvec3	scale;
	double	tmp;

	if (!get_vector(c_split_func(args[1], &c_iscomma), &pos))
		return (false);
	if (!get_vector(c_split_func(args[2], &c_iscomma), &axis) \
		|| !check_norm(&axis))
		return (false);
	if (!get_double(args[3], &tmp, false))
		return (false);
	scale.x = tmp;
	scale.y = tmp;
	if (!get_double(args[4], &tmp, false))
		return (false);
	scale.z = tmp;
	return (set_mat(cylinder, pos, axis, scale));
}
