/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:32:54 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/29 14:51:35 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_infile(t_ios *io, char *file, char *original_filename)
{
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile_name = ft_strdup(file);
	if (io->infile_name && io->infile_name[0] == '\0')
	{
		display_error(original_filename, "ambiguous redirect");
		return ;
	}
	io->fd_input = open(io->infile_name, O_RDONLY);
	if (io->fd_input == -1)
		display_error(io->infile_name, strerror(errno));
}

void	syntax_redir_in(t_pre_command **cmd, t_token **token)
{
	t_pre_command	*end_command;
	t_token			*temp;

	temp = *token;
	end_command = lst_last_cmd(*cmd);
	init_io(end_command);
	open_infile(end_command->io_fds, temp->next->token,
		temp->next->token_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token = temp;
}
