/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_scene_read_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:25:56 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 10:01:34 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing_bonus.h"

static bool	check_double_comma(char *rt_obj)
{
	bool	comma;
	int		i;

	comma = false;
	i = 0;
	while (rt_obj[i])
	{
		if (rt_obj[i] == ',')
		{
			if (comma)
				return (error_bool(ERR_COMMA));
			comma = true;
		}
		else if (comma)
			comma = false;
		i++;
	}
	return (true);
}

static bool	dispatch_obj(t_mrt *v, char **rt_obj, int *o, int *l)
{
	static const t_obj_spc	obj_spc[] = {
	{"A", &parse_amb}, {"C", &parse_cam}, {"L", &parse_light},
	{"sp", &parse_sphere}, {"pl", &parse_plane}, {"cy", &parse_cylinder},
	{"co", &parse_cone}
	};
	int						i;

	if (!rt_obj)
		return (error_bool(ERR_ALLOC));
	i = -1;
	while (++i < ELEMENTS_MAX)
		if (!c_strcmp(*rt_obj, obj_spc[i].id))
			return (obj_spc[i].ft(v, rt_obj, o, l));
	return (error_clean_array(ERR_UNDEFINED, rt_obj));
}

bool	read_rt_scene(t_mrt *v, char **rt)
{
	int		i;
	int		obj_index;
	int		lights_index;

	i = -1;
	obj_index = 0;
	lights_index = 0;
	while (rt[++i])
	{
		if (*rt[i] == '#')
			continue ;
		else if (!check_double_comma(rt[i]) \
			|| !dispatch_obj(v, c_split_func(rt[i], &c_isspace), \
				&obj_index, &lights_index))
		{
			error_putline(rt[i]);
			return (error_clean_array("", rt));
		}
	}
	c_free_void_array((void **)rt);
	return (true);
}
