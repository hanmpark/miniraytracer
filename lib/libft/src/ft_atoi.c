#include "libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned long	s;
	unsigned long	r;

	s = 1;
	r = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		s = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		r = (r * 10) + (*nptr - 48);
		nptr++;
	}
	return ((unsigned long)(s * r));
}
