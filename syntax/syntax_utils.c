/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:53:57 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 11:32:25 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_add_new_token(t_token **token_lst,
	char *token_name, int type, int status)
{
	lst_add_back_token(token_lst,
		lst_new_token(token_name, type, status));
}

int	count_arguments(t_token *temp)
{
	int	count;

	count = 0;
	while (temp != NULL && (temp->type == WORD || temp->type == VAR))
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
