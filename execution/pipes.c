/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marwamostafa <marwamostafa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:25:07 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/11 15:37:39 by marwamostaf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*the function goes through a list of commands and closes the pipe file descriptors
associated with each command, except for skip_cmd. 
The purpose is to clean up resources and ensure that pipes are properly closed
when they are no longer needed.*/
void	close_pipe_fds(t_pre_command *cmds, t_pre_command *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipe_fd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	create_pipes(t_config *data)
{
	int				*fd;
	t_pre_command	*tmp;

	tmp = data->pre_cmds;
	while (tmp)
	{
		if (tmp->is_pipe_output || (tmp->prev && tmp->prev->is_pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (fd == NULL || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	set_pipe_fds(t_pre_command *cmds, t_pre_command *c)
{
	if (c == NULL)
		return (false);
	if (c->prev && c->prev->is_pipe_output)
		dup2(c->prev->pipe_fd[0], STDIN_FILENO);//duplicate the read end of the pipe
		//(c->prev->pipe_fd[0]) to the standard input 
	if (c->is_pipe_output)
		dup2(c->pipe_fd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (true);
}
