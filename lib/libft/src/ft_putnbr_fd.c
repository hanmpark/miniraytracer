/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:22:47 by yobouhle          #+#    #+#             */
/*   Updated: 2022/11/23 11:24:14 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
	else if (n >= 0)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putchar_fd('-', fd);
		if (n == -2147483648)
		{
			n /= 10;
			ft_putnbr_fd(-n, fd);
			ft_putchar_fd('8', fd);
		}
		else
			ft_putnbr_fd(-n, fd);
	}
}
