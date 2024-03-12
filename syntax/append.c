/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:09:20 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 11:42:51 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	remove_old_file_ref(t_ios *io, bool infile)
{
	if (infile == true && io->infile_name)
	{
		if (io->fd_input == -1 || (io->outfile_name && io->fd_output == -1))
			return (false);
		if (io->heredoc_delimiter != NULL)
		{
			free_pointer(io->heredoc_delimiter);
			io->heredoc_delimiter = NULL;
			unlink(io->infile_name);
		}
		free_pointer(io->infile_name);
		close(io->fd_input);
	}
	else if (infile == false && io->outfile_name)
	{
		if (io->fd_output == -1 || (io->infile_name && io->fd_input == -1))
			return (false);
		free_pointer(io->outfile_name);
		close(io->fd_output);
	}
	return (true);
}

static void	open_outfile_append(t_ios *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile_name = ft_strdup(file);
	if (io->outfile_name && io->outfile_name[0] == '\0' && var_filename)
	{
		display_error(var_filename, "ambiguous redirect");
		return ;
	}
	io->fd_output = open(io->outfile_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_output == -1)
		display_error(io->outfile_name, strerror(errno));
}

void	syntax_append(t_pre_command **cmd, t_token **token)
{
	t_pre_command	*end_command;
	t_token			*temp;

	temp = *token;
	end_command = lst_last_cmd(*cmd);
	init_io(end_command);
	open_outfile_append(end_command->io_fds, temp->next->token,
		temp->next->token_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token = temp;
}
