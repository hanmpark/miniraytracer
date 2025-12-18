#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_size;

	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	while (*src != '\0' && size-- > 1)
		*dest++ = *src++;
	*dest = '\0';
	return (src_size);
}
