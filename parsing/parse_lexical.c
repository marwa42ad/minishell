/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:31:51 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 21:36:00 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	adds a token to the linked list, since it's a word, the status is NOQUOTE
*/
int	ft_add_word_token(t_config *config, int start, int end)
{
	char	*word;

	word = ft_substr(config->command_input, start, end - start);
	if (word == NULL)
		return (-1);
	lst_add_back_token(&config->token_list, lst_new_token(word, WORD, NOQUOTE));
	return (0);
}

/*
	adds a token to the linked list, since it's a separator,
	the status is NOQUOTE
*/
int	ft_add_sep_token(t_config *config, int i, int septype)
{
	char	*sep;
	int		size;

	if (septype == REDIR_HERE_DOC || septype == REDIR_APPEND)
		size = 2;
	else
		size = 1;
	sep = ft_substr(config->command_input, i, size);
	if (sep == NULL)
		return (-1);
	lst_add_back_token(&config->token_list,
		lst_new_token(sep, septype, NOQUOTE));
	return (0);
}

int	ft_process_token(t_config *config, int *i, int septype, int start)
{
	if (septype != 0)
	{
		if ((*i) != 0 && ft_get_separator(config->command_input, (*i) - 1) == 0)
			ft_add_word_token(config, start, *i);
		if (septype >= PIPE && septype <= END_OF_FILE)
		{
			ft_add_sep_token(config, *i, septype);
			if (septype == REDIR_HERE_DOC || septype == REDIR_APPEND)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

int	process_quotecheck(t_config *config, int end, int quotecheck, int septype)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i <= end)
	{
		quotecheck = ft_check_quotes(config->command_input[i], quotecheck);
		if (quotecheck == NOQUOTE)
		{
			septype = ft_get_separator(config->command_input, i);
			start = ft_process_token(config, &i, septype, start);
		}
		i++;
	}
	return (quotecheck);
}

bool	ft_tokenization(t_config *config)
{
	int	end;
	int	quotecheck;
	int	septype;

	end = ft_strlen(config->command_input);
	quotecheck = NOQUOTE;
	septype = 0;
	quotecheck = process_quotecheck(config, end, quotecheck, septype);
	if (quotecheck != NOQUOTE)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (false);
	}
	return (true);
}
