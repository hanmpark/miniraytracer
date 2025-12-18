#include "libft.h"

int	c_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}
