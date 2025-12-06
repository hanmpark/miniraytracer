#include "mrt_parsing.h"

bool	get_double(char *str, double *num, bool accept_negative)
{
	if (!c_isdouble(str))
		return (error_bool(ERR_DOUBLE));
	*num = c_atod(str);
	if (accept_negative == false)
	{
		if (*num < EPSILON_SCALE && *num > 0.0)
		{
			ft_putstr_fd(WARNING_SCALE, 1);
			*num = EPSILON_SCALE;
		}
		else if (*num < 0.0)
			return (error_bool(ERR_POS));
	}
	return (true);
}

bool	get_fov(char *str, int *fov)
{
	if (!c_strisdigit(str) || ft_strlen(str) > 3)
		return (error_bool(ERR_INT));
	*fov = ft_atoi(str);
	if (*fov < 0 || *fov > 180)
		return (error_bool(ERR_RANGE_FOV));
	return (true);
}

bool	get_vector(char **xyz, t_fvec3 *vec)
{
	if (!xyz)
		return (error_bool(ERR_ALLOC));
	else if (c_arraylen(xyz) != 3)
		return (error_clean_array(ERR_ARG, xyz));
	if (!get_double(xyz[0], &vec->x, true) \
		|| !get_double(xyz[1], &vec->y, true) \
		|| !get_double(xyz[2], &vec->z, true))
		return (error_clean_array("", xyz));
	c_free_void_array((void **)xyz);
	return (true);
}

bool	get_boolean(char *str, bool *setbool)
{
	int	num;

	if (!c_strisdigit(str) || ft_strlen(str) > 1)
		return (error_bool(ERR_BOOL));
	num = ft_atoi(str);
	if (num != 1 && num != 0)
		return (error_bool(ERR_BOOL));
	*setbool = (bool)num;
	return (true);
}

bool	check_norm(t_fvec3 *vec)
{
	double	len;

	if ((vec->x < -1.0 || vec->x > 1.0) \
		|| (vec->y < -1.0 || vec->y > 1.0) \
		|| (vec->z < -1.0 || vec->z > 1.0))
		return (error_bool(ERR_NORM));
	len = len_fvec3(*vec);
	if (len < EPSILON)
		return (error_bool(ERR_NORM));
	if (len < 0.999 || len > 1.001)
		return (error_bool(ERR_NORM));
	*vec = mult_double_fvec3(*vec, 1.0 / len);
	return (true);
}
