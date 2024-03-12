/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 10:49:45 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 11:30:00 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_pipe(t_pre_command **cmd, t_token **token)
{
	t_pre_command	*end_command;
	t_pre_command	*new_command;

	end_command = lst_last_cmd(*cmd);
	end_command->is_pipe_output = true;
	new_command = lst_new_command(false);
	lst_add_back_cmd(&end_command, new_command);
	*token = (*token)->next;
}
