/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:18:41 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 10:20:47 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_variable_len(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			break ;
		count++;
		i++;
	}
	return (count);
}

// This function returns the size of the variable.
int	ft_var_size(char *str, int pos)
{
	int	size;

	size = 0;
	if (str[pos] == '?')
		return (size + 1);
	while (str[pos] != 0)
	{
		if (ft_isalnum(str[pos]) == 1 || str[pos] == '_')
			size++;
		else
			break ;
		pos++;
	}
	return (size);
}

/*
This function extracts the variable name from the input string.
It returns the variable name using substring function.
*/
char	*ft_extract_var(char *str)
{
	int	i;
	int	pos;
	int	size;

	i = 0;
	pos = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			pos = i + 1;
			break ;
		}
		i++;
	}
	size = ft_var_size(str, pos);
	return (ft_substr(str, pos, size));
}

void	copy_var_value(char *new_str, char *var_value, int *j)
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

void	erase_variable(t_token *token_node, int index)
{
	char	*token_str;
	char	*new_token_str;
	int		i;
	int		j;

	token_str = token_node->token;
	i = 0;
	j = 0;
	new_token_str = (char *)malloc(sizeof(char) * (ft_strlen(token_str)
				- ft_variable_len(token_str + index)) + 1);
	if (new_token_str == NULL)
		return ;
	while (token_str[i] != '\0')
	{
		if (token_str[i] == '$' && i == index)
		{
			i = i + ft_variable_len(token_str + index) + 1;
			if (token_str[i] == '\0')
				break ;
		}
		new_token_str[j++] = token_str[i++];
	}
	new_token_str[j] = '\0';
	free_pointer(token_node->token);
	token_node->token = new_token_str;
}
