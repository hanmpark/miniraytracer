#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p_o;
	char	*p_n;

	if (s == NULL || f == NULL)
		return (NULL);
	p_o = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (p_o == NULL)
		return (NULL);
	p_n = p_o;
	while (*s)
	{
		*p_n = (*f)((p_n - p_o), *s++);
		p_n++;
	}
	*p_n = '\0';
	return (p_o);
}
