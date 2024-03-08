/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <yobouhle@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:21:44 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/05 15:20:03 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

void	mrt_mlx_put_pixel(t_mrt *v, int x, int y, int color)
{
	char		*dst;
	const int	offset = (y * v->mlx_img.ll + x * (v->mlx_img.bpp / 8));

	dst = v->mlx_img.addr + offset;
	*(unsigned int *)dst = color;
}

void	mrt_mlx_refresh(t_mrt *v)
{
	mlx_put_image_to_window(v->mlx_ptr, v->mlx_win, v->mlx_img.img, 0, 0);
}

void	mrt_mlx_clear(t_mrt *v)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCR_HGH)
	{
		x = -1;
		while (++x < SCR_WID)
			mrt_mlx_put_pixel(v, x, y, 0x0);
	}
}
