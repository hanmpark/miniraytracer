/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_vec3_op1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:09:48 by yobouhle          #+#    #+#             */
/*   Updated: 2025/12/05 22:58:08 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math.h"

double	len_fvec3(const t_fvec3 a_cpy)
{
	return (sqrt(a_cpy.x * a_cpy.x + a_cpy.y * a_cpy.y + a_cpy.z * a_cpy.z));
}

t_fvec3	norm_fvec3(t_fvec3 a_cpy)
{
	double	w;

	w = len_fvec3(a_cpy);
	if (close_enough(w, 0.0) == 0)
	{
		a_cpy.x /= w;
		a_cpy.y /= w;
		a_cpy.z /= w;
	}
	return (a_cpy);
}

t_fvec3	add_fvec3(t_fvec3 a_cpy, const t_fvec3 b_cpy)
{
	a_cpy.x += b_cpy.x;
	a_cpy.y += b_cpy.y;
	a_cpy.z += b_cpy.z;
	return (a_cpy);
}

t_fvec3	sub_fvec3(t_fvec3 a_cpy, const t_fvec3 b_cpy)
{
	a_cpy.x -= b_cpy.x;
	a_cpy.y -= b_cpy.y;
	a_cpy.z -= b_cpy.z;
	return (a_cpy);
}

t_fvec3	new_fvec3(double x, double y, double z)
{
	t_fvec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
