/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <yobouhle@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 22:20:58 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/05 19:41:50 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

int	event_keyboard(int keycode, t_mrt *v)
{
	if (keycode == XK_Escape)
		event_destroy(v);
	return (0);
}

int	event_destroy(t_mrt *v)
{
	free(v->objs);
	mlx_destroy_image(v->mlx_ptr, v->mlx_img.img);
	mlx_destroy_window(v->mlx_ptr, v->mlx_win);
	mlx_destroy_display(v->mlx_ptr);
	free(v->mlx_ptr);
	exit(0);
}
