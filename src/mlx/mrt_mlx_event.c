#include "mrt_render.h"
#include "mrt_parsing.h"


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
	}
	pthread_mutex_unlock(&v->secu_mutex);
	launch_render(v);
	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_join(v->threads[i].thread, NULL))
		{
			if (write(STDERR_FILENO, \
					"pthread_join call fail event_destroy\n", 38) == -1)
				perror("write");
			ft_putnbr_fd(i, STDERR_FILENO);
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
	if (keycode == KEY_ESC)
	{
		event_destroy(v);
	}
	else if (keycode == KEY_F)
	{
		set_fast_mode(v, !v->fast_mode);
		launch_render(v);
	}
	else if (v->fast_mode == true)
	{
		t_fvec3	forward;
		t_fvec3	right;
		t_fvec3	world_up;

		forward = norm_fvec3(v->cam.align);
		forward.z = 0.0;
		if (len_fvec3(forward) < EPSILON)
			forward = norm_fvec3(v->cam.align);
		else
			forward = norm_fvec3(forward);
		world_up = new_fvec3(0.0, 0.0, 1.0);
		right = norm_fvec3(cross_fvec3(forward, world_up));
		if (keycode == KEY_W)
			v->cam.pos = add_fvec3(v->cam.pos, \
				mult_double_fvec3(forward, MOVE_STEP));
		else if (keycode == KEY_S)
			v->cam.pos = sub_fvec3(v->cam.pos, \
				mult_double_fvec3(forward, MOVE_STEP));
		else if (keycode == KEY_D)
			v->cam.pos = add_fvec3(v->cam.pos, \
				mult_double_fvec3(right, MOVE_STEP));
		else if (keycode == KEY_A)
			v->cam.pos = sub_fvec3(v->cam.pos, \
				mult_double_fvec3(right, MOVE_STEP));
		else if (keycode == KEY_SPACE)
			v->cam.pos.z += MOVE_STEP;
		else if (keycode == KEY_CTRL)
			v->cam.pos.z -= MOVE_STEP;
		else if (keycode == KEY_Q)
			v->cam.lookat.y -= KEY_LOOK_STEP;
		else if (keycode == KEY_E)
			v->cam.lookat.y += KEY_LOOK_STEP;

		else if (keycode == KEY_LEFT)
			v->cam.lookat.z += KEY_LOOK_STEP;
		else if (keycode == KEY_RIGHT)
			v->cam.lookat.z -= KEY_LOOK_STEP;
		else if (keycode == KEY_UP)
			v->cam.lookat.x += KEY_LOOK_STEP;
		else if (keycode == KEY_DOWN)
			v->cam.lookat.x -= KEY_LOOK_STEP;
		else
			return (0);
		
		printf("pos can %f %f %f\n", v->cam.pos.x, v->cam.pos.y, v->cam.pos.z);
		set_cam_data(&v->cam);
		set_cam_screen(&v->cam);
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
