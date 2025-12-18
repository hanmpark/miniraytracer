#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*p_n;

	if (s == NULL || f == NULL)
		return ;
	p_n = s;
	while (*p_n)
	{
		(*f)((p_n - s), p_n);
		p_n++;
	}
}
