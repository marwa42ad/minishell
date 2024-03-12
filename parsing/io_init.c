/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:13:47 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 21:14:03 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_io(t_pre_command *cmd)
{
	if (!cmd->io_fds)
	{
		cmd->io_fds = malloc(sizeof * cmd->io_fds);
		if (!cmd->io_fds)
			return ;
		cmd->io_fds->infile_name = NULL;
		cmd->io_fds->outfile_name = NULL;
		cmd->io_fds->heredoc_delimiter = NULL;
		cmd->io_fds->has_heredoc_quotes = false;
		cmd->io_fds->fd_input = -1;
		cmd->io_fds->fd_output = -1;
		cmd->io_fds->stdin_backup = -1;
		cmd->io_fds->stdout_backup = -1;
	}
}
