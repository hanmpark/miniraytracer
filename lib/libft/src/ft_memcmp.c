#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_n;
	unsigned char	*s2_n;

	s1_n = (unsigned char *)s1;
	s2_n = (unsigned char *)s2;
	while (n--)
		if (*s1_n++ != *s2_n++)
			return (*--s1_n - *--s2_n);
	return (0);
}
