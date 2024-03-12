/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:40:22 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/09 12:24:01 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_code(t_config *data, char *arg, bool *error)
{
	unsigned long long	i;

	if (arg == NULL)
		return (data->error_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

static bool	is_quiet_mode(t_config *data)
{
	t_pre_command	*cmd;

	cmd = data->pre_cmds;
	if (!cmd)
		return (false);
	if (cmd->next != NULL || cmd->prev != NULL)
		return (true);
	return (false);
}

int	process_exit_error(char *const *args)
{
	int	exit_code;

	exit_code = 2;
	write(2, "exit\n", 5);
	display_detailed_err("exit", args[1], "numeric argument required");
	return (exit_code);
}

static int	exit_builtin1(t_config *data, char **args)
{
	int		exit_code;
	bool	error;

	error = false;
	exit_code = 0;
	exit_code = get_exit_code(data, args[1], &error);
	if (error)
		exit_code = process_exit_error(args);
	else if (args[2])
	{
		write(2, "exit\n", 5);
		return (display_error("exit", "too many arguments"), 1);
	}
	return (exit_shell(data, exit_code), 2);
}

int	exit_builtin(t_config *data, char **args)
{
	int		exit_code;
	bool	quiet;

	exit_code = 0;
	quiet = is_quiet_mode(data);
	if (!quiet && data->is_interactive)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
	{
		exit_code = data->error_code;
		write(2, "exit\n", 5);
	}
	else
		exit_builtin1(data, args);
	if (exit_code != 2)
		write(2, "exit\n", 5);
	return (exit_shell(data, exit_code), 2);
}
