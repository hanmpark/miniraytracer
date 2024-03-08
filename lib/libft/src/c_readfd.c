/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_readfd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 21:06:07 by yobouhle          #+#    #+#             */
/*   Updated: 2023/03/20 00:14:13 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_readfd_loop(int *fd, char *s_read, char **s_tot, ssize_t *res)
{
	char	*s_tmp;

	while (*res == BUFFER_SIZE)
	{
		*res = read(*fd, s_read, BUFFER_SIZE);
		if (*res == -1)
		{
			free(*s_tot);
			return (-1);
		}
		else if (res == 0)
			return (0);
		s_read[*res] = '\0';
		s_tmp = malloc((ft_strlen(*s_tot) + *res + 1) * sizeof(char));
		if (s_tmp == NULL)
		{
			free(*s_tot);
			return (-1);
		}
		ft_strlcpy(s_tmp, *s_tot, ft_strlen(*s_tot) + 1);
		ft_strlcat(s_tmp, s_read, ft_strlen(*s_tot) + *res + 1);
		free(*s_tot);
		*s_tot = s_tmp;
	}
	return (0);
}

char	*c_readfd(int fd)
{
	char	s_read[BUFFER_SIZE + 1];
	char	*s_tot;
	ssize_t	res;

	res = read(fd, s_read, BUFFER_SIZE);
	if (res <= 0)
		return (NULL);
	s_read[res] = '\0';
	s_tot = malloc((res + 1) * sizeof(char));
	if (s_tot == NULL)
		return (NULL);
	ft_strlcpy(s_tot, s_read, res + 1);
	if (res == BUFFER_SIZE && c_readfd_loop(&fd, s_read, &s_tot, &res))
		return (NULL);
	return (s_tot);
}
