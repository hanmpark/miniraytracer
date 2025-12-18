#include "libft.h"

// Checks if the string is only composed of digits
int	c_strisdigit(char *str)
{
	int	i;

	if (str[0] == '-')
		i = 0;
	else
		i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
