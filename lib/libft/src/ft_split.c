/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobouhle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:25:22 by yobouhle          #+#    #+#             */
/*   Updated: 2024/01/25 17:30:16 by yobouhle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words_split(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

static int	ft_write_words_split(char const *s, char c, char **split)
{
	size_t	i;
	size_t	word;
	size_t	word_start;

	i = 0;
	word = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		word_start = i;
		while (s[i] && s[i] != c)
			i++;
		split[word] = ft_substr(s, word_start, i - word_start);
		if (split[word++] == NULL)
		{
			while (--word)
				free(split[word - 1]);
			return (-1);
		}
		while (s[i] && s[i] == c)
			i++;
	}
	split[word] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**p_p;
	size_t	words;

	if (s == NULL)
		return (NULL);
	words = ft_count_words_split(s, c);
	p_p = (char **)malloc((words + 1) * sizeof(char *));
	if (p_p == NULL)
		return (NULL);
	if (ft_write_words_split(s, c, p_p))
	{
		free(p_p);
		return (NULL);
	}
	return (p_p);
}
