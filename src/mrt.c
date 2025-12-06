/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 06:27:15 by yobouhle          #+#    #+#             */
/*   Updated: 2025/12/05 23:01:01 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_error.h"
#include "mrt_parsing.h"
#include "mrt_render.h"

static void	init_settings(t_mrt *v)
{
	v->fast_mode = false;
	v->antialiasing = true;
	v->pixel_step = PIXEL_STEP_DEFAULT;
	v->max_ref_depth = MAX_REF_DEPTH_DEFAULT;
	v->mouse_tracking = false;
	v->last_mouse_x = 0;
	v->last_mouse_y = 0;
}

static bool	launch(t_mrt *v)
{
	if (!init_threads(v))
		return (false);
	if (!init_mrt_mlx(v))
		return (false);
	set_mrt_mlx_hook(v);
	return (true);
}

int	main(int ac, char **av)
{
	t_mrt	v;

	if (ac != 2)
	{
		ft_putstr_fd(ERR_USAGE, 2);
		return (1);
	}
	else if (mrt_parsing(&v, av[1]) == false)
		return (2);
	init_settings(&v);
	if (launch(&v) == false)
	{
		free(v.lights);
		free(v.objs);
		return (3);
	}
	return (0);
}
