/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:25:53 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/27 11:25:08 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	convert_tokens_to_args(char **args_array, t_token *temp, int *i)
{
	while (temp != NULL && (temp->type == WORD || temp->type == VAR))
	{
		args_array[*i] = ft_strdup(temp->token);
		temp = temp->next;
		(*i)++;
	}
	args_array[*i] = NULL;
}

static char	**build_argument_array(
	int len, char **args_array, t_pre_command *cmd, t_token **token_lst)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *token_lst;
	while (i < len)
	{
		args_array[i] = cmd->args_array[i];
		i++;
	}
	convert_tokens_to_args(args_array, temp, &i);
	return (args_array);
}

int	add_arguments(t_token **token_lst, t_pre_command *cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

	i = 0;
	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (cmd->args_array[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (new_tab == NULL)
		return (-1);
	new_tab = build_argument_array(len, new_tab, cmd, token_lst);
	free_pointer(cmd->args_array);
	cmd->args_array = new_tab;
	*token_lst = temp;
	return (0);
}

int	create_arguments(t_token **token_lst, t_pre_command *cmd)
{
	int		i;
	int		nb;
	t_token	*temp;

	i = 0;
	temp = *token_lst;
	nb = count_arguments(temp);
	cmd->args_array = malloc(sizeof(char *) * (nb + 2));
	if (cmd->args_array == NULL)
		return (-1);
	temp = *token_lst;
	i = 0;
	cmd->args_array[i] = ft_strdup(cmd->command);
	i++;
	while (temp->type == WORD || temp->type == VAR)
	{
		cmd->args_array[i] = ft_strdup(temp->token);
		i++;
		temp = temp->next;
	}
	cmd->args_array[i] = NULL;
	*token_lst = temp;
	return (0);
}

int	set_arguments(t_token **token_lst, t_pre_command *cmd)
{
	int	operation_status;

	operation_status = 0;
	if (cmd != NULL && cmd->args_array == NULL)
		operation_status = create_arguments(token_lst, cmd);
	else
		operation_status = add_arguments(token_lst, cmd);
	return (operation_status);
}
