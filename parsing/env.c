/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:07:25 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 12:08:35 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Obs: the last element of env is NULL.
	I'm setting the last element of the array to null as well to be easy
	to find/count.
	This function will creat a list with all the env variables, using =
	as a separator.
*/
void	init_env(char **env, t_config *config)
{
	int		i;
	int		j;
	int		k;
	char	**str;

	i = 0;
	j = 0;
	k = 0;
	config->ls_env = NULL;
	while (env[i] != 0)
		i++;
	while (j < i)
	{
		str = ft_split(env[j], '=');
		ft_lstadd_back(&config->ls_env, ft_lstnew(ft_strdup(str[0]),
				ft_strdup(str[1])));
		while (str[k] != NULL)
		{
			free_pointer(str[k]);
			k++;
		}
		k = 0;
		free_pointer(str);
		j++;
	}
}

/* is_valid_env:
*	Checks if the key is a valid name for an evironment
*	variable.
*	Returns true if the key contains only alphanumeric chars
*	or '_', or false if not.
*/
bool	is_valid_env(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	**env_to_array(t_config *data)
{
	char	**env_array;
	int		i;
	t_list	*crnt;
	char	*temp;

	i = 0;
	crnt = data->ls_env;
	env_array = malloc(sizeof(char *) * (ft_lstsize(crnt) + 1));
	while (crnt)
	{
		temp = ft_strjoin(crnt->name, "=");
		if (crnt->value == NULL)
			env_array[i] = ft_strdup(temp);
		else
			env_array[i] = ft_strjoin(temp, crnt->value);
		free_pointer(temp);
		crnt = crnt->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
