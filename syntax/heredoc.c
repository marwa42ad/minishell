/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:33:05 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/29 14:51:14 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_has_delimiter(char *delimiter, bool *has_delimiter)
{
	int		str_len;
	char	*clean_delimiter;

	str_len = ft_strlen(delimiter);
	str_len--;
	if (delimiter != NULL && str_len > 2
		&& ((delimiter[0] == '\'' && delimiter[str_len] == '\'')
			|| (delimiter[0] == '\"' && delimiter[str_len] == '\"'))
	)
	{
		*has_delimiter = true;
		clean_delimiter = ft_strtrim(delimiter, "\'\"");
		return (clean_delimiter);
	}
	*has_delimiter = false;
	return (ft_strdup(delimiter));
}

static char	*get_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	number = ft_itoa(i);
	if (number == NULL)
		return (NULL);
	name = ft_strjoin(HEREDOC_NAME, number);
	free(number);
	i++;
	return (name);
}

bool	get_heredoc(t_config *data, t_ios *io)
{
	int		tmp_fd;
	bool	ret;

	ret = true;
	tmp_fd = open(io->infile_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ret = fill_heredoc(data, io, tmp_fd);
	close(tmp_fd);
	return (ret);
}

void	clear_delimiter(t_token *const *token, bool *has_delimiter,
						t_ios *io)
{
	char	*cleaned_delimiter;

	cleaned_delimiter = \
		check_has_delimiter((*token)->next->token, has_delimiter);
	io->heredoc_delimiter = cleaned_delimiter;
}

void	syntax_here_doc(t_config *data, t_pre_command **cmd, t_token **token)
{
	t_pre_command	*end_command;
	t_token			*temp;
	bool			has_delimiter;
	t_ios			*io;

	temp = *token;
	end_command = lst_last_cmd(*cmd);
	init_io(end_command);
	io = end_command->io_fds;
	if (!remove_old_file_ref(io, true))
		return ;
	io->infile_name = get_heredoc_name();
	if (temp->next == NULL || temp->next->token == NULL)
		heredoc_message();
	clear_delimiter(token, &has_delimiter, io);
	if (get_heredoc(data, io))
		io->fd_input = open(io->infile_name, O_RDONLY);
	else
		io->fd_input = -1;
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token = temp;
}
