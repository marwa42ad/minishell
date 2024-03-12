/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:51:33 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 21:55:49 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == NOQUOTE)
		{
			if (str[i] == '\'')
				status = SINGLEQ;
			if (str[i] == '\"')
				status = DOUBLEQ;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SINGLEQ)
			|| (str[i] == '\"' && status == DOUBLEQ))
		{
			status = NOQUOTE;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->token[*i] == '\'')
		(*token_node)->status = SINGLEQ;
	if ((*token_node)->token[*i] == '\"')
		(*token_node)->status = DOUBLEQ;
	(*i)++;
}
