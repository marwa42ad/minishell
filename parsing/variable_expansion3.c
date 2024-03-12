/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:22:34 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/09 10:24:10 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_variable_expansion(t_config *config, t_token *currenttoken)
{
	t_token	*token;
	int		i;
	char	*env_value;

	token = currenttoken;
	i = 0;
	while (token->token[i] != '\0')
	{
		token->status = ft_check_quotes(token->token[i], token->status);
		if (token->token[i] == '$' && (token->token[i + 1] != '$'
				&& token->token[i + 1] != ' ' && token->token[i + 1] != '='
				&& token->token[i + 1] != '\0') && token->status != SINGLEQ)
		{
			env_value = ft_retrieve_env_value(config, token->token + i);
			ft_replace(token, env_value, i);
		}
		else
			i++;
	}
}

/*
This function expands all the variables,
which is replace variables with their values.
*/
void	ft_expand_all_variables(t_config *config)
{
	t_token	*token;

	token = config->token_list;
	while (token != NULL)
	{
		if (token->type == VAR)
			ft_variable_expansion(config, token);
		token = token->next;
	}
}

bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

bool	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

char	*erase_and_replace(t_token **token_node, char *str,
			char *var_value, int index)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - ft_variable_len(str + index)
			+ ft_strlen(var_value));
	newstr = generate_new_token_string(str, var_value, newstr_size, index);
	if (token_node && *token_node)
	{
		free_pointer((*token_node)->token);
		(*token_node)->token = newstr;
	}
	return (newstr);
}
