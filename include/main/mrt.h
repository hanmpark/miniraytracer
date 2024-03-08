/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 06:27:19 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/07 15:20:34 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_H
# define MRT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>

# include "libft.h"
# include "mlx.h"
# include "mrt_math.h"

/* PRINT COLORS */

# define DEF	"\033[0m"
# define BOLD	"\033[1m"
# define IT		"\033[3m"
# define RED	"\033[38;5;160m"

/* SCREEN PARAMETERS */

# define SCR_WID	800
# define SCR_HGH	800

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
	t_fmat4x4	fmat4x4[7];
	t_fmat3x3	lintfm;
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
	t_fvec3	close_pos;
	t_fvec3	close_normal;
	t_obj	*close_obj;
	double	min_dist;
}	t_hit;

typedef struct s_mrt
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	mlx_img;

	t_amb	amb;
	t_cam	cam;
	t_light	light;

	t_obj	*objs;
	int		nb_objs;
}	t_mrt;

#endif