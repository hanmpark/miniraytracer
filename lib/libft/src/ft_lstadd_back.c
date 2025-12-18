#include "libft.h"
#include "stdio.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_lst;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp_lst = ft_lstlast(*lst);
	temp_lst->next = new;
}
