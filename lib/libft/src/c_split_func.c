/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_split_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:25:22 by yobouhle          #+#    #+#             */
/*   Updated: 2024/01/25 19:43:22 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, int (*f)(int))
{
	size_t	count;

	count = 0;
	while (*str && f(*str))
		str++;
	if (*str == 0)
		return (0);
	while (*str)
	{
		count++;
		while (*str && !f(*str))
			str++;
		while (*str && f(*str))
			str++;
	}
	return (count);
}

static char	*cpy_to_tab(char const *str, size_t size)
{
	char	*tab;
	size_t	i;

	i = 0;
	tab = malloc((size + 1) * sizeof(char));
	if (!tab)
		return (0);
	while (i < size)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

// Splits a string into an array of substrings based on a specified delimiter.
char	**c_split_func(char const *s, int (*f)(int))
{
	char	**tab;
	size_t	j;
	size_t	count;

	if (!s)
		return (0);
	count = count_words(s, f);
	tab = malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (0);
	while (*s)
	{
		if (*s && !f(*s))
		{
			j = 0;
			while (s[j] && !f(s[j]))
				j++;
			*(tab++) = cpy_to_tab(s, j);
			s += j;
		}
		else
			s++;
	}
	*tab = 0;
	return (tab - count);
}
