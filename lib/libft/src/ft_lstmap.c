#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_start;
	t_list	*lst_out;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	lst_start = ft_lstnew((*f)(lst->content));
	if (lst_start == NULL)
		return (NULL);
	lst_out = lst_start;
	while (lst->next != NULL)
	{
		lst = lst->next;
		lst_out->next = ft_lstnew((*f)(lst->content));
		if (lst_out->next == NULL)
		{
			ft_lstclear(&lst_start, del);
			return (NULL);
		}
		lst_out = lst_out->next;
	}
	return (lst_start);
}
