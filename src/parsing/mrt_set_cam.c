#include "mrt_parsing.h"

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

void	set_cam_data(t_cam *cam)
{
	static bool first_render = false;
	t_fmat4x4	rotation_mat[3];

	// printf("here pos can %f %f %f\n", cam->pos.x, cam->pos.y, cam->pos.z);

	cam->up = new_fvec3(0.0, 0.0, 1.0);
	cam->align = new_fvec3(0.0, 1.0, 0.0);
	identity_mat4x4(rotation_mat[0]);
	identity_mat4x4(rotation_mat[1]);
	identity_mat4x4(rotation_mat[2]);
	if (first_render == false)
	{
		convert_radian(&cam->lookat, true);
		first_render = true;
	}
	rot_x_mat4x4(rotation_mat[0], cam->lookat.x);
	rot_y_mat4x4(rotation_mat[1], cam->lookat.y);
	rot_z_mat4x4(rotation_mat[2], cam->lookat.z);
	cam->align = mult_mat4x4_fvec3(cam->align, rotation_mat[0]);
	cam->up = mult_mat4x4_fvec3(cam->up, rotation_mat[1]);
	cam->align = mult_mat4x4_fvec3(cam->align, rotation_mat[2]);
}

