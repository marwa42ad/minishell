/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:22:36 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 23:39:57 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO REVIEW

t_token	*lst_new_token(char *str, int type, int status)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!(new_node))
		return (NULL);
	new_node->token = str;
	new_node->type = type;
	new_node->token_backup = NULL;
	new_node->status = status;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	lst_add_back_token(t_token **alst, t_token *new_node)
{
	t_token	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

void	lst_delone_token(t_token *lst)
{
	if (lst && lst->token)
	{
		if (lst->token != NULL)
		{
			free(lst->token);
			lst->token = NULL;
		}
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (lst != NULL)
	{
		free(lst);
		lst = NULL;
	}
}

void	lst_clear_token(t_token **lst)
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		lst_delone_token(*lst);
		*lst = tmp;
	}
}
