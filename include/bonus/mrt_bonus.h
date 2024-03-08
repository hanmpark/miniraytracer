/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 06:27:19 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/08 14:23:54 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_BONUS_H
# define MRT_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <pthread.h>
# include <sys/time.h>

# include "libft.h"
# include "mlx.h"
# include "mrt_math_bonus.h"

/* PRINT COLORS */

# define DEF	"\033[0m"
# define BOLD	"\033[1m"
# define IT		"\033[3m"
# define RED	"\033[38;5;160m"

/* SCREEN PARAMETERS */

# define SCR_WID 			1920
# define SCR_HGH 			1080
# define MAX_REF_RAYS		50
# define NUM_THREADS		16

/* NOT MODIFIABLE SCREEN PARAMETER */

# define SAMPLES_PER_PIXEL	4

typedef struct s_amb
{
	double	ratio;
	t_fvec3	rgb;
}	t_amb;

typedef struct s_cam
{
	t_fvec3	pos;
	t_ray	ray;
	t_fvec3	lookat;
	int		fov;
	t_fvec3	up;

	t_fvec3	align;
	t_fvec3	prj_u;
	t_fvec3	prj_v;
	t_fvec3	prj_center;
}	t_cam;

typedef struct s_light
{
	t_fvec3	pos;
	t_fvec3	rgb;
	double	ratio;
}	t_light;

typedef struct s_obj
{
	int			type;
	t_fvec3		color;
	double		reflection;
	double		shininess;
	t_fmat4x4	fmat4x4[7];
	t_fmat3x3	lintfm;
	bool		is_checker;
}	t_obj;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		ed;
}	t_img;

typedef struct s_hit
{
	t_fvec3	pos;
	t_fvec3	normal;
	t_fuv	fuv;
	t_fvec3	close_pos;
	t_fvec3	close_normal;
	t_fuv	close_fuv;
	t_obj	*close_obj;
	double	min_dist;
}	t_hit;

typedef struct s_th
{
	struct s_mrt	*v;
	pthread_t		thread;
	t_ray			camray;
	int				count_ref_rays;
	int				start_y;
	int				end_y;
}	t_th;

typedef struct s_t
{
	struct timeval	start_time;
	struct timeval	end_time;
	time_t			seconds;
	time_t			microseconds;
}	t_t;

typedef struct s_mrt
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	mlx_img;

	t_amb	amb;
	t_cam	cam;
	t_light	*lights;
	int		nb_lights;

	t_obj	*objs;
	int		nb_objs;
	t_th	threads[NUM_THREADS];

	t_t		t;
}	t_mrt;

#endif