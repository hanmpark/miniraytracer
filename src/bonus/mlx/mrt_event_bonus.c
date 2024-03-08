/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_event_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:20:58 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/08 15:31:16 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render_bonus.h"

int	event_keyboard(int keycode, t_mrt *v)
{
	if (keycode == XK_Escape)
		event_destroy(v);
	return (0);
}

int	event_destroy(t_mrt *v)
{
	pthread_mutex_destroy(&v->count_mutex);
	free(v->lights);
	free(v->objs);
	mlx_destroy_image(v->mlx_ptr, v->mlx_img.img);
	mlx_destroy_window(v->mlx_ptr, v->mlx_win);
	mlx_destroy_display(v->mlx_ptr);
	free(v->mlx_ptr);
	exit(0);
}
