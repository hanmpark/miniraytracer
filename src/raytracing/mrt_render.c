#include "mrt_render.h"

static t_fvec3	pixel_color(t_th *clu, t_ray camray)
{
	t_fvec3	color;
	t_hit	hit;
	int		i;

	color = new_fvec3(0.0, 0.0, 0.0);
	hit.min_dist = INFINITY;
	i = 0;
	while (i < clu->v->nb_objs)
	{
		if (hit_object(&clu->v->objs[i], camray, &hit))
			color = raytracing_color(clu, camray, hit);
		i++;
	}
	return (color);
}

static t_fvec3	sample_pixel(t_th *clu, double x, double y)
{
	clu->count_ref_rays = 0;
	setup_camera_ray(clu->v, &clu->camray, x, y);
	return (pixel_color(clu, clu->camray));
}

static t_fvec3	render_pixel(t_th *clu, double x, double y)
{
	const double	offs[2] = {-0.25, 0.25};
	t_fvec3			col;
	int				i;
	int				j;

	col = new_fvec3(0.0, 0.0, 0.0);
	if (!clu->v->antialiasing)
		return (sample_pixel(clu, x, y));
	i = -1;
	while (++i < 2)
	{
		j = -1;
		while (++j < 2)
			col = add_fvec3(col, sample_pixel(clu, x + offs[i], y + offs[j]));
	}
	return (col);
}

static void	fill_block(t_mrt *v, int x, int y, int step, int color)
{
	int	xx;
	int	yy;

	yy = y;
	while (yy < y + step && yy < SCR_HGH)
	{
		xx = x;
		while (xx < x + step && xx < SCR_WID)
		{
			mrt_mlx_put_pixel(v, xx, yy, color);
			xx++;
		}
		yy++;
	}
}

void	*thread_render(void *arg)
{
	t_th	*clu;
	int		step;
	int		x;
	int		y;
	int		color;
	t_fvec3	col;
	double	sample_x;
	double	sample_y;

	clu = (t_th *)arg;
	while ("Yippie")
	{
		pthread_mutex_lock(&clu->v->secu_mutex);
		while (clu->v->launch_multithread == false || clu->launch_thread == false)
			pthread_cond_wait(&clu->v->threads_cond, &clu->v->secu_mutex);
		if (clu->kill == true)
		{
			clu->v->killed_thread++;
			if (clu->v->killed_thread == NUM_THREADS)
			{
				clu->v->launch_multithread = false;
				pthread_cond_signal(&clu->v->main_cond);
			}
			// printf("pass %d\n", clu->id);
			pthread_mutex_unlock(&clu->v->secu_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&clu->v->secu_mutex);

		step = clu->v->pixel_step;
		y = clu->id * step;
		while (y < SCR_HGH)
		{
			x = 0;
			while (x < SCR_WID)
			{
				sample_x = x + (step > 1 ? (step >> 1) : 0);
				sample_y = y + (step > 1 ? (step / 2.0) : 0);
				if (sample_x >= SCR_WID)
					sample_x = SCR_WID - 1;
				if (sample_y >= SCR_HGH)
					sample_y = SCR_HGH - 1;
				col = render_pixel(clu, sample_x, sample_y);
				col = color_to_byte(color_cap(col,
											  clu->v->antialiasing ? SAMPLES_PER_PIXEL : 1));
				color = mrt_color_mlx(0, col.x, col.y, col.z);
				fill_block(clu->v, x, y, step, color);
				x += step;
			}
			y += NUM_THREADS * step;
			// TODO remove or adapt work only the first render
			if (clu->id == 0 && clu->v->fast_mode == false)
				mrt_mlx_refresh(clu->v);
		}

		pthread_mutex_lock(&clu->v->secu_mutex);
		clu->v->finished_thread++;
		clu->launch_thread = false;
		clu->count_ref_rays = 0;
		if (clu->v->finished_thread == NUM_THREADS)
		{
			clu->v->launch_multithread = false;
			clu->v->finished_thread = 0;
			pthread_cond_signal(&clu->v->main_cond);
		}
		pthread_mutex_unlock(&clu->v->secu_mutex);
	}

	return (NULL);
}
