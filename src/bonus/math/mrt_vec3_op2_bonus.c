/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_vec3_op2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:27:23 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/05 16:20:22 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math_bonus.h"

double	dot_fvec3(const t_fvec3 a_cpy, const t_fvec3 b_cpy)
{
	return (a_cpy.x * b_cpy.x + a_cpy.y * b_cpy.y + a_cpy.z * b_cpy.z);
}

t_fvec3	cross_fvec3(const t_fvec3 a_cpy, const t_fvec3 b_cpy)
{
	t_fvec3	o;

	o.x = a_cpy.y * b_cpy.z - a_cpy.z * b_cpy.y;
	o.y = a_cpy.z * b_cpy.x - a_cpy.x * b_cpy.z;
	o.z = a_cpy.x * b_cpy.y - a_cpy.y * b_cpy.x;
	return (o);
}

t_fvec3	mult_double_fvec3(t_fvec3 a_cpy, const double b)
{
	a_cpy.x *= b;
	a_cpy.y *= b;
	a_cpy.z *= b;
	return (a_cpy);
}

t_fvec3	mult_fvec3(t_fvec3 a_cpy, const t_fvec3 b_cpy)
{
	a_cpy.x *= b_cpy.x;
	a_cpy.y *= b_cpy.y;
	a_cpy.z *= b_cpy.z;
	return (a_cpy);
}

t_fvec3	mult_mat4x4_fvec3(const t_fvec3 i_cpy, const t_fmat4x4 m_ptr)
{
	t_fvec3	o;

	o.x = i_cpy.x * m_ptr[0][0] + i_cpy.y * m_ptr[0][1] + \
	i_cpy.z * m_ptr[0][2] + m_ptr[0][3];
	o.y = i_cpy.x * m_ptr[1][0] + i_cpy.y * m_ptr[1][1] + \
	i_cpy.z * m_ptr[1][2] + m_ptr[1][3];
	o.z = i_cpy.x * m_ptr[2][0] + i_cpy.y * m_ptr[2][1] + \
	i_cpy.z * m_ptr[2][2] + m_ptr[2][3];
	return (o);
}
