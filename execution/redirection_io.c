/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:28:47 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 15:32:44 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	restore_io(t_ios *io)
{
	int	ret;

	ret = true;
	if (io == NULL)
		return (ret);
	if (io->stdin_backup != -1)
	{
		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1)
	{
		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

int	redir_io_fd(t_ios *io)
{
	int	ret;

	if ((io->fd_input != -1) && dup2(io->fd_input, STDIN_FILENO) == -1)
	{
		display_detailed_err("dup2", io->infile_name, strerror(errno));
		ret = false;
	}
	if ((io->fd_output != -1) && (dup2(io->fd_output, STDOUT_FILENO) == -1))
	{
		display_detailed_err("dup2", io->outfile_name, strerror(errno));
		ret = false;
	}
	return (ret);
}

bool	redirect_io(t_ios *io)
{
	int	ret;

	ret = true;
	if (io == NULL)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
	{
		display_detailed_err("dup", "stdin backup", strerror(errno));
		ret = false;
	}
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
	{
		display_detailed_err("dup", "stdout backup", strerror(errno));
		ret = false;
	}
	ret = redir_io_fd(io);
	return (ret);
}

bool	check_infile_outfile(t_ios *io)
{
	if (io == NULL || (io->infile_name == NULL && io->outfile_name == NULL))
		return (true);
	if ((io->infile_name != NULL && io->fd_input == -1)
		|| (io->outfile_name != NULL && io->fd_output == -1))
		return (false);
	return (true);
}
