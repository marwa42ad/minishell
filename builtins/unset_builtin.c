/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:52:55 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 13:55:02 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unset_lst(t_list **lst, char *name)
{
	t_list	*crnt;
	t_list	*to_del;

	crnt = *lst;
	while (crnt->next)
	{
		if (ft_strncmp(crnt->next->name, name, ft_strlen(name)) == 0)
		{
			to_del = crnt->next;
			if (crnt->next->next)
				crnt->next = crnt->next->next;
			else
				crnt->next = NULL;
			ft_lstdelone(to_del);
		}
		if (crnt->next)
			crnt = crnt->next;
	}
	return (0);
}

int	process_unset(t_config *config, char *const *args, int i)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (!is_valid_env(args[i]) || ft_strchr(args[i], '=') != NULL)
	{
		display_detailed_err("unset", args[i], "not a valid identifier");
		ret = EXIT_FAILURE;
	}
	else
	{
		if (ft_retrieve_env_value(config, args[i]) != NULL)
			unset_lst(&config->ls_env, args[i]);
	}
	return (ret);
}

int	unset_builtin(t_config *config, char **args)
{
	int	i;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args != NULL && args[i])
	{
		ret = process_unset(config, args, i);
		i++;
	}
	return (ret);
}
