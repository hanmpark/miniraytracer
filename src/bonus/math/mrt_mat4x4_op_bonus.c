/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_mat4x4_op_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:09:51 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/05 16:20:55 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_math_bonus.h"

void	mult_mat4x4(t_fmat4x4 m_out_ptr, const t_fmat4x4 m_ptr)
{
	t_fmat4x4	m_temp;
	int			x;
	int			y;
	int			z;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
			m_temp[y][x] = m_out_ptr[y][x];
	}
	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			m_out_ptr[y][x] = 0;
			z = -1;
			while (++z < 4)
				m_out_ptr[y][x] += m_temp[y][z] * m_ptr[z][x];
		}
	}
}

void	identity_mat4x4(t_fmat4x4 m_ptr)
{
	int	x;
	int	y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (x == y)
				m_ptr[y][x] = 1.0;
			else
				m_ptr[y][x] = 0.0;
			x++;
		}
		y++;
	}
}
