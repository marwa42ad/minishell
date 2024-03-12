/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:15:10 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/09 11:08:30 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_config *data, int exno)
{
	if (data)
	{
		if (data->pre_cmds && data->pre_cmds->io_fds)
		{
			close_fds(data->pre_cmds, true);
		}
		free_data(data, true);
	}
	exit (exno);
}

void	ft_exit(int signal)
{
	t_config	*config;

	(void)signal;
	config = get_config_instance(NULL);
	exit_shell(config, 0);
}
