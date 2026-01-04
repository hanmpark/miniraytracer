#include "mrt_render.h"

t_fvec3	color_cap(t_fvec3 color, int samples)
{
	// double	inv;

	// if (samples < 1)
	// 	samples = 1;
	// inv = 1.0 / (double)samples;
	// color.x = fmax(0.0, fmin(1.0, color.x * inv));
	// color.y = fmax(0.0, fmin(1.0, color.y * inv));
	// color.z = fmax(0.0, fmin(1.0, color.z * inv));
	(void)samples;
	color.x = fmax(0.0, fmin(1.0, color.x / SAMPLES_PER_PIXEL));
	color.y = fmax(0.0, fmin(1.0, color.y / SAMPLES_PER_PIXEL));
	color.z = fmax(0.0, fmin(1.0, color.z / SAMPLES_PER_PIXEL));
	return (color);
}

t_fvec3	color_to_byte(t_fvec3 color)
{
	color.x = round(color.x * 255);
	color.y = round(color.y * 255);
	color.z = round(color.z * 255);
	return (color);
}

t_fvec3	color_apply_checker(const t_fuv fuv_cpy)
{
	t_fvec3	checker_color;

	if ((int)(floor(fuv_cpy.u) + floor(fuv_cpy.v)) % 2 == 0)
	{
		checker_color.x = 0;
		checker_color.y = 0;
		checker_color.z = 0;
	}
	else
	{
		checker_color.x = 1;
		checker_color.y = 1;
		checker_color.z = 1;
	}
	return (checker_color);
}
