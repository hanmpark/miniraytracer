/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mat3x3_inv_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:57:01 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/05 18:17:47 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math_bonus.h"

static double	det_mat3x3(t_fmat3x3 m)
{
	double	det;

	det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) \
		- m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) \
		+ m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	return (det);
}

static void	cofactor_mat3x3(t_fmat3x3 m, t_fmat3x3 cof)
{
	cof[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]);
	cof[0][1] = -(m[0][1] * m[2][2] - m[0][2] * m[2][1]);
	cof[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
	cof[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]);
	cof[1][1] = (m[0][0] * m[2][2] - m[2][0] * m[0][2]);
	cof[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);
	cof[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
	cof[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);
	cof[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]);
}

bool	inv_mat3x3(t_fmat3x3 inv, t_fmat3x3 m)
{
	t_fmat3x3	cof;
	t_fmat3x3	adj;
	double		det;
	int			i;
	int			j;

	det = det_mat3x3(m);
	if (close_enough(det, 0.0))
		return (false);
	cofactor_mat3x3(m, cof);
	transpose_mat3x3(cof, adj);
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			inv[i][j] = adj[i][j] / det;
	}
	return (true);
}
