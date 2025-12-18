#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	len_lst;

	if (lst == NULL)
		return (0);
	len_lst = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		len_lst++;
	}
	return (len_lst);
}
