/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_get_data2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:31:01 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 10:11:12 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_parsing_bonus.h"

static bool	get_color(char *str, double *color)
{
	if (!c_strisdigit(str))
		return (error_bool(ERR_STRDIGIT));
	if (ft_strlen(str) > 3 || ft_atoi(str) < 0 || ft_atoi(str) > 255)
		return (error_bool(ERR_RANGE_COLORS));
	*color = (double)ft_atoi(str) / 255.0;
	return (true);
}

bool	get_rgb(char **rgb_str, t_fvec3 *rgb)
{
	if (!rgb_str)
		return (error_bool(ERR_ALLOC));
	if (c_arraylen(rgb_str) != NB_RGB_ARGS)
		return (error_clean_array(ERR_ARG, rgb_str));
	if (!get_color(rgb_str[0], &rgb->x) \
		|| !get_color(rgb_str[1], &rgb->y) \
		|| !get_color(rgb_str[2], &rgb->z))
		return (error_clean_array("", rgb_str));
	c_free_void_array((void **)rgb_str);
	return (true);
}
