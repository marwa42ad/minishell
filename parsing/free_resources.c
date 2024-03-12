/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:34:46 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 16:05:55 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_token_list(t_token *token_list)
{
	t_token	*temp;

	while (token_list != NULL)
	{
		temp = token_list;
		token_list = token_list->next;
		if (temp->token != NULL)
		{
			free(temp->token);
			temp->token = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free_pointer(args[i]);
		args[i] = NULL;
		i++;
	}
	free_pointer(args);
	args = NULL;
}

void	ft_free(t_pre_command *const *lst)
{
	free_pointer((*lst)->pipe_fd);
	free_io((*lst)->io_fds);
	free_pointer(*lst);
}

void	free_pre_cmd_list(t_pre_command **lst)
{
	t_pre_command	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		if ((*lst)->command != NULL)
		{
			free_pointer((*lst)->command);
			(*lst)->command = NULL;
		}
		if ((*lst)->path != NULL)
		{
			free_pointer((*lst)->path);
			(*lst)->path = NULL;
		}
		if ((*lst)->args_array != NULL)
		{
			free_args((*lst)->args_array);
			(*lst)->args_array = NULL;
		}
		ft_free(lst);
		*lst = temp;
	}
}

void	free_config(t_config *config)
{
	if (config != NULL && config->token_list != NULL)
	{
		free_token_list(config->token_list);
		config->token_list = NULL;
	}
	if (config != NULL && config->command_input != NULL)
	{
		free(config->command_input);
		config->command_input = NULL;
	}
	if (config != NULL && config->pre_cmds != NULL)
	{
		free_pre_cmd_list(&config->pre_cmds);
		config->pre_cmds = NULL;
	}
}
