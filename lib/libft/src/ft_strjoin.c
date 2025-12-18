#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_o;
	char	*p_n;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p_o = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (p_o == NULL)
		return (NULL);
	p_n = p_o;
	while (*s1)
		*p_n++ = *s1++;
	while (*s2)
		*p_n++ = *s2++;
	*p_n = '\0';
	return (p_o);
}
