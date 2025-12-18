#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*e;

	e = s;
	while (*e)
		e++;
	return (e - s);
}
