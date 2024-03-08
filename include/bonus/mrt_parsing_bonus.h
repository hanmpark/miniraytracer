/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parsing_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:55:23 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 16:25:49 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_PARSING_BONUS_H
# define MRT_PARSING_BONUS_H

# include "mrt_bonus.h"
# include "mrt_error_bonus.h"
# include "mrt_objects_bonus.h"

/* ARGUMENTS NUMBER */

# define ELEMENTS_MAX	7

# define NB_AMB_ARGS	3
# define NB_CAM_ARGS	4
# define NB_LGT_ARGS	4

# define NB_SPH_ARGS	7
# define NB_PLA_ARGS	7
# define NB_REV_ARGS	9

# define NB_RGB_ARGS	3

# define EPSILON_SCALE	0.05
# define WARNING_SCALE	"WARNING : diameter/height have been round up to 0.05\n"

typedef struct s_count_caps
{
	int	a;
	int	c;
}	t_count_caps;

typedef bool	(*t_func)(t_mrt *v, char **args, int *o, int *l);

typedef struct s_obj_spc
{
	char	*id;
	t_func	ft;
}	t_obj_spc;

bool	mrt_parsing(t_mrt *v, char *rt);

/* GET AND READ RT FILE */

char	**get_rt_scene(char *filename);
bool	read_rt_scene(t_mrt *obj, char **rt);

/* PARAMETERS */

bool	parse_amb(t_mrt *v, char **args, int *o, int *l);
bool	parse_cam(t_mrt *v, char **args, int *o, int *l);
void	set_cam_data(t_cam *cam);
void	set_cam_screen(t_cam *cam);
bool	parse_light(t_mrt *v, char **args, int *o, int *l);

/* OBJECTS */

bool	parse_sphere(t_mrt *v, char **args, int *o, int *l);
bool	parse_plane(t_mrt *v, char **args, int *o, int *l);
bool	parse_cylinder(t_mrt *v, char **args, int *o, int *l);
bool	parse_cone(t_mrt *v, char **args, int *o, int *l);
bool	set_sphere_data(t_obj *sphere, char **args);
bool	set_plane_data(t_obj *plane, char **args);
bool	set_revolution_data(t_obj *cylinder, char **args);

/* DATA */

bool	get_rgb(char **rgb_str, t_fvec3 *rgb);
bool	get_double(char *str, double *num, bool accept_negative);
bool	get_fov(char *str, int *fov);
bool	get_vector(char **xyz, t_fvec3 *vec);
bool	get_boolean(char *str, bool *setbool);
bool	check_norm(t_fvec3 vec);

#endif