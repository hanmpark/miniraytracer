/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_arraylen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:22:29 by hanmpark          #+#    #+#             */
/*   Updated: 2024/01/25 17:31:38 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Counts the length of an array
size_t	c_arraylen(char **ar)
{
	size_t	len;

	len = 0;
	while (ar && ar[len])
		len++;
	return (len);
}
