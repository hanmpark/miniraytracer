/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 06:27:15 by yobouhle          #+#    #+#             */
/*   Updated: 2024/03/08 16:49:19 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_error.h"
#include "mrt_parsing.h"
#include "mrt_render.h"

static bool	launch(t_mrt *v)
{
	if (!init_mrt_mlx(v))
		return (false);
	set_mrt_mlx_hook(v);
	return (true);
}

int	main(int ac, char **av)
{
	t_mrt	v;

	if (ac != 2)
	{
		ft_putstr_fd(ERR_USAGE, 2);
		return (1);
	}
	else if (mrt_parsing(&v, av[1]) == false)
		return (2);
	if (launch(&v) == false)
	{
		free(v.objs);
		return (3);
	}
	return (0);
}
