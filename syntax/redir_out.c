/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:49:45 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 11:31:44 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_outfile_trunc(t_ios *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile_name = ft_strdup(file);
	if (io->outfile_name && io->outfile_name[0] == '\0')
	{
		display_error(var_filename, "ambiguous redirect");
		return ;
	}
	io->fd_output = open(io->outfile_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_output == -1)
		display_error(io->outfile_name, strerror(errno));
}

void	syntax_redir_out(t_pre_command **cmd, t_token **token)
{
	t_pre_command	*end_command;
	t_token			*temp;

	temp = *token;
	end_command = lst_last_cmd(*cmd);
	init_io(end_command);
	open_outfile_trunc
		(end_command->io_fds, temp->next->token, temp->next->token_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token = temp;
}
