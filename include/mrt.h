#ifndef MRT_H
# define MRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# include "libft.h"
# include "mlx.h"
# include "mrt_math.h"

/* ESC BUTTON */
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_F 3
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_SPACE 49
#  define KEY_CTRL 256
# elif defined __unix__
#  define KEY_ESC 65307
#  define KEY_F 102
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_SPACE 32
#  define KEY_CTRL 65507
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

/* PRINT COLORS */

# define DEF	"\033[0m"
# define BOLD	"\033[1m"
# define IT		"\033[3m"
# define RED	"\033[38;5;160m"

/* SCREEN PARAMETERS */

# define SCR_WID 			1920
# define SCR_HGH 			1080
# define NUM_THREADS		16
# define MAX_REF_DEPTH_DEFAULT	100
# define PIXEL_STEP_DEFAULT		1
# define PIXEL_STEP_FAST		32
# define MOVE_STEP				0.5
# define LOOK_SENSITIVITY		0.002
# define KEY_LOOK_STEP			0.05

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
	double	yaw;
	double	pitch;

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
	int				id;
	struct s_mrt	*v;
	pthread_t		thread;
	t_ray			camray;
	int				count_ref_rays;
}	t_th;

typedef struct s_mrt
{
	void			*mlx_ptr;
	void			*mlx_win;
	t_img			mlx_img;

	t_amb			amb;
	t_cam			cam;
	t_light			*lights;
	int				nb_lights;

	t_obj			*objs;
	int				nb_objs;
	t_th			threads[NUM_THREADS];
	size_t			finished_thread;
	pthread_mutex_t	count_mutex;
	bool			fast_mode;
	bool			antialiasing;
	int				pixel_step;
	int				max_ref_depth;
}	t_mrt;

#endif
