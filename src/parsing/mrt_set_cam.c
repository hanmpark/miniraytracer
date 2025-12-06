#include "mrt_parsing.h"

static t_fvec3	get_cam_up(t_fvec3 align)
{
	t_fvec3	up;

	up = new_fvec3(0.0, 0.0, 1.0);
	if (fabs(dot_fvec3(align, up)) > 0.999)
		up = new_fvec3(0.0, 1.0, 0.0);
	return (up);
}

void	set_cam_screen(t_cam *cam)
{
	static const double	scr_ratio = (double)SCR_WID / (double)SCR_HGH;
	double				fov;

	fov = cam->fov * (PI / 180.0);
	cam->prj_u = mult_double_fvec3(\
						norm_fvec3(cross_fvec3(cam->align, cam->up)), \
						fov);
	cam->prj_v = mult_double_fvec3(\
						norm_fvec3(\
							cross_fvec3(cam->align, cam->prj_u)), \
						fov / scr_ratio);
	cam->prj_center = add_fvec3(cam->pos, cam->align);
}

void	update_cam_orientation(t_cam *cam)
{
	t_fvec3	dir;

	dir.x = sin(cam->yaw) * cos(cam->pitch);
	dir.y = cos(cam->yaw) * cos(cam->pitch);
	dir.z = sin(cam->pitch);
	cam->align = norm_fvec3(dir);
	cam->lookat = cam->align;
	cam->up = get_cam_up(cam->align);
	set_cam_screen(cam);
}

void	set_cam_data(t_cam *cam)
{
	cam->align = norm_fvec3(cam->lookat);
	cam->lookat = cam->align;
	cam->yaw = atan2(cam->align.x, cam->align.y);
	cam->pitch = asin(fmax(fmin(cam->align.z, 1.0), -1.0));
	cam->up = get_cam_up(cam->align);
	set_cam_screen(cam);
}
