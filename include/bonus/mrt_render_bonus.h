/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:55:26 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 15:38:24 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_RENDER_BONUS_H
# define MRT_RENDER_BONUS_H

# include "mrt_bonus.h"
# include "mrt_math_bonus.h"
# include "mrt_objects_bonus.h"

/* DEFINE CHECKER SIZES */

# define SPHERE_CHECKER			8
# define SPH_CYLINDER_CHECKER	3
# define SPH_CONE_CHECKER		6

# define PLANE_CHECKER			1
# define PL_CYLINDER_CHECKER	3
# define PL_CONE_CHECKER		5

typedef enum e_intensity
{
	LIGHT,
	SPECULAR
}	t_intensity;

/* MLX */

int		event_keyboard(int keycode, t_mrt *v);
int		event_destroy(t_mrt *v);

void	mrt_mlx_put_pixel(t_mrt *v, int x, int y, int color);
void	mrt_mlx_refresh(t_mrt *v);
void	mrt_mlx_clear(t_mrt *v);

/* RAY TRACING */

void	*render(void *arg);
t_fvec3	raytracing_color(t_th *clu, t_ray incident_ray, t_hit hit);
double	light_intensity(t_mrt *v, t_light light, t_hit hit);
double	specular_intensity(t_mrt *v, t_light light, t_ray inc_ray, t_hit hit);

/* RAYS */

void	setup_camera_ray(t_mrt *v, t_ray *camray, double x, double y);
t_ray	ray_apply_matrix(t_ray ray_cpy, const t_fmat4x4 m_ptr);
t_ray	setup_light_ray(t_hit *hit, t_fvec3 lightdir);
bool	cast_light_ray(t_mrt *v, t_light light, t_ray lightray, t_hit hit);
bool	cast_reflection_ray(t_mrt *v, t_ray ray, t_hit *hit);

/* COLORS */

int		mrt_color_mlx(unsigned char t, unsigned char r, \
	unsigned char g, unsigned char b);
t_fvec3	color_cap(t_fvec3 color);
t_fvec3	color_to_byte(t_fvec3 color);
t_fvec3	color_apply_checker(const t_fuv fuv_cpy);

/* CHECKER TEXTURE */

void	compute_spheric_uv(t_hit *hit, t_fvec3 ray, t_type type);
void	compute_planar_uv(t_hit *hit, t_fvec3 ray, t_type type);

/* THREADS */

bool	init_threads(t_mrt *v);
int		render_threaded(t_mrt *v);

#endif