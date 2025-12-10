#include "mrt_error.h"
#include "mrt_render.h"

static double get_time_seconds(void)
{
	struct timeval t;

	gettimeofday(&t, NULL);
	return (t.tv_sec + t.tv_usec / 1e6);
}

static void launch_multithread(t_mrt *v)
{
	int i;

	i = 0;
	pthread_mutex_lock(&v->secu_mutex);
	while (i < NUM_THREADS)
	{
		v->threads[i].launch_thread = true;
		i++;
	}
	v->launch_multithread = true;
	pthread_cond_broadcast(&v->threads_cond);
	pthread_mutex_unlock(&v->secu_mutex);
}

// TODO TOSEE this is not needed main thread can keep running and first thread handle refresh (avoid mlx waiting)
static void wait_end_multithread(t_mrt *v)
{
	pthread_mutex_lock(&v->secu_mutex);
	while (v->launch_multithread == true)
		pthread_cond_wait(&v->main_cond, &v->secu_mutex);
	pthread_mutex_unlock(&v->secu_mutex);
}

int launch_render(t_mrt *v)
{
	double start;
	double elapsed;

	mrt_mlx_clear(v);
	start = get_time_seconds();

	launch_multithread(v);
	wait_end_multithread(v);

	mrt_mlx_refresh(v);

	elapsed = get_time_seconds() - start;
	printf("Rendering took %.2f seconds.\n", elapsed);

	return (0);
}

bool init_threads(t_mrt *v)
{
	int i;

	if (pthread_mutex_init(&(v->secu_mutex), NULL))
		return (error_bool(ERR_MUTEX_INIT));
	if (pthread_cond_init(&(v->threads_cond), NULL))
		return (error_bool(ERR_THREAD_COND_INIT));
	if (pthread_cond_init(&(v->main_cond), NULL))
		return (error_bool(ERR_THREAD_COND_INIT));

	i = 0;
	while (i < NUM_THREADS)
	{
		v->threads[i].id = i;
		v->threads[i].v = v;
		v->threads[i].count_ref_rays = 0; // TODO check why count_ref_rays init 0 too (sample_pixel) ?
		v->threads[i].launch_thread = false;
		// v->threads[i].camray initialize by setup_camera_ray TODO ?
		i++;
	}

	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_create(&v->threads[i].thread, NULL, thread_render, &v->threads[i]))
			return (error_bool(ERR_THREAD_INIT));
		i++;
	}
	return (true);
}
