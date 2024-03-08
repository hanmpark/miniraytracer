/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:55:26 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/06 23:43:08 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_RENDER_H
# define MRT_RENDER_H

# include "mrt.h"
# include "mrt_math.h"
# include "mrt_objects.h"

/* MLX */

int		event_keyboard(int keycode, t_mrt *v);
int		event_destroy(t_mrt *v);

void	mrt_mlx_put_pixel(t_mrt *v, int x, int y, int color);
void	mrt_mlx_refresh(t_mrt *v);
void	mrt_mlx_clear(t_mrt *v);

/* RAY TRACING */

int		render_screen(t_mrt *v);
t_fvec3	raytracing(t_mrt *v, t_hit hit);

/* RAYS */

void	setup_camera_ray(t_mrt *v, double x, double y);
t_ray	ray_apply_matrix(t_ray ray_cpy, const t_fmat4x4 m_ptr);
t_ray	setup_light_ray(t_fvec3 lightdir, t_hit *hit);
bool	cast_light_ray(t_mrt *v, t_ray lightray, t_hit hit);

/* COLORS*/

int		mrt_color_mlx(unsigned char t, unsigned char r, \
	unsigned char g, unsigned char b);
t_fvec3	color_cap(t_fvec3 color);
t_fvec3	color_to_byte(t_fvec3 color);

#endif