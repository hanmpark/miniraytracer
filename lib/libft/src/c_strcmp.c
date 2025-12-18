#include "libft.h"

// Compares two strings
int	c_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return ((unsigned char) *s1 - *s2);
}
