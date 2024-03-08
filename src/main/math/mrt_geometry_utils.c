/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_geometry_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:22:24 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 11:33:26 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math.h"
#include "mrt_render.h"

int	close_enough(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

void	convert_radian(t_fvec3 *rot, bool is_cam)
{
	if (is_cam == true)
	{
		if (rot->x < 0.0 && close_enough(rot->x, -0.5))
			rot->x += 0.01;
		if (rot->y < 0.0 && close_enough(rot->y, -0.5))
			rot->y += 0.01;
		if (rot->z < 0.0 && close_enough(rot->z, -0.5))
			rot->z += 0.01;
		if (rot->x >= 0.0 && close_enough(rot->x, 0.5))
			rot->x -= 0.01;
		if (rot->y >= 0.0 && close_enough(rot->y, 0.5))
			rot->y -= 0.01;
		if (rot->z >= 0.0 && close_enough(rot->z, 0.5))
			rot->z -= 0.01;
	}
	rot->x *= M_PI;
	rot->y *= M_PI;
	rot->z *= M_PI;
}

double	solve_quadratic(double a, double b, double c, double ret)
{
	double	det;
	double	root1;
	double	root2;

	det = pow(b, 2.0) - (4.0 * a * c);
	if (det < 0.0)
		return (ret);
	det = sqrt(det);
	root1 = (-b + det) / (2.0 * a);
	root2 = (-b - det) / (2.0 * a);
	if (root1 > 0.0 && root1 < root2)
		return (root1);
	else if (root2 > 0.0)
		return (root2);
	return (ret);
}
