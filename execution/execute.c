/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:24:49 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 23:41:38 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_children(t_config *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->pre_cmds, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->process_id)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

static int	create_children(t_config *data)
{
	t_pre_command	*cmd;

	cmd = data->pre_cmds;
	while (data->process_id != 0 && cmd)
	{
		data->process_id = fork();
		if (data->process_id == -1)
		{
			display_error("fork", strerror(errno));
			return (EXIT_FAILURE);
		}
		else if (data->process_id == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

static int	prep_for_exec(t_config *data)
{
	if (data == NULL || data->pre_cmds == NULL)
		return (EXIT_SUCCESS);
	if (data->pre_cmds->command == NULL)
	{
		if (data->pre_cmds->io_fds
			&& !check_infile_outfile(data->pre_cmds->io_fds))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND_ERROR);
}

int	ms_execute(t_config *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND_ERROR)
		return (ret);
	if (!data->pre_cmds->is_pipe_output && !data->pre_cmds->prev
		&& check_infile_outfile(data->pre_cmds->io_fds))
	{
		redirect_io(data->pre_cmds->io_fds);
		ret = execute_builtin(data, data->pre_cmds);
		restore_io(data->pre_cmds->io_fds);
	}
	if (ret != CMD_NOT_FOUND_ERROR)
		return (ret);
	return (create_children(data));
}
