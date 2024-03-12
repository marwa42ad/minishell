/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:53:21 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/23 11:03:25 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_command(t_pre_command **cmd)
{
	(*cmd)->args_array = NULL;
	(*cmd)->command = NULL;
	(*cmd)->next = NULL;
	(*cmd)->path = NULL;
	(*cmd)->is_pipe_output = false;
	(*cmd)->prev = NULL;
}

t_pre_command	*lst_new_command(bool value)
{
	t_pre_command	*new_cmd;

	new_cmd = (t_pre_command *)malloc(sizeof(t_pre_command));
	if (new_cmd == NULL)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_pre_command));
	new_cmd->is_pipe_output = value;
	init_command(&new_cmd);
	return (new_cmd);
}

void	lst_add_back_cmd(t_pre_command **list, t_pre_command *new_cmd)
{
	t_pre_command	*begin;

	begin = *list;
	if (begin == NULL)
	{
		*list = new_cmd;
		return ;
	}
	if (list != 0 && *list != 0 && new_cmd != 0)
	{
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new_cmd;
		new_cmd->prev = begin;
	}
}

t_pre_command	*lst_last_cmd(t_pre_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

int	lst_size_cmd(t_pre_command *cmd)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
