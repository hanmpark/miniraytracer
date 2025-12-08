#include "mrt_math.h"

static bool	compute_det(\
	t_fmat4x4 m_out_ptr, const double inv[16],  union  u_fmat4x4and16 * m)
{
	int		x;
	int		y;
	double	det;

	det = m->mat16[0] * inv[0] + m->mat16[4] * inv[1] + m->mat16[8] * inv[2] + m->mat16[12] * inv[3];
	if (close_enough(det, 0.0))
		return (false);
	det = 1.0 / det;
	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			m_out_ptr[y][x] = inv[(4 * y) + x] * det;
		}
	}
	return (true);
}

static bool	compute_inv_end(\
	t_fmat4x4 m_out_ptr, double inv[16], union u_fmat4x4and16 * m)
{
	inv[10] = m->mat16[0] * m->mat16[5] * m->mat16[15] - m->mat16[0] * m->mat16[13] * m->mat16[7] - m->mat16[1] * m->mat16[4] * \
	m->mat16[15] + m->mat16[1] * m->mat16[12] * m->mat16[7] + m->mat16[3] * m->mat16[4] * m->mat16[13] - m->mat16[3] * m->mat16[12] * m->mat16[5];
	inv[11] = -m->mat16[0] * m->mat16[5] * m->mat16[11] + m->mat16[0] * m->mat16[9] * m->mat16[7] + m->mat16[1] * m->mat16[4] * \
	m->mat16[11] - m->mat16[1] * m->mat16[8] * m->mat16[7] - m->mat16[3] * m->mat16[4] * m->mat16[9] + m->mat16[3] * m->mat16[8] * m->mat16[5];
	inv[12] = -m->mat16[4] * m->mat16[9] * m->mat16[14] + m->mat16[4] * m->mat16[13] * m->mat16[10] + m->mat16[5] * m->mat16[8] * \
	m->mat16[14] - m->mat16[5] * m->mat16[12] * m->mat16[10] - m->mat16[6] * m->mat16[8] * m->mat16[13] + m->mat16[6] * m->mat16[12] * m->mat16[9];
	inv[13] = m->mat16[0] * m->mat16[9] * m->mat16[14] - m->mat16[0] * m->mat16[13] * m->mat16[10] - m->mat16[1] * m->mat16[8] * \
	m->mat16[14] + m->mat16[1] * m->mat16[12] * m->mat16[10] + m->mat16[2] * m->mat16[8] * m->mat16[13] - m->mat16[2] * m->mat16[12] * m->mat16[9];
	inv[14] = -m->mat16[0] * m->mat16[5] * m->mat16[14] + m->mat16[0] * m->mat16[13] * m->mat16[6] + m->mat16[1] * m->mat16[4] * \
	m->mat16[14] - m->mat16[1] * m->mat16[12] * m->mat16[6] - m->mat16[2] * m->mat16[4] * m->mat16[13] + m->mat16[2] * m->mat16[12] * m->mat16[5];
	inv[15] = m->mat16[0] * m->mat16[5] * m->mat16[10] - m->mat16[0] * m->mat16[9] * m->mat16[6] - m->mat16[1] * m->mat16[4] * \
	m->mat16[10] + m->mat16[1] * m->mat16[8] * m->mat16[6] + m->mat16[2] * m->mat16[4] * m->mat16[9] - m->mat16[2] * m->mat16[8] * m->mat16[5];
	return (compute_det(m_out_ptr, (const double *)inv, m));
}

