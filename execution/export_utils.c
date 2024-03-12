/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 19:37:04 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 23:41:44 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env(t_config *config, char *name, char *value)
{
	t_list	*temp;

	temp = config->ls_env;
	while (temp)
	{
		if (ft_strlen(temp->name) == ft_strlen(name)
			&& ft_strncmp(temp->name, name, ft_strlen(temp->name)) == 0)
		{
			if (temp->value && ft_strncmp(temp->value, "", 1) != 0)
				free(temp->value);
			temp->value = value;
			return (0);
		}
		temp = temp->next;
	}
	if (temp == NULL)
		ft_lstadd_back(&config->ls_env, ft_lstnew(name, value));
	return (0);
}
