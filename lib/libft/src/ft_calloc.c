#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	t;
	void	*ptr;

	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	t = nmemb * size;
	ptr = malloc(t);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, t);
	return (ptr);
}
