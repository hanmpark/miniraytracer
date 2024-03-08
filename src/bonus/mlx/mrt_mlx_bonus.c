/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:21:44 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/08 23:35:15 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_error_bonus.h"
#include "mrt_render_bonus.h"

static bool	free_launch(t_mrt *v, bool destroy_windows)
{
	if (destroy_windows == true)
		mlx_destroy_window(v->mlx_ptr, v->mlx_win);
	// mlx_destroy_window(v->mlx_ptr, v->mlx_win);
	free(v->mlx_ptr);
	return (error_bool(ERR_MLX));
}

bool	init_mrt_mlx(t_mrt *v)
{
	v->mlx_ptr = mlx_init();
	if (v->mlx_ptr == NULL)
		return (error_bool(ERR_MLX));
	v->mlx_win = mlx_new_window(v->mlx_ptr, SCR_WID, SCR_HGH, "minirt");
	if (v->mlx_win == NULL)
		return (free_launch(v, false));
	v->mlx_img.img = mlx_new_image(v->mlx_ptr, SCR_WID, SCR_HGH);
	if (v->mlx_img.img == NULL)
		return (free_launch(v, true));
	v->mlx_img.addr = mlx_get_data_addr(v->mlx_img.img, &v->mlx_img.bpp, \
		&v->mlx_img.ll, &v->mlx_img.ed);
	return (true);
}
