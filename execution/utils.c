/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:38:00 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 21:32:23 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function used to search for the environment variable in the linked list
char	*find_env(t_config *config, char *env_name)
{
	t_list	*tmp;

	tmp = config->ls_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, env_name) == 0)
		{
			return ((char *)tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_putendl_fd(char *s, int fd)
{
	char	*tmp;

	tmp = ft_strjoin(s, "\n");
	ft_putstr_fd(tmp, fd);
	free_pointer(tmp);
}

/*
In the first interation this function stores the configuration
from config. On the following calls it just uses it.
 */
t_config	*get_config_instance(t_config *config)
{
	static t_config	*cpy_config;

	if (config != NULL)
		cpy_config = config;
	return (cpy_config);
}
