/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:18:41 by yobouhle          #+#    #+#             */
/*   Updated: 2024/01/25 12:03:24 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	t;
	void	*ptr;

	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	t = nmemb * size;
	ptr = malloc(t);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, t);
	return (ptr);
}
