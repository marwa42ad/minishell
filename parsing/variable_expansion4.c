/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:27:22 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 10:30:24 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	str_update(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_and_replace(NULL, str, var_value, index);
		free_pointer(tmp);
	}
	return (str);
}

char	*var_expander_heredoc(t_config *data, char *str)
{
	int		i;
	char	*env_value;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$'
			&& is_next_char_a_sep(str[i + 1]) == false
			&& var_between_quotes(str, i) == false)
		{
			env_value = ft_retrieve_env_value(data, str + i);
			str = replace_str_heredoc(str, env_value, i);
		}
		else
			i++;
	}
	return (str);
}
