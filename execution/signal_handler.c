/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:15:39 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/08 22:15:33 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
In is_interactive mode:
◦ ctrl-C displays a new prompt on a new line.
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing.
*/

void	ft_new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_handle_control_c(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = ft_new_prompt;
	sigaction(SIGINT, &signal, NULL);
}

void	ft_handle_control_d(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = ft_exit;
	sigaction(SIGQUIT, &signal, NULL);
}

void	ft_handle_control_backslash(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal, NULL);
}

void	ft_set_signal_handlers(t_config *config)
{
	get_config_instance(config);
	ft_handle_control_c();
	ft_handle_control_d();
	ft_handle_control_backslash();
}
