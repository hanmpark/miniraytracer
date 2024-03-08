/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_thread_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:59:59 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 15:58:20 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
