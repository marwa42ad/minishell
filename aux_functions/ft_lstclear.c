/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:07:07 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 23:40:29 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*list;

	if (!lst)
		return ;
	list = *lst;
	while (list)
	{
		temp = list->next;
		free_pointer(list->name);
		free_pointer(list->value);
		free_pointer(list);
		list = temp;
	}
	*lst = NULL;
}
