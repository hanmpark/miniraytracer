#include "mrt_math.h"

inline static bool can_compute_det(union u_fmat4x4and16 *u_m_out_ptr, const double inv[16], const union u_fmat4x4and16 *u_m_ptr)
{
	double det;
	int index_fill_out;

	det = u_m_ptr->mat16[0] * inv[0] + u_m_ptr->mat16[4] * inv[1] + u_m_ptr->mat16[8] * inv[2] + u_m_ptr->mat16[12] * inv[3];
	if (close_enough(det, 0.0))
		return (false);
	det = 1.0 / det;

	index_fill_out = 0;
	while (index_fill_out < 16)
	{
		u_m_out_ptr->mat16[index_fill_out] = inv[index_fill_out] * det;
		index_fill_out++;
	}
	return (true);
}

/*
 * internet version ¯\_0 ‿ 0_/¯
 * http://rodolphe-vaillant.fr/entry/7/c-code-for-4x4-matrix-inversion
 */
bool	inv_mat4x4(t_fmat4x4 m_out_ptr, const t_fmat4x4 m_ptr)
{
	union u_fmat4x4and16 *u_m_out_ptr = (union u_fmat4x4and16 *)m_out_ptr;
	const union u_fmat4x4and16 *u_m_ptr = (const union u_fmat4x4and16 *)m_ptr;
	double inv[16];

	inv[0] = u_m_ptr->mat16[5] * u_m_ptr->mat16[10] * u_m_ptr->mat16[15] - u_m_ptr->mat16[5] * u_m_ptr->mat16[14] * u_m_ptr->mat16[11] - u_m_ptr->mat16[6] * u_m_ptr->mat16[9] * u_m_ptr->mat16[15] + u_m_ptr->mat16[6] * u_m_ptr->mat16[13] * u_m_ptr->mat16[11] + u_m_ptr->mat16[7] * u_m_ptr->mat16[9] * u_m_ptr->mat16[14] - u_m_ptr->mat16[7] * u_m_ptr->mat16[13] * u_m_ptr->mat16[10];
	inv[1] = -u_m_ptr->mat16[1] * u_m_ptr->mat16[10] * u_m_ptr->mat16[15] + u_m_ptr->mat16[1] * u_m_ptr->mat16[14] * u_m_ptr->mat16[11] + u_m_ptr->mat16[2] * u_m_ptr->mat16[9] * u_m_ptr->mat16[15] - u_m_ptr->mat16[2] * u_m_ptr->mat16[13] * u_m_ptr->mat16[11] - u_m_ptr->mat16[3] * u_m_ptr->mat16[9] * u_m_ptr->mat16[14] + u_m_ptr->mat16[3] * u_m_ptr->mat16[13] * u_m_ptr->mat16[10];
	inv[2] = u_m_ptr->mat16[1] * u_m_ptr->mat16[6] * u_m_ptr->mat16[15] - u_m_ptr->mat16[1] * u_m_ptr->mat16[14] * u_m_ptr->mat16[7] - u_m_ptr->mat16[2] * u_m_ptr->mat16[5] * u_m_ptr->mat16[15] + u_m_ptr->mat16[2] * u_m_ptr->mat16[13] * u_m_ptr->mat16[7] + u_m_ptr->mat16[3] * u_m_ptr->mat16[5] * u_m_ptr->mat16[14] - u_m_ptr->mat16[3] * u_m_ptr->mat16[13] * u_m_ptr->mat16[6];
	inv[3] = -u_m_ptr->mat16[1] * u_m_ptr->mat16[6] * u_m_ptr->mat16[11] + u_m_ptr->mat16[1] * u_m_ptr->mat16[10] * u_m_ptr->mat16[7] + u_m_ptr->mat16[2] * u_m_ptr->mat16[5] * u_m_ptr->mat16[11] - u_m_ptr->mat16[2] * u_m_ptr->mat16[9] * u_m_ptr->mat16[7] - u_m_ptr->mat16[3] * u_m_ptr->mat16[5] * u_m_ptr->mat16[10] + u_m_ptr->mat16[3] * u_m_ptr->mat16[9] * u_m_ptr->mat16[6];
	inv[4] = -u_m_ptr->mat16[4] * u_m_ptr->mat16[10] * u_m_ptr->mat16[15] + u_m_ptr->mat16[4] * u_m_ptr->mat16[14] * u_m_ptr->mat16[11] + u_m_ptr->mat16[6] * u_m_ptr->mat16[8] * u_m_ptr->mat16[15] - u_m_ptr->mat16[6] * u_m_ptr->mat16[12] * u_m_ptr->mat16[11] - u_m_ptr->mat16[7] * u_m_ptr->mat16[8] * u_m_ptr->mat16[14] + u_m_ptr->mat16[7] * u_m_ptr->mat16[12] * u_m_ptr->mat16[10];
	inv[5] = u_m_ptr->mat16[0] * u_m_ptr->mat16[10] * u_m_ptr->mat16[15] - u_m_ptr->mat16[0] * u_m_ptr->mat16[14] * u_m_ptr->mat16[11] - u_m_ptr->mat16[2] * u_m_ptr->mat16[8] * u_m_ptr->mat16[15] + u_m_ptr->mat16[2] * u_m_ptr->mat16[12] * u_m_ptr->mat16[11] + u_m_ptr->mat16[3] * u_m_ptr->mat16[8] * u_m_ptr->mat16[14] - u_m_ptr->mat16[3] * u_m_ptr->mat16[12] * u_m_ptr->mat16[10];
	inv[6] = -u_m_ptr->mat16[0] * u_m_ptr->mat16[6] * u_m_ptr->mat16[15] + u_m_ptr->mat16[0] * u_m_ptr->mat16[14] * u_m_ptr->mat16[7] + u_m_ptr->mat16[2] * u_m_ptr->mat16[4] * u_m_ptr->mat16[15] - u_m_ptr->mat16[2] * u_m_ptr->mat16[12] * u_m_ptr->mat16[7] - u_m_ptr->mat16[3] * u_m_ptr->mat16[4] * u_m_ptr->mat16[14] + u_m_ptr->mat16[3] * u_m_ptr->mat16[12] * u_m_ptr->mat16[6];
	inv[7] = u_m_ptr->mat16[0] * u_m_ptr->mat16[6] * u_m_ptr->mat16[11] - u_m_ptr->mat16[0] * u_m_ptr->mat16[10] * u_m_ptr->mat16[7] - u_m_ptr->mat16[2] * u_m_ptr->mat16[4] * u_m_ptr->mat16[11] + u_m_ptr->mat16[2] * u_m_ptr->mat16[8] * u_m_ptr->mat16[7] + u_m_ptr->mat16[3] * u_m_ptr->mat16[4] * u_m_ptr->mat16[10] - u_m_ptr->mat16[3] * u_m_ptr->mat16[8] * u_m_ptr->mat16[6];
	inv[8] = u_m_ptr->mat16[4] * u_m_ptr->mat16[9] * u_m_ptr->mat16[15] - u_m_ptr->mat16[4] * u_m_ptr->mat16[13] * u_m_ptr->mat16[11] - u_m_ptr->mat16[5] * u_m_ptr->mat16[8] * u_m_ptr->mat16[15] + u_m_ptr->mat16[5] * u_m_ptr->mat16[12] * u_m_ptr->mat16[11] + u_m_ptr->mat16[7] * u_m_ptr->mat16[8] * u_m_ptr->mat16[13] - u_m_ptr->mat16[7] * u_m_ptr->mat16[12] * u_m_ptr->mat16[9];
	inv[9] = -u_m_ptr->mat16[0] * u_m_ptr->mat16[9] * u_m_ptr->mat16[15] + u_m_ptr->mat16[0] * u_m_ptr->mat16[13] * u_m_ptr->mat16[11] + u_m_ptr->mat16[1] * u_m_ptr->mat16[8] * u_m_ptr->mat16[15] - u_m_ptr->mat16[1] * u_m_ptr->mat16[12] * u_m_ptr->mat16[11] - u_m_ptr->mat16[3] * u_m_ptr->mat16[8] * u_m_ptr->mat16[13] + u_m_ptr->mat16[3] * u_m_ptr->mat16[12] * u_m_ptr->mat16[9];
	inv[10] = u_m_ptr->mat16[0] * u_m_ptr->mat16[5] * u_m_ptr->mat16[15] - u_m_ptr->mat16[0] * u_m_ptr->mat16[13] * u_m_ptr->mat16[7] - u_m_ptr->mat16[1] * u_m_ptr->mat16[4] * u_m_ptr->mat16[15] + u_m_ptr->mat16[1] * u_m_ptr->mat16[12] * u_m_ptr->mat16[7] + u_m_ptr->mat16[3] * u_m_ptr->mat16[4] * u_m_ptr->mat16[13] - u_m_ptr->mat16[3] * u_m_ptr->mat16[12] * u_m_ptr->mat16[5];
	inv[11] = -u_m_ptr->mat16[0] * u_m_ptr->mat16[5] * u_m_ptr->mat16[11] + u_m_ptr->mat16[0] * u_m_ptr->mat16[9] * u_m_ptr->mat16[7] + u_m_ptr->mat16[1] * u_m_ptr->mat16[4] * u_m_ptr->mat16[11] - u_m_ptr->mat16[1] * u_m_ptr->mat16[8] * u_m_ptr->mat16[7] - u_m_ptr->mat16[3] * u_m_ptr->mat16[4] * u_m_ptr->mat16[9] + u_m_ptr->mat16[3] * u_m_ptr->mat16[8] * u_m_ptr->mat16[5];
	inv[12] = -u_m_ptr->mat16[4] * u_m_ptr->mat16[9] * u_m_ptr->mat16[14] + u_m_ptr->mat16[4] * u_m_ptr->mat16[13] * u_m_ptr->mat16[10] + u_m_ptr->mat16[5] * u_m_ptr->mat16[8] * u_m_ptr->mat16[14] - u_m_ptr->mat16[5] * u_m_ptr->mat16[12] * u_m_ptr->mat16[10] - u_m_ptr->mat16[6] * u_m_ptr->mat16[8] * u_m_ptr->mat16[13] + u_m_ptr->mat16[6] * u_m_ptr->mat16[12] * u_m_ptr->mat16[9];
	inv[13] = u_m_ptr->mat16[0] * u_m_ptr->mat16[9] * u_m_ptr->mat16[14] - u_m_ptr->mat16[0] * u_m_ptr->mat16[13] * u_m_ptr->mat16[10] - u_m_ptr->mat16[1] * u_m_ptr->mat16[8] * u_m_ptr->mat16[14] + u_m_ptr->mat16[1] * u_m_ptr->mat16[12] * u_m_ptr->mat16[10] + u_m_ptr->mat16[2] * u_m_ptr->mat16[8] * u_m_ptr->mat16[13] - u_m_ptr->mat16[2] * u_m_ptr->mat16[12] * u_m_ptr->mat16[9];
	inv[14] = -u_m_ptr->mat16[0] * u_m_ptr->mat16[5] * u_m_ptr->mat16[14] + u_m_ptr->mat16[0] * u_m_ptr->mat16[13] * u_m_ptr->mat16[6] + u_m_ptr->mat16[1] * u_m_ptr->mat16[4] * u_m_ptr->mat16[14] - u_m_ptr->mat16[1] * u_m_ptr->mat16[12] * u_m_ptr->mat16[6] - u_m_ptr->mat16[2] * u_m_ptr->mat16[4] * u_m_ptr->mat16[13] + u_m_ptr->mat16[2] * u_m_ptr->mat16[12] * u_m_ptr->mat16[5];
	inv[15] = u_m_ptr->mat16[0] * u_m_ptr->mat16[5] * u_m_ptr->mat16[10] - u_m_ptr->mat16[0] * u_m_ptr->mat16[9] * u_m_ptr->mat16[6] - u_m_ptr->mat16[1] * u_m_ptr->mat16[4] * u_m_ptr->mat16[10] + u_m_ptr->mat16[1] * u_m_ptr->mat16[8] * u_m_ptr->mat16[6] + u_m_ptr->mat16[2] * u_m_ptr->mat16[4] * u_m_ptr->mat16[9] - u_m_ptr->mat16[2] * u_m_ptr->mat16[8] * u_m_ptr->mat16[5];

	return (can_compute_det(u_m_out_ptr, inv, u_m_ptr));
}
