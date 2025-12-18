#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst_out;

	lst_out = malloc(sizeof(t_list));
	if (lst_out == NULL)
		return (NULL);
	lst_out->content = content;
	lst_out->next = NULL;
	return (lst_out);
}
