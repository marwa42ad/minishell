/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:33:14 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 16:04:08 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function search and return the value of the variable from the env list.
char	*ft_retrieve_env_value(t_config *config, char *str)
{
	char	*var;
	char	*value;

	var = ft_extract_var(str);
	value = find_env(config, var);
	if (value == NULL)
	{
		if (var && var[0] == '?')
			value = ft_itoa(config->error_code);
	}
	free(var);
	var = NULL;
	return (value);
}

char	*generate_new_token_string(char *old, char *var_value,
		int len, int index)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * len);
	if (new == NULL)
		return (NULL);
	while (old[i] != '\0')
	{
		if (old[i] == '$' && i == index)
		{
			str_update(new, var_value, &j);
			i = i + ft_variable_len(old + index) + 1;
			if (old[i] == '\0')
				break ;
		}
		new[j] = old[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

void	replace_variable(t_token *token_node,
			char *env_value, int index)
{
	char	*newstr;
	int		newstr_size;
	int		var_size;
	char	*str;

	str = token_node->token;
	var_size = ft_variable_len(str + index);
	newstr_size = (ft_strlen(str) - var_size
			+ ft_strlen(env_value));
	newstr = generate_new_token_string(str, env_value, newstr_size, index);
	if (token_node != NULL && token_node->token != NULL)
	{
		free_pointer(token_node->token);
		token_node->token = newstr;
	}
}

void	ft_replace(t_token *token, char *env_value, int index)
{
	if (env_value == NULL)
		erase_variable(token, index);
	else
		replace_variable(token, env_value, index);
}

/*
Rules to expand variables:
1. Variable with double quotes are expanded (ex: echo "$PATH");
2. Variable with single quotes are not expanded (ex: echo '$PATH');
3. Variable with no quotes are expanded (ex: echo $PATH);

there is no need to set the status of the token to "NOQUOTE" since it
was already set in the parse_lexical.c file;

Special parameters
	"$?"" - exit status of the last command;
*/