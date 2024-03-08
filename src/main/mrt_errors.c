/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:50:00 by hanmpark          #+#    #+#             */
/*   Updated: 2024/03/07 08:54:32 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mrt_error.h"

/*
 * error_bool
 * ----------
 * Displays an error message in bold red and returns false.
 */
bool	error_bool(char *err_msg)
{
	ft_putstr_fd(BOLD RED, 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd(DEF, 2);
	return (false);
}

/*
 * error_putline
 * -------------
 * Displays an error message for a specific line number in red.
 */
void	error_putline(char *line_str)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Line : ", 2);
	ft_putstr_fd(IT, 2);
	ft_putendl_fd(line_str, 2);
	ft_putstr_fd(DEF, 2);
}

/*
 * error_array
 * -----------
 * Displays an error message in bold red and returns NULL.
 */
char	**error_array(char *err_msg)
{
	ft_putstr_fd(BOLD RED, 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd(DEF, 2);
	return (NULL);
}

/*
 * error_clean_array
 * -----------------
 * Frees an array of strings and returns false.
 */
bool	error_clean_array(char *err_msg, char **array)
{
	c_free_void_array((void **)array);
	ft_putstr_fd(BOLD RED, 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd(DEF, 2);
	return (false);
}
