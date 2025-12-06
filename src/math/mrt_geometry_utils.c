/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_geometry_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:22:24 by hanmpark          #+#    #+#             */
/*   Updated: 2025/12/05 22:58:30 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math.h"
#include "mrt_render.h"

int	close_enough(double a, double b)
{
	return (fabs(a - b) < EPSILON);
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
