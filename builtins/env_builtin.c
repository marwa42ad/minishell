/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:35:58 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/08 22:14:03 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_env_string(const t_list *env_item, char *line_name)
{
	char	*line_total;

	line_total = ft_strjoin(line_name, env_item->value);
	ft_putendl_fd(line_total, STDOUT_FILENO);
	free_pointer(line_name);
	free_pointer(line_total);
}

int	env_builtin(t_config *data, char **args)
{
	t_list	*env_item;
	char	*line_name;

	if (args && args[1])
	{
		display_error("env", "too many arguments");
		return (2);
	}
	if (data == NULL || data->ls_env == NULL)
		return (EXIT_FAILURE);
	env_item = data->ls_env;
	while (env_item)
	{
		line_name = ft_strjoin(env_item->name, "=");
		if (env_item->value != NULL)
			build_env_string(env_item, line_name);
		else
		{
			ft_putendl_fd(line_name, STDOUT_FILENO);
			free_pointer(line_name);
		}
		env_item = env_item->next;
	}
	return (EXIT_SUCCESS);
}
