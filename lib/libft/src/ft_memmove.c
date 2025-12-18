#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_d;
	unsigned const char	*p_s;

	p_d = (unsigned char *)dest;
	p_s = (unsigned const char *)src;
	if ((p_d != p_s) && n)
	{
		if (p_d < p_s)
			ft_memcpy(dest, src, n);
		else
			while (n--)
				*(p_d + n) = *(p_s + n);
	}
	return (dest);
}
