/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_set_mat_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:08:15 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/05 17:24:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing_bonus.h"

static bool	set_mat(t_obj *obj, t_fvec3 pos, t_fvec3 rot, t_fvec3 scale)
{
	int	i;

	i = -1;
	while (++i < 7)
		identity_mat4x4(obj->fmat4x4[i]);
	translation_mat4x4(obj->fmat4x4[TRANSLATION], pos);
	convert_radian(&rot, false);
	rot_x_mat4x4(obj->fmat4x4[ROTX], rot.x);
	rot_y_mat4x4(obj->fmat4x4[ROTY], rot.y);
	rot_z_mat4x4(obj->fmat4x4[ROTZ], rot.z);
	scale_mat4x4(obj->fmat4x4[SCALE], scale);
	i = 1;
	while (++i < 7)
		mult_mat4x4(obj->fmat4x4[FORWARD], obj->fmat4x4[i]);
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
	return (set_mat(sphere, pos, new_fvec3(0.0, 0.0, 0.0), diameter));
}

bool	set_plane_data(t_obj *plane, char **args)
{
	t_fvec3	pos;
	t_fvec3	rot;

	if (!get_vector(c_split_func(args[1], &c_iscomma), &pos))
		return (false);
	if (!get_vector(c_split_func(args[2], &c_iscomma), &rot) \
		|| !check_norm(rot))
		return (false);
	return (set_mat(plane, pos, rot, new_fvec3(1.0, 1.0, 1.0)));
}

bool	set_revolution_data(t_obj *cylinder, char **args)
{
	t_fvec3	pos;
	t_fvec3	rot;
	t_fvec3	scale;
	double	tmp;

	if (!get_vector(c_split_func(args[1], &c_iscomma), &pos))
		return (false);
	if (!get_vector(c_split_func(args[2], &c_iscomma), &rot) \
		|| !check_norm(rot))
		return (false);
	if (!get_double(args[3], &tmp, false))
		return (false);
	scale.x = tmp;
	scale.y = tmp;
	if (!get_double(args[4], &tmp, false))
		return (false);
	scale.z = tmp;
	return (set_mat(cylinder, pos, rot, scale));
}
