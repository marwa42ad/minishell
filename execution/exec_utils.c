/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:10:38 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 16:19:21 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Checks if the command is a directory rather than an executable.
	Returns false if not.
*/
bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	check_command_not_found(t_config *data, t_pre_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL
		&& ft_retrieve_env_value(data, "PATH") != NULL)
	{
		display_error(cmd->command, "command not found");
		return (CMD_NOT_FOUND_ERROR);
	}
	if (access(cmd->command, F_OK) != 0)
	{
		display_error(cmd->command, strerror(errno));
		return (CMD_NOT_FOUND_ERROR);
	}
	else if (cmd_is_dir(cmd->command))
	{
		display_error(cmd->command, "is a directory");
		return (CMD_NOT_EXECUTABLE_ERROR);
	}
	else if (access(cmd->command, F_OK | X_OK) != 0)
	{
		display_error(cmd->command, strerror(errno));
		return (CMD_NOT_EXECUTABLE_ERROR);
	}
	return (EXIT_SUCCESS);
}
