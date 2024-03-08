/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mat3x3_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:39:06 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/06 19:52:55 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math.h"

t_fvec3	mult_mat3x3_fvec3(const t_fvec3 i_cpy, const t_fmat3x3 m_ptr)
{
	t_fvec3	o;

	o.x = i_cpy.x * m_ptr[0][0] + i_cpy.y * m_ptr[0][1] + i_cpy.z * m_ptr[0][2];
	o.y = i_cpy.x * m_ptr[1][0] + i_cpy.y * m_ptr[1][1] + i_cpy.z * m_ptr[1][2];
	o.z = i_cpy.x * m_ptr[2][0] + i_cpy.y * m_ptr[2][1] + i_cpy.z * m_ptr[2][2];
	return (o);
}

void	transpose_mat3x3(t_fmat3x3 src, t_fmat3x3 dest)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			dest[i][j] = src[j][i];
	}
}

static void	copy_mat3x3(t_fmat3x3 m, t_fmat3x3 m_cpy)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			m[i][j] = m_cpy[i][j];
	}
}

bool	extract_linear_mat3x3(t_fmat3x3 m, t_fmat4x4 m4)
{
	t_fmat3x3	linear_part_m4x4;
	t_fmat3x3	new_m;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			linear_part_m4x4[i][j] = m4[j][i];
	}
	if (!inv_mat3x3(m, linear_part_m4x4))
		return (false);
	copy_mat3x3(new_m, m);
	transpose_mat3x3(new_m, m);
	return (true);
}
