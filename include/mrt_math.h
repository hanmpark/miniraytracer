/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_math.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:23:12 by hanmpark          #+#    #+#             */
/*   Updated: 2025/12/05 23:03:09 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_MATH_H
# define MRT_MATH_H

# include <math.h>
# include <stdbool.h>

# define EPSILON		0.00001
# define PI				3.14159265358979323846
# define SHADOW_BIAS	0.001

typedef enum e_mat_enum
{
	FORWARD,
	BACKWARD,
	TRANSLATION,
	ROTX,
	ROTY,
	ROTZ,
	SCALE
}	t_mat_enum;

typedef struct t_fuv
{
	double	u;
	double	v;
}	t_fuv;

typedef struct s_fvec3
{
	double	x;
	double	y;
	double	z;
}	t_fvec3;

typedef double	t_fmat4x4[4][4];

typedef double	t_fmat3x3[3][3];

typedef struct s_ray
{
	t_fvec3	pos;
	t_fvec3	dir;
	t_fvec3	vec;
}	t_ray;

/* MATRIX 4x4 */

void	mult_mat4x4(t_fmat4x4 m_out_ptr, const t_fmat4x4 m_ptr);
bool	inv_mat4x4(t_fmat4x4 m_out_ptr, const t_fmat4x4 m_ptr);
void	identity_mat4x4(t_fmat4x4 m_ptr);
void	translation_mat4x4(t_fmat4x4 m_ptr, const t_fvec3 trans_cpy);
void	rot_x_mat4x4(t_fmat4x4 m_ptr, double x);
void	rot_y_mat4x4(t_fmat4x4 m_ptr, double y);
void	rot_z_mat4x4(t_fmat4x4 m_ptr, double z);
void	scale_mat4x4(t_fmat4x4 m_ptr, const t_fvec3 scale_cpy);

/* MATRIX 3x3 */

bool	inv_mat3x3(t_fmat3x3 inv, t_fmat3x3 m);
void	transpose_mat3x3(t_fmat3x3 src, t_fmat3x3 dest);
bool	extract_linear_mat3x3(t_fmat3x3 m, t_fmat4x4 m4);

/* VECTORS */

double	len_fvec3(const t_fvec3 a_cpy);
t_fvec3	norm_fvec3(t_fvec3 a_cpy);
t_fvec3	add_fvec3(t_fvec3 a_cpy, const t_fvec3 b_cpy);
t_fvec3	sub_fvec3(t_fvec3 a_cpy, const t_fvec3 b_cpy);
t_fvec3	mult_fvec3(t_fvec3 a_cpy, const t_fvec3 b_cpy);
double	dot_fvec3(const t_fvec3 a_cpy, const t_fvec3 b_cpy);
t_fvec3	cross_fvec3(const t_fvec3 a_cpy, const t_fvec3 b_cpy);
t_fvec3	mult_double_fvec3(t_fvec3 a_cpy, const double b);
t_fvec3	mult_mat4x4_fvec3(const t_fvec3 i_cpy, const t_fmat4x4 m_ptr);
t_fvec3	mult_mat3x3_fvec3(const t_fvec3 i_cpy, const t_fmat3x3 m_ptr);
t_fvec3	new_fvec3(double x, double y, double z);

/* UTILS */

int		close_enough(double a, double b);
double	solve_quadratic(double a, double b, double c, double ret);

#endif
