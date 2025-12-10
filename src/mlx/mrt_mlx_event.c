#include "mrt_render.h"
#include "mrt_parsing.h"

static t_fvec3 get_right(t_cam *cam)
{
	return (norm_fvec3(cross_fvec3(cam->align, cam->up)));
}

static void move_camera(t_mrt *v, double forward, double strafe)
{
	t_fvec3 right;

	if (!v->fast_mode || (forward == 0.0 && strafe == 0.0))
		return;
	right = get_right(&v->cam);
	v->cam.pos = add_fvec3(v->cam.pos,
						   mult_double_fvec3(v->cam.align, forward * MOVE_STEP));
	v->cam.pos = add_fvec3(v->cam.pos,
						   mult_double_fvec3(right, strafe * MOVE_STEP));
	set_cam_screen(&v->cam);
}

static void rotate_camera_keys(t_mrt *v, double dyaw, double dpitch)
{
	if (!v->fast_mode)
		return;
	v->cam.yaw += dyaw;
	v->cam.pitch += dpitch;
	if (v->cam.pitch > (PI / 2.0 - 0.01))
		v->cam.pitch = PI / 2.0 - 0.01;
	if (v->cam.pitch < -(PI / 2.0 - 0.01))
		v->cam.pitch = -(PI / 2.0 - 0.01);
	update_cam_orientation(&v->cam);
}

static void set_fast_mode(t_mrt *v, bool enabled)
{
	v->fast_mode = enabled;
	if (enabled)
	{
		v->pixel_step = PIXEL_STEP_FAST;
		v->max_ref_depth = 1;
		v->antialiasing = false;
	}
	else
	{
		v->pixel_step = PIXEL_STEP_DEFAULT;
		v->max_ref_depth = MAX_REF_DEPTH_DEFAULT;
		v->antialiasing = true;
	}
}

static int event_destroy(t_mrt *v)
{
	int i;

	pthread_mutex_lock(&v->secu_mutex);
	i = 0;
	while (i < NUM_THREADS)
	{
		v->threads[i].kill = true;
		i++;
		// printf("debug %d\n", i);
	}
	pthread_mutex_unlock(&v->secu_mutex);
	launch_render(v);
	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_join(v->threads[i].thread, NULL))
		{
			write(STDERR_FILENO, "pthread_join call fail event_destroy\n", 38);
			ft_putnbr_fd(i,STDERR_FILENO);
		}
		i++;
	}
	free(v->lights);
	free(v->objs);
	pthread_mutex_destroy(&v->secu_mutex);
	pthread_cond_destroy(&v->main_cond);
	pthread_cond_destroy(&v->threads_cond);
	mlx_destroy_image(v->mlx_ptr, v->mlx_img.img);
	mlx_destroy_window(v->mlx_ptr, v->mlx_win);
	free(v->mlx_ptr);
	exit(0);
}

static int event_keyboard(int keycode, t_mrt *v)
{
	double forward;
	double strafe;

	if (keycode == KEY_ESC)
		event_destroy(v);
	if (keycode == KEY_F)
	{
		set_fast_mode(v, !v->fast_mode);
		launch_render(v);
	}
	else if (v->fast_mode == true)
	{
		forward = 0.0;
		strafe = 0.0;
		if (keycode == KEY_W)
			forward = 1.0;
		else if (keycode == KEY_S)
			forward = -1.0;
		else if (keycode == KEY_D)
			strafe = 1.0;
		else if (keycode == KEY_A)
			strafe = -1.0;
		else if (keycode == KEY_SPACE)
		{
			move_camera(v, 0.0, 0.0);
			v->cam.pos.z += MOVE_STEP;
			set_cam_screen(&v->cam);
		}
		else if (keycode == KEY_CTRL)
		{
			move_camera(v, 0.0, 0.0);
			v->cam.pos.z -= MOVE_STEP;
			set_cam_screen(&v->cam);
		}
		if (forward != 0.0 || strafe != 0.0)
			move_camera(v, forward, strafe);
		else if (keycode == KEY_LEFT)
			rotate_camera_keys(v, -KEY_LOOK_STEP, 0.0);
		else if (keycode == KEY_RIGHT)
			rotate_camera_keys(v, KEY_LOOK_STEP, 0.0);
		else if (keycode == KEY_UP)
			rotate_camera_keys(v, 0.0, KEY_LOOK_STEP);
		else if (keycode == KEY_DOWN)
			rotate_camera_keys(v, 0.0, -KEY_LOOK_STEP);
		launch_render(v);
	}
	return (0);
}

static int event_expose(t_mrt *v)
{
	mrt_mlx_refresh(v);
	return (0);
}

void set_mrt_mlx_hook(t_mrt *v)
{
	launch_render(v);
	mlx_hook(v->mlx_win, 17, 0, &event_destroy, v);
	mlx_hook(v->mlx_win, 2, 1L << 0, event_keyboard, v);
	mlx_hook(v->mlx_win, 12, 1L << 15, event_expose, v);
	mlx_loop(v->mlx_ptr);
}
