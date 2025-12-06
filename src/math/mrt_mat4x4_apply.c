#include "mrt_math.h"

void	translation_mat4x4(t_fmat4x4 m_ptr, const t_fvec3 trans_cpy)
{
	m_ptr[0][3] = trans_cpy.x;
	m_ptr[1][3] = trans_cpy.y;
	m_ptr[2][3] = trans_cpy.z;
}

void	rot_x_mat4x4(t_fmat4x4 m_ptr, double x)
{
	m_ptr[1][1] = cos(x);
	m_ptr[2][1] = sin(x);
	m_ptr[1][2] = -sin(x);
	m_ptr[2][2] = cos(x);
}

void	rot_y_mat4x4(t_fmat4x4 m_ptr, double y)
{
	m_ptr[0][0] = cos(y);
	m_ptr[2][0] = -sin(y);
	m_ptr[0][2] = sin(y);
	m_ptr[2][2] = cos(y);
}

void	rot_z_mat4x4(t_fmat4x4 m_ptr, double z)
{
	m_ptr[0][0] = cos(z);
	m_ptr[1][0] = sin(z);
	m_ptr[0][1] = -sin(z);
	m_ptr[1][1] = cos(z);
}

void	scale_mat4x4(t_fmat4x4 m_ptr, const t_fvec3 scale_cpy)
{
	m_ptr[0][0] = scale_cpy.x;
	m_ptr[1][1] = scale_cpy.y;
	m_ptr[2][2] = scale_cpy.z;
}
