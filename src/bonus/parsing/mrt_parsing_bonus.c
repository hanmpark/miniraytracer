/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:06:54 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 15:04:20 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing_bonus.h"

static bool	verify_scene_objs(char **lines, int *nb_objs, int *nb_lights)
{
	t_count_caps	nb_cap;
	int				i;

	ft_bzero(&nb_cap, sizeof(t_count_caps));
	*nb_objs = 0;
	*nb_lights = 0;
	i = -1;
	while (lines && lines[++i])
	{
		nb_cap.a += *lines[i] == 'A';
		nb_cap.c += *lines[i] == 'C';
		*nb_lights += *lines[i] == 'L';
		*nb_objs += *lines[i] >= 'a' && *lines[i] <= 'z';
	}
	if (nb_cap.a != 1 || nb_cap.c != 1 || *nb_lights < 1)
		return (error_bool(ERR_CAP));
	if (*nb_objs == 0)
		return (error_bool(ERR_NB_OBJS));
	return (true);
}

bool	mrt_parsing(t_mrt *v, char *rt)
{
	char	**rt_scene;

	rt_scene = get_rt_scene(rt);
	if (!rt_scene)
		return (false);
	if (verify_scene_objs(rt_scene, &v->nb_objs, &v->nb_lights) == false)
		return (error_clean_array("", rt_scene));
	v->objs = malloc(sizeof(t_obj) * v->nb_objs);
	if (!v->objs)
		return (error_clean_array(ERR_ALLOC, rt_scene));
	v->lights = malloc(sizeof(t_light) * v->nb_lights);
	if (!v->lights)
	{
		free(v->objs);
		return (error_clean_array(ERR_ALLOC, rt_scene));
	}
	else if (read_rt_scene(v, rt_scene) == false)
	{
		free(v->lights);
		free(v->objs);
		return (false);
	}
	return (true);
}
