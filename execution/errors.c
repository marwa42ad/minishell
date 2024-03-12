/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:00:09 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/09 10:23:45 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Joins two strings together, freeing the previous string.
	Returns the new concatenated string. Or NULL if an error occured.
*/
char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (add == NULL)
		return (str);
	if (str == NULL)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_pointer(tmp);
	return (str);
}

/* add_detail_quotes:
Checks whether to add quotes around the error detail:
i.e. "unset: `@': not a valid identifier"
Returns true if the command is export or unset,
false if not.
*/
static bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

void	display_detailed_err(char *command, char *detail, char *error_message)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = join_strs(msg, command);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(msg, "`");
		msg = join_strs(msg, detail);
		if (detail_quotes)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_pointer(msg);
}

void	display_error(char *command, char *error_message)
{
	display_detailed_err(command, NULL, error_message);
}

/* errmsg:
	Prints an error message that is unrelated to a specific command.
	Used in parsing phase for syntax errors.
*/
void	errmsg(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = join_strs(msg, errmsg);
	if (quotes)
		msg = join_strs(msg, " `");
	else
		msg = join_strs(msg, ": ");
	msg = join_strs(msg, detail);
	if (quotes)
		msg = join_strs(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	free_pointer(msg);
}
