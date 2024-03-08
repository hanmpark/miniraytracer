/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_param_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:41:26 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 16:16:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing_bonus.h"

bool	parse_cam(t_mrt *v, char **args, int *o, int *l)
{
	(void)o;
	(void)l;
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

bool	parse_amb(t_mrt *v, char **args, int *o, int *l)
{
	(void)o;
	(void)l;
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

bool	parse_light(t_mrt *v, char **args, int *o, int *l)
{
	(void)o;
	if (c_arraylen(args) != NB_LGT_ARGS)
		return (error_clean_array(ERR_NBR_ARGS, args));
	if (!get_vector(c_split_func(args[1], &c_iscomma), &v->lights[*l].pos) \
		|| !get_double(args[2], &v->lights[*l].ratio, true) \
		|| !get_rgb(c_split_func(args[3], &c_iscomma), &v->lights[*l].rgb))
		return (error_clean_array("", args));
	if (v->lights[*l].ratio < 0.0 || v->lights[*l].ratio > 1.0)
		return (error_clean_array(ERR_RATIO, args));
	v->lights[*l].rgb = mult_double_fvec3(v->lights[*l].rgb, \
		v->lights[*l].ratio);
	c_free_void_array((void **)args);
	(*l)++;
	return (true);
}
