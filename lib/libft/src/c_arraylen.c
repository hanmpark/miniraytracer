#include "libft.h"

// Counts the length of an array
size_t	c_arraylen(char **ar)
{
	size_t	len;

	len = 0;
	while (ar && ar[len])
		len++;
	return (len);
}
