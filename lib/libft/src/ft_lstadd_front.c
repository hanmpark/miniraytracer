#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*temp_lst;

	if (lst == NULL || new == NULL)
		return ;
	temp_lst = *lst;
	*lst = new;
	new->next = temp_lst;
}
