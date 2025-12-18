#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list_temp;

	if (lst == NULL || del == NULL)
		return ;
	list_temp = *lst;
	while (*lst)
	{
		list_temp = list_temp->next;
		ft_lstdelone(*lst, del);
		*lst = list_temp;
	}
}
