/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx_image_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:36:08 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 22:46:40 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render_bonus.h"

int	mrt_color_mlx(unsigned char t, unsigned char r, \
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

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
