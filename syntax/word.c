/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:05:04 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 11:33:53 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_first_token_or_pipe(t_token *token, t_pre_command *cmd)
{
	if (token->prev == NULL || (token->prev && token->prev->type == PIPE)
		|| cmd->command == NULL)
		return (true);
	return (false);
}

static int	has_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	free_str_array(char **str_array)
{
	int	i;

	i = 0;
	if (str_array)
	{
		while (str_array[i])
		{
			if (str_array[i])
			{
				free(str_array[i]);
				str_array[i] = NULL;
			}
			i++;
		}
		free(str_array);
		str_array = NULL;
	}
}

static void	set_cmd_var(t_pre_command *cmd, char *token)
{
	t_token		*new_tkn;
	t_token		*tmp;
	char		**cmd_parts;
	int			i;

	new_tkn = NULL;
	cmd_parts = ft_split(token, ' ');
	if (cmd_parts == NULL)
		return ;
	cmd->command = ft_strdup(cmd_parts[0]);
	i = 0;
	while (cmd_parts[++i])
	{
		if (i == 1)
		{
			new_tkn = lst_new_token(ft_strdup(cmd_parts[1]), WORD, NOQUOTE);
			tmp = new_tkn;
		}
		else
			lst_add_new_token(&new_tkn, ft_strdup(cmd_parts[i]), WORD, NOQUOTE);
	}
	lst_add_new_token(&new_tkn, NULL, END_OF_FILE, NOQUOTE);
	set_arguments(&new_tkn, cmd);
	lst_clear_token(&tmp);
	free_str_array(cmd_parts);
}

void	syntax_word(t_pre_command **command, t_token **token)
{
	t_token			*tmp;
	t_pre_command	*end_cmd;

	tmp = *token;
	while (tmp->type == WORD || tmp->type == VAR)
	{
		end_cmd = lst_last_cmd(*command);
		if (is_first_token_or_pipe(tmp, end_cmd) == true)
		{
			if (tmp->type == VAR && has_space(tmp->token) == 1)
				set_cmd_var(end_cmd, tmp->token);
			else
				end_cmd->command = ft_strdup(tmp->token);
			tmp = tmp->next;
		}
		else
			set_arguments(&tmp, end_cmd);
	}
	*token = tmp;
}
