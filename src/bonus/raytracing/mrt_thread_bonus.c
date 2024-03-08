/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_thread_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:59:59 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/08 14:22:06 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_render_bonus.h"

bool	init_threads(t_mrt *v)
{
	static const double	sliceheight = SCR_HGH / NUM_THREADS;
	int					i;

	i = 0;
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
	return (true);
}

int	render_threaded(t_mrt *v)
{
	int		i;
	double	elapsed;

	i = -1;
	mrt_mlx_clear(v);
	while (++i < NUM_THREADS)
		pthread_create(&v->threads[i].thread, NULL, render, &v->threads[i]);
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(v->threads[i].thread, NULL);
	mrt_mlx_refresh(v);
	gettimeofday(&v->t.end_time, NULL);
	v->t.seconds = v->t.end_time.tv_sec - v->t.start_time.tv_sec;
	v->t.microseconds = v->t.end_time.tv_usec - v->t.start_time.tv_usec;
	elapsed = v->t.seconds + v->t.microseconds / 1e6;
	printf("Rendering took %.2f seconds.\n", elapsed);
	return (0);
}
