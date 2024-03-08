/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx_event_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:20:58 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/09 00:18:04 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render_bonus.h"

static int	event_destroy(t_mrt *v)
{
	free(v->lights);
	free(v->objs);
	mlx_destroy_image(v->mlx_ptr, v->mlx_img.img);
	mlx_destroy_window(v->mlx_ptr, v->mlx_win);
	free(v->mlx_ptr);
	exit(0);
}

static int	event_keyboard(int keycode, t_mrt *v)
{
	if (keycode == KEY_ESC)
		event_destroy(v);
	return (0);
}

void	set_mrt_mlx_hook(t_mrt *v)
{
	render_threaded(v);
	mlx_hook(v->mlx_win, 17, 0, &event_destroy, v);
	mlx_key_hook(v->mlx_win, event_keyboard, (void *)v);
	mlx_loop(v->mlx_ptr);
}
