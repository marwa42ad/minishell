/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:04:05 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 21:55:10 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	if_quotes_and_default(t_token **token_node, int i)
{
	if (((*token_node)->token[i] == '\'' || (*token_node)->token[i] == '\"')
		&& (*token_node)->status == NOQUOTE)
		return (true);
	else
		return (false);
}

static bool	change_back_to_default(t_token **token_node, int *i)
{
	if (((*token_node)->token[*i] == '\'' && (*token_node)->status == SINGLEQ)
		|| ((*token_node)->token[*i] == '\"'
			&& (*token_node)->status == DOUBLEQ))
	{
		(*token_node)->status = NOQUOTE;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->token, i, i));
	if (new_line == NULL)
		return (1);
	while ((*token_node)->token[i])
	{
		if (if_quotes_and_default(token_node, i) == true)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_default(token_node, &i) == true)
			continue ;
		new_line[j++] = (*token_node)->token[i++];
	}
	new_line[j] = '\0';
	free_pointer((*token_node)->token);
	(*token_node)->token = new_line;
	return (0);
}

bool	quotes_in_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	ft_quotes_removal(t_config *config)
{
	t_token	*temp;

	temp = config->token_list;
	while (temp)
	{
		if (quotes_in_string(temp->token) == true && (!temp->prev
				|| (temp->prev && temp->prev->type != REDIR_HERE_DOC)))
			remove_quotes(&temp);
		temp = temp->next;
	}
}

/*
3.5.9 Quote Removal
After the preceding expansions, all unquoted occurrences of the
characters ‘\’, ‘'’, and ‘"’ that did not result from one of the
above expansions are removed.

https://www.gnu.org/software/bash/manual/html_node/Quote-Removal.html
*/
