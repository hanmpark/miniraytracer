/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mlx_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:48:04 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 16:48:25 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render.h"

/*
 * mrt_color_mlx
 * -------------
 * Packs RGBA color components into a single integer value suitable for use
 * with MiniLibX. The function takes individual 8-bit unsigned integers
 * for transparency (t), red (r), green (g), and blue (b) components
 * and combines them into a single 32-bit integer.
 */
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
