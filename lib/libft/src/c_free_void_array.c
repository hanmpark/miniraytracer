#include "libft.h"

// Frees an array of void
void	c_free_void_array(void **ar)
{
	int	i;

	if (!ar)
		return ;
	i = 0;
	while (ar[i])
		free(ar[i++]);
	free(ar);
}
