/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_thread_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:59:59 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 16:39:36 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_error_bonus.h"
#include "mrt_render_bonus.h"

static double	get_time_seconds(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec + t.tv_usec / 1e6);
}

int	render_threaded(t_mrt *v)
{
	double	start;
	int		i;

	start = get_time_seconds();
	i = -1;
	mrt_mlx_clear(v);
	while (++i < NUM_THREADS)
		pthread_create(&v->threads[i].thread, NULL, render, &v->threads[i]);
	i = -1;
	while (v->finished_thread != NUM_THREADS)
		mrt_mlx_refresh(v);
	pthread_mutex_destroy(&v->count_mutex);
	printf("Rendering took %.2f seconds.\n", get_time_seconds() - start);
	return (0);
}

bool	init_threads(t_mrt *v)
{
	static const double	sliceheight = SCR_HGH / NUM_THREADS;
	int					i;

	i = 0;
	v->finished_thread = 0;
	while (i < NUM_THREADS)
	{
		v->threads[i].v = v;
		v->threads[i].count_ref_rays = 0;
		v->threads[i].start_y = i * sliceheight;
		v->threads[i].end_y = (i + 1) * sliceheight;
		if (i == NUM_THREADS - 1)
			v->threads[i].end_y = SCR_HGH;
		i++;
	}
	if (pthread_mutex_init(&v->count_mutex, NULL))
		return (error_bool(ERR_MUTEX_INIT));
	return (true);
}
