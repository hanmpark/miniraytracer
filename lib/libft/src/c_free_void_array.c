/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_free_void_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:54:42 by yobouhle          #+#    #+#             */
/*   Updated: 2024/01/30 18:54:44 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Frees an array of void
void	c_free_void_array(void **ar)
{
	int	i;

	if (!ar)
		return ;
	i = 0;
	while (ar[i])
		free(ar[i++]);
	free(ar);
}
