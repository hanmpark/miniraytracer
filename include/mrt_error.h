/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanmpark <hanmpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:03:37 by yobouhle          #+#    #+#             */
/*   Updated: 2025/12/05 23:02:47 by hanmpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_ERROR_H
# define MRT_ERROR_H

# include "mrt.h"

/* GLOBAL ERROR */

# define ERR_FILE "Error\nInvalid file name\n"
# define ERR_OPEN "Error\nFailed to open file\n"
# define ERR_ALLOC "Error\nMemory allocation failed\n"
# define ERR_READ "Error\nFailed to read file\n"
# define ERR_ARG "Error\nInvalid argument found\n"

/* SCENE ELEMENT */

# define ERR_CAP "Error\nIncorrect number of 'A', 'C', or 'L'\n"
# define ERR_COMMA "Error\nIncoherent number of commas found\n"
# define ERR_NB_OBJS "Error\nInsufficient scene elements\n"
# define ERR_NBR_ARGS "Error\nIncorrect number of arguments\n"
# define ERR_UNDEFINED "Error\nUndefined object encountered\n"

/* DIGIT */

# define ERR_DOUBLE "Error\nDouble value not found\n"
# define ERR_INT "Error\nInteger value not found\n"
# define ERR_POS "Error\nPositive value not found\n"
# define ERR_STRDIGIT "Error\nNon-digit characters found\n"

/* MATRIX */

# define ERR_INV_MAT "Error\nCannot compute the inverse matrix\n"

/* RANGE */

# define ERR_RANGE_COLORS "Error\nColor value out of range [0, 255]\n"
# define ERR_RANGE_FOV "Error\nField of view (FOV) out of range [0, 180]\n"
# define ERR_NORM "Error\nValue must be in the range [-1, 1]\n"
# define ERR_RATIO "Error\nRatio must be within [0.0, 1.0]\n"
# define ERR_BOOL "Error\nBool must be in the range [-1, 1]\n"
# define ERR_SPECULAR "Error\nShininess [0, 10] Reflection [0, 1]\n"

/* THREADS */

# define ERR_MUTEX_INIT "Error\nFailed to initialize mutex\n"

/* USAGE */

# define ERR_USAGE "usage: ./miniRT <path/to/scene.rt>\n"

/* ERROR MESSAGE MRT/LAUNCH */

# define ERR_MLX "Error\nSomething wrong occured with MLX\n"

bool	error_bool(char *err_msg);
void	error_putline(char *line_str);
char	**error_array(char *err_msg);
bool	error_clean_array(char *err_msg, char **array);

#endif
