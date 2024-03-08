/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:41:26 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 08:33:30 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing.h"

static void	set_cam_screen(t_cam *cam)
{
	static const double	scr_ratio = (double)SCR_WID / (double)SCR_HGH;
	double				fov;

	fov = cam->fov * (M_PI / 180.0);
	cam->prj_u = mult_double_fvec3(\
					norm_fvec3(cross_fvec3(cam->align, cam->up)), \
					fov);
	cam->prj_v = mult_double_fvec3(\
					norm_fvec3(\
						cross_fvec3(cam->align, cam->prj_u)), \
					fov / scr_ratio);
	cam->prj_center = add_fvec3(cam->pos, cam->align);
}

static void	set_cam_data(t_cam *cam)
{
	t_fmat4x4	rotation_mat[3];

	cam->up = new_fvec3(0.0, 0.0, 1.0);
	cam->align = new_fvec3(0.0, 1.0, 0.0);
	identity_mat4x4(rotation_mat[0]);
	identity_mat4x4(rotation_mat[1]);
	identity_mat4x4(rotation_mat[2]);
	convert_radian(&cam->lookat, true);
	rot_x_mat4x4(rotation_mat[0], cam->lookat.x);
	rot_y_mat4x4(rotation_mat[1], cam->lookat.y);
	rot_z_mat4x4(rotation_mat[2], cam->lookat.z);
	cam->align = mult_mat4x4_fvec3(cam->align, rotation_mat[0]);
	cam->up = mult_mat4x4_fvec3(cam->up, rotation_mat[1]);
	cam->align = mult_mat4x4_fvec3(cam->align, rotation_mat[2]);
}

bool	parse_cam(t_mrt *v, char **args, int *o)
{
	(void)o;
	if (c_arraylen(args) != NB_CAM_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	if (!get_vector(c_split_func(args[1], &c_iscomma), &v->cam.pos) \
		|| !get_vector(c_split_func(args[2], &c_iscomma), &v->cam.lookat) \
		|| !check_norm(v->cam.lookat) \
		|| !get_fov(args[3], &v->cam.fov))
		return (error_clean_array("", args));
	c_free_void_array((void **)args);
	set_cam_data(&v->cam);
	set_cam_screen(&v->cam);
	return (true);
}

bool	parse_amb(t_mrt *v, char **args, int *o)
{
	(void)o;
	if (c_arraylen(args) != NB_AMB_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	if (!get_double(args[1], &v->amb.ratio, true) \
		|| !get_rgb(c_split_func(args[2], &c_iscomma), &v->amb.rgb))
		return (error_clean_array("", args));
	if (v->amb.ratio < 0.0 || v->amb.ratio > 1.0)
		return (error_clean_array(ERR_RATIO, args));
	v->amb.rgb = mult_double_fvec3(v->amb.rgb, v->amb.ratio);
	c_free_void_array((void **)args);
	return (true);
}

bool	parse_light(t_mrt *v, char **args, int *o)
{
	(void)o;
	if (c_arraylen(args) != NB_LGT_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	if (!get_vector(c_split_func(args[1], &c_iscomma), &v->light.pos) \
		|| !get_double(args[2], &v->light.ratio, true) \
		|| !get_rgb(c_split_func(args[3], &c_iscomma), &v->light.rgb))
		return (error_clean_array("", args));
	if (v->light.ratio < 0.0 || v->light.ratio > 1.0)
		return (error_clean_array(ERR_RATIO, args));
	if (v->light.rgb.x != 1.0 || v->light.rgb.y != 1.0 || v->light.rgb.z != 1.0)
	{
		ft_putstr_fd(WARNING_LIGHT, 1);
		v->light.rgb = new_fvec3(1.0, 1.0, 1.0);
	}
	v->light.rgb = mult_double_fvec3(v->light.rgb, v->light.ratio);
	c_free_void_array((void **)args);
	return (true);
}
