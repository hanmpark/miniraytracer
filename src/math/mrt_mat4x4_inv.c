#include "mrt_math.h"

static bool	compute_det(\
	t_fmat4x4 m_out_ptr, const double inv[16], const double m[16])
{
	int		x;
	int		y;
	double	det;

	det = m[0] * inv[0] + m[4] * inv[1] + m[8] * inv[2] + m[12] * inv[3];
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
	t_fmat4x4 m_out_ptr, double inv[16], const double m[16])
{
	inv[10] = m[0] * m[5] * m[15] - m[0] * m[13] * m[7] - m[1] * m[4] * \
	m[15] + m[1] * m[12] * m[7] + m[3] * m[4] * m[13] - m[3] * m[12] * m[5];
	inv[11] = -m[0] * m[5] * m[11] + m[0] * m[9] * m[7] + m[1] * m[4] * \
	m[11] - m[1] * m[8] * m[7] - m[3] * m[4] * m[9] + m[3] * m[8] * m[5];
	inv[12] = -m[4] * m[9] * m[14] + m[4] * m[13] * m[10] + m[5] * m[8] * \
	m[14] - m[5] * m[12] * m[10] - m[6] * m[8] * m[13] + m[6] * m[12] * m[9];
	inv[13] = m[0] * m[9] * m[14] - m[0] * m[13] * m[10] - m[1] * m[8] * \
	m[14] + m[1] * m[12] * m[10] + m[2] * m[8] * m[13] - m[2] * m[12] * m[9];
	inv[14] = -m[0] * m[5] * m[14] + m[0] * m[13] * m[6] + m[1] * m[4] * \
	m[14] - m[1] * m[12] * m[6] - m[2] * m[4] * m[13] + m[2] * m[12] * m[5];
	inv[15] = m[0] * m[5] * m[10] - m[0] * m[9] * m[6] - m[1] * m[4] * \
	m[10] + m[1] * m[8] * m[6] + m[2] * m[4] * m[9] - m[2] * m[8] * m[5];
	return (compute_det(m_out_ptr, (const double *)inv, m));
}

static bool	compute_inv(t_fmat4x4 m_out_ptr, const double m[16])
{
	double	inv[16];

	inv[0] = m[5] * m[10] * m[15] - m[5] * m[14] * m[11] - m[6] * m[9] * \
	m[15] + m[6] * m[13] * m[11] + m[7] * m[9] * m[14] - m[7] * m[13] * m[10];
	inv[1] = -m[1] * m[10] * m[15] + m[1] * m[14] * m[11] + m[2] * m[9] * \
	m[15] - m[2] * m[13] * m[11] - m[3] * m[9] * m[14] + m[3] * m[13] * m[10];
	inv[2] = m[1] * m[6] * m[15] - m[1] * m[14] * m[7] - m[2] * m[5] * \
	m[15] + m[2] * m[13] * m[7] + m[3] * m[5] * m[14] - m[3] * m[13] * m[6];
	inv[3] = -m[1] * m[6] * m[11] + m[1] * m[10] * m[7] + m[2] * m[5] * \
	m[11] - m[2] * m[9] * m[7] - m[3] * m[5] * m[10] + m[3] * m[9] * m[6];
	inv[4] = -m[4] * m[10] * m[15] + m[4] * m[14] * m[11] + m[6] * m[8] * \
	m[15] - m[6] * m[12] * m[11] - m[7] * m[8] * m[14] + m[7] * m[12] * m[10];
	inv[5] = m[0] * m[10] * m[15] - m[0] * m[14] * m[11] - m[2] * m[8] * \
	m[15] + m[2] * m[12] * m[11] + m[3] * m[8] * m[14] - m[3] * m[12] * m[10];
	inv[6] = -m[0] * m[6] * m[15] + m[0] * m[14] * m[7] + m[2] * m[4] * \
	m[15] - m[2] * m[12] * m[7] - m[3] * m[4] * m[14] + m[3] * m[12] * m[6];
	inv[7] = m[0] * m[6] * m[11] - m[0] * m[10] * m[7] - m[2] * m[4] * \
	m[11] + m[2] * m[8] * m[7] + m[3] * m[4] * m[10] - m[3] * m[8] * m[6];
	inv[8] = m[4] * m[9] * m[15] - m[4] * m[13] * m[11] - m[5] * m[8] * \
	m[15] + m[5] * m[12] * m[11] + m[7] * m[8] * m[13] - m[7] * m[12] * m[9];
	inv[9] = -m[0] * m[9] * m[15] + m[0] * m[13] * m[11] + m[1] * m[8] * \
	m[15] - m[1] * m[12] * m[11] - m[3] * m[8] * m[13] + m[3] * m[12] * m[9];
	return (compute_inv_end(m_out_ptr, inv, m));
}

/*
 * internet version ¯\_0 ‿ 0_/¯
 * http://rodolphe-vaillant.fr/entry/7/c-code-for-4x4-matrix-inversion
 */
bool	inv_mat4x4(t_fmat4x4 m_out_ptr, const t_fmat4x4 m_ptr)
{
	double	m[16];
	int		x;
	int		y;

	y = -1;
	while (++y < 4)
	{
		x = -1;
		while (++x < 4)
		{
			m[(4 * y) + x] = m_ptr[y][x];
		}
	}
	return (compute_inv(m_out_ptr, (const double *)m));
}
