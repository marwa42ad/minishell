/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:00:10 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 21:04:45 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_no_arg_commands(t_config *data)
{
	t_pre_command	*cmd;

	if (data == NULL || !data->pre_cmds)
		return ;
	cmd = data->pre_cmds;
	while (cmd && cmd->command)
	{
		if (cmd->args_array == NULL)
		{
			cmd->args_array = malloc(sizeof * cmd->args_array * 2);
			cmd->args_array[0] = ft_strdup(cmd->command);
			cmd->args_array[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->pre_cmds);
}

int	args_count(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i++;
	return (i);
}

int	validate_quote(char *s, int start, int end)
{
	int		l;
	char	p;

	if (s == NULL)
		return (0);
	l = 0;
	p = 0;
	while (start < end)
	{
		if ((s[start] == '"' || s[start] == '\'') && l == 0)
		{
			p = s[start];
			start++;
			l = 1;
		}
		if (s[start] == p)
		{
			if (l == 1)
				l = 0;
			p = 0;
		}
		start++;
	}
	return (l);
}
