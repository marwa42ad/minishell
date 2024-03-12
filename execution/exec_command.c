/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:06:04 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 16:01:33 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_config *data, t_pre_command *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND_ERROR;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = cd_builtin(data, cmd->args_array);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = echo_builtin(cmd->args_array);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = env_builtin(data, cmd->args_array);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = export_builtin(data, cmd->args_array);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = pwd_builtin(data);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = unset_builtin(data, cmd->args_array);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = exit_builtin(data, cmd->args_array);
	return (ret);
}

static void	free_env_array(char **env_array)
{
	int		len;
	char	**temp;

	len = 0;
	temp = env_array;
	if (env_array == NULL)
		return ;
	while ((*temp) != NULL)
	{
		len++;
		temp++;
	}
	while (len >= 0)
	{
		free(env_array[len]);
		len--;
	}
	free(env_array);
}

static int	execute_sys_bin(t_config *data, t_pre_command *cmd)
{
	char	**env;

	if (cmd->command == NULL || cmd->command[0] == '\0')
		return (CMD_NOT_FOUND_ERROR);
	if (cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND_ERROR);
	env = env_to_array(data);
	cmd->path = get_cmd_path(data, cmd->command);
	if (cmd->path == NULL)
	{
		free_env_array(env);
		return (CMD_NOT_FOUND_ERROR);
	}
	if (execve(cmd->path, cmd->args_array, env) == -1)
		display_error("execve", strerror(errno));
	free_env_array(env);
	while (*env)
		free(*env++);
	free(env);
	return (EXIT_FAILURE);
}

static int	execute_local_bin(t_config *data, t_pre_command *cmd)
{
	int	ret;

	ret = check_command_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->command, cmd->args_array, env_to_array(data)) == -1)
	{
		display_error("execve", strerror(errno));
		return (errno);
	}
	return (EXIT_FAILURE);
}

int	execute_command(t_config *data, t_pre_command *cmd)
{
	int	ret;

	if (cmd == NULL || cmd->command == NULL)
	{
		display_error("child",
			"parsing error: no command to execute!");
		exit_shell(data, EXIT_FAILURE);
	}
	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->pre_cmds, cmd);
	redirect_io(cmd->io_fds);
	close_fds(data->pre_cmds, false);
	if (ft_strchr(cmd->command, '/') == NULL)
	{
		ret = execute_builtin(data, cmd);
		if (ret != CMD_NOT_FOUND_ERROR)
			exit_shell(data, ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != CMD_NOT_FOUND_ERROR)
			exit_shell(data, ret);
	}
	ret = execute_local_bin(data, cmd);
	exit_shell(data, ret);
	return (ret);
}