static bool	compute_inv(t_fmat4x4 m_out_ptr, union	u_fmat4x4and16 * m)
{
	double	inv[16];

	inv[0] = m->mat16[5] * m->mat16[10] * m->mat16[15] - m->mat16[5] * m->mat16[14] * m->mat16[11] - m->mat16[6] * m->mat16[9] * \
	m->mat16[15] + m->mat16[6] * m->mat16[13] * m->mat16[11] + m->mat16[7] * m->mat16[9] * m->mat16[14] - m->mat16[7] * m->mat16[13] * m->mat16[10];
	inv[1] = -m->mat16[1] * m->mat16[10] * m->mat16[15] + m->mat16[1] * m->mat16[14] * m->mat16[11] + m->mat16[2] * m->mat16[9] * \
	m->mat16[15] - m->mat16[2] * m->mat16[13] * m->mat16[11] - m->mat16[3] * m->mat16[9] * m->mat16[14] + m->mat16[3] * m->mat16[13] * m->mat16[10];
	inv[2] = m->mat16[1] * m->mat16[6] * m->mat16[15] - m->mat16[1] * m->mat16[14] * m->mat16[7] - m->mat16[2] * m->mat16[5] * \
	m->mat16[15] + m->mat16[2] * m->mat16[13] * m->mat16[7] + m->mat16[3] * m->mat16[5] * m->mat16[14] - m->mat16[3] * m->mat16[13] * m->mat16[6];
	inv[3] = -m->mat16[1] * m->mat16[6] * m->mat16[11] + m->mat16[1] * m->mat16[10] * m->mat16[7] + m->mat16[2] * m->mat16[5] * \
	m->mat16[11] - m->mat16[2] * m->mat16[9] * m->mat16[7] - m->mat16[3] * m->mat16[5] * m->mat16[10] + m->mat16[3] * m->mat16[9] * m->mat16[6];
	inv[4] = -m->mat16[4] * m->mat16[10] * m->mat16[15] + m->mat16[4] * m->mat16[14] * m->mat16[11] + m->mat16[6] * m->mat16[8] * \
	m->mat16[15] - m->mat16[6] * m->mat16[12] * m->mat16[11] - m->mat16[7] * m->mat16[8] * m->mat16[14] + m->mat16[7] * m->mat16[12] * m->mat16[10];
	inv[5] = m->mat16[0] * m->mat16[10] * m->mat16[15] - m->mat16[0] * m->mat16[14] * m->mat16[11] - m->mat16[2] * m->mat16[8] * \
	m->mat16[15] + m->mat16[2] * m->mat16[12] * m->mat16[11] + m->mat16[3] * m->mat16[8] * m->mat16[14] - m->mat16[3] * m->mat16[12] * m->mat16[10];
	inv[6] = -m->mat16[0] * m->mat16[6] * m->mat16[15] + m->mat16[0] * m->mat16[14] * m->mat16[7] + m->mat16[2] * m->mat16[4] * \
	m->mat16[15] - m->mat16[2] * m->mat16[12] * m->mat16[7] - m->mat16[3] * m->mat16[4] * m->mat16[14] + m->mat16[3] * m->mat16[12] * m->mat16[6];
	inv[7] = m->mat16[0] * m->mat16[6] * m->mat16[11] - m->mat16[0] * m->mat16[10] * m->mat16[7] - m->mat16[2] * m->mat16[4] * \
	m->mat16[11] + m->mat16[2] * m->mat16[8] * m->mat16[7] + m->mat16[3] * m->mat16[4] * m->mat16[10] - m->mat16[3] * m->mat16[8] * m->mat16[6];
	inv[8] = m->mat16[4] * m->mat16[9] * m->mat16[15] - m->mat16[4] * m->mat16[13] * m->mat16[11] - m->mat16[5] * m->mat16[8] * \
	m->mat16[15] + m->mat16[5] * m->mat16[12] * m->mat16[11] + m->mat16[7] * m->mat16[8] * m->mat16[13] - m->mat16[7] * m->mat16[12] * m->mat16[9];
	inv[9] = -m->mat16[0] * m->mat16[9] * m->mat16[15] + m->mat16[0] * m->mat16[13] * m->mat16[11] + m->mat16[1] * m->mat16[8] * \
	m->mat16[15] - m->mat16[1] * m->mat16[12] * m->mat16[11] - m->mat16[3] * m->mat16[8] * m->mat16[13] + m->mat16[3] * m->mat16[12] * m->mat16[9];
	return (compute_inv_end(m_out_ptr, inv, m));
}

/*
 * internet version ¯\_0 ‿ 0_/¯
 * http://rodolphe-vaillant.fr/entry/7/c-code-for-4x4-matrix-inversion
 */
bool	inv_mat4x4(t_fmat4x4 m_out_ptr, const t_fmat4x4 m_ptr)
{

	union u_fmat4x4and16 * union_m_ptr = (union u_fmat4x4and16 *)m_ptr; 
	// double	m->mat16[16];
	// int		x;
	// int		y;

	// y = -1;
	// while (++y < 4)
	// {
	// 	x = -1;
	// 	while (++x < 4)
	// 	{
	// 		m->mat16[(4 * y) + x] = m_ptr[y][x];
	// 	}
	// }
	return (compute_inv(m_out_ptr, union_m_ptr));
}
