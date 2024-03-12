/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:29:26 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/09 10:23:59 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_command(t_config *config, t_token *token)
{
	t_pre_command	*cmd;

	if (token == config->token_list)
	{
		cmd = lst_new_command(false);
		lst_add_back_cmd(&config->pre_cmds, cmd);
	}
	if (token->type == PIPE)
	{
		cmd = lst_new_command(false);
		lst_add_back_cmd(&config->pre_cmds, cmd);
	}
}

void	ft_build_commands(t_config *config)
{
	t_token	*token;

	token = config->token_list;
	if (token->type == END_OF_FILE)
		return ;
	while (token->next != NULL)
	{
		if (token == config->token_list)
			lst_add_back_cmd(&config->pre_cmds, lst_new_command(false));
		if (token->type == WORD || token->type == VAR)
			syntax_word(&config->pre_cmds, &token);
		else if (token->type == PIPE)
			syntax_pipe(&config->pre_cmds, &token);
		else if (token->type == REDIR_IN)
			syntax_redir_in(&config->pre_cmds, &token);
		else if (token->type == REDIR_OUT)
			syntax_redir_out(&config->pre_cmds, &token);
		else if (token->type == REDIR_APPEND)
			syntax_append(&config->pre_cmds, &token);
		else if (token->type == REDIR_HERE_DOC)
			syntax_here_doc(config, &config->pre_cmds, &token);
		else if (token->type == END_OF_FILE)
			break ;
	}
	prep_no_arg_commands(config);
}

static void	validate_pipes(char *str, int index, int len, int *error)
{
	if (str[index] == '|' && (str[index + 1] == '|')
		&& validate_quote(str, 0, index) == 0)
	{
		if (len - index == 2)
			*error = 1;
		*error = 1;
	}
	else if (str[index] == '|' && len - index == 1)
		*error = 1;
	else if (str[index] == '|' && index == 0)
		*error = 1;
	else if (ft_strlen(&str[index]) >= 3)
		if (str[index] == '|' && str[index + 1] == ' ' && str[index + 2] == '|')
			*error = 1;
	if (index > 0)
		if (str[index] == '|' && (str[index - 1] == '<'
				|| str[index - 1] == '>')
			&& validate_quote(str, 0, index) == 0)
			*error = 1;
}

static void	validate_redir(char *str, int i, int len, int *error)
{
	if (str[i] == '<' && str[i + 1] == '<' && validate_quote(str, 0, i) == 0)
	{
		if (len - i == 2)
			*error = 1;
		else if ((str[i + 2] == '<' || str[i + 2] == '>')
			&& validate_quote(str, 0, i) == 0)
			*error = 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>'
		&& validate_quote(str, 0, i) == 0)
	{
		if (len - i == 2)
			*error = 1;
		else if ((str[i + 2] == '<' || str[i + 2] == '>')
			&& validate_quote(str, 0, i) == 0)
			*error = 1;
	}
	else if ((str[i] == '>' || str[i] == '<')
		&& len - i == 1 && validate_quote(str, 0, i) == 0)
		*error = 1;
	else if ((((str[i] == '>' || str[i] == '<') && str[i + 1] == ' ' \
	&& (str[i + 2] == '>' || str[i + 2] == '<')) || ((str[i] == '>' \
	|| str[i] == '<') && (str[i + 1] == '>' || str[i + 1] == '<'))) \
	&& validate_quote(str, 0, i + 2) == 0)
		*error = 1;
}

int	check_pipe_and_redir(t_config *config)
{
	char	*str;
	int		index;
	int		len;
	int		error;

	str = ft_strdup(config->command_input);
	index = 0;
	len = ft_strlen(str);
	error = 0;
	while (index < len && error == 0)
	{
		validate_pipes(str, index, len, &error);
		validate_redir(str, index, len, &error);
		index++;
	}
	free(str);
	if (error == 1)
	{
		printf("syntax error near unexpected token\n");
		return (false);
	}
	return (true);
}
