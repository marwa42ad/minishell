/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:57:09 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 21:21:43 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_eof(t_config *config)
{
	t_token	*token;

	token = config->token_list;
	if (token->type == END_OF_FILE)
		return (0);
	else
		return (-1);
}

static void	process_token(t_token *token)
{
	int	i;

	i = 0;
	while (token->token[i] != '\0')
	{
		if (token->token[i] == '$')
		{
			if (token->prev != NULL && token->prev->type == REDIR_HERE_DOC)
				break ;
			if (strcmp(token->token, "\"$\"") != 0)
				token->type = VAR;
			break ;
		}
		i++;
	}
	i = 0;
}

bool	ft_validate_token(t_config *config)
{
	t_token	*token;

	token = config->token_list;
	if (token->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (false);
	}
	if (check_pipe_and_redir(config) == false)
		return (false);
	while (token != NULL)
	{
		process_token(token);
		token = token->next;
	}
	return (true);
}

int	ft_parse_input(t_config *config)
{
	if (config->command_input == NULL)
		exit_builtin(config, NULL);
	if (config->command_input[0] == '\0')
		return (0);
	if (ft_only_spaces(config->command_input) == 1)
		return (0);
	add_history(config->command_input);
	if (ft_tokenization(config) == false)
		return (-1);
	if (ft_check_eof(config) == true)
		return (-1);
	if (ft_validate_token(config) == false)
		return (-1);
	ft_expand_all_variables(config);
	ft_quotes_removal(config);
	ft_build_commands(config);
	return (0);
}

int	ft_get_separator(char *str, int i)
{
	if (((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (REDIR_HERE_DOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (REDIR_APPEND);
	else if (str[i] == '<')
		return (REDIR_IN);
	else if (str[i] == '>')
		return (REDIR_OUT);
	else if (str[i] == '\0')
		return (END_OF_FILE);
	else
		return (0);
}

/*
void print_token(t_token *token)
{
	t_token *temp;
	int i = 0;
	temp = token;
	while (temp)
	{
		printf("token %d\n", i++);
		printf("str: %s\n", temp->token);
		printf("type: %d\n", temp->type);
		printf("status: %d\n", temp->status);
		printf("############################");
		temp = temp->next;
	}
}
*/

/*
if (strcmp(token->token, "\"$\"") != 0)
This is to a avoid setting this case "$" as a VAR
*/