/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:55:16 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 16:02:21 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_config *data, bool clear_history)
{
	if (data && data->command_input)
	{
		free_pointer(data->command_input);
		data->command_input = NULL;
	}
	if (data && data->token_list)
		lst_clear_token(&data->token_list);
	if (data != NULL && data->pre_cmds != NULL)
	{
		free_pre_cmd_list(&data->pre_cmds);
		data->pre_cmds = NULL;
	}
	if (clear_history == true)
	{
		if (data && data->working_dir)
			free_pointer(data->working_dir);
		if (data && data->old_working_dir)
			free_pointer(data->old_working_dir);
		if (data && data->ls_env)
			ft_lstclear(&data->ls_env);
	}
}

/* close_fds:
*	Closes opened file descriptors, including pipes and input and
*	output fds. If close_backups is set to true, it also closes
*	backup STDIN and STDOUT file descriptors.
*/
void	close_fds(t_pre_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_input != -1)
			close(cmds->io_fds->fd_input);
		if (cmds->io_fds->fd_output != -1)
			close(cmds->io_fds->fd_output);
		if (close_backups)
			restore_io(cmds->io_fds);
	}
	close_pipe_fds(cmds, NULL);
}

/* free_io:
*	Frees the input/output fd structure.
*/
void	free_io(t_ios *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->heredoc_delimiter)
	{
		unlink(io->infile_name);
		free_pointer(io->heredoc_delimiter);
	}
	if (io->infile_name)
		free_pointer(io->infile_name);
	if (io->outfile_name)
		free_pointer(io->outfile_name);
	if (io)
		free_pointer(io);
}

/* free_str_tab:
*	Frees an array of strings.
*/
void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_pointer(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free_pointer(tab);
		tab = NULL;
	}
}

/* free_pointer:
*	Frees a pointer of any type if it is not NULL and sets it to NULL.
*	This avoids accidental double-frees.
*/
void	free_pointer(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
