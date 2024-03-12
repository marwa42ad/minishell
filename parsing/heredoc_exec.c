/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 00:09:37 by alexa             #+#    #+#             */
/*   Updated: 2023/12/29 14:52:04 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free_pointer(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_pointer(tmp);
		}
	}
	free_str_tab(tab);
	return (str);
}

static char	*get_expanded_var_line(t_config *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (words == NULL)
		return (NULL);
	i = 0;
	while (words[i] != NULL)
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = var_expander_heredoc(data, words[i]);
			if (words[i] == NULL)
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

static bool	evaluate_heredoc_line(t_config *data, char **line,
			t_ios *io, bool *ret)
{
	if (*line == NULL)
	{
		display_detailed_err("warning", "here-document delimited by \
		end-of-file: wanted", io->heredoc_delimiter);
		*ret = true;
		return (false);
	}
	if (ft_strcmp(*line, io->heredoc_delimiter) == 0)
	{
		*ret = true;
		return (false);
	}
	if (io->has_heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = get_expanded_var_line(data, *line);
		if ((*line) == NULL)
		{
			free_pointer(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

bool	fill_heredoc(t_config *data, t_ios *io, int fd)
{
	char	*line;
	bool	ret;

	ret = false;
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!evaluate_heredoc_line(data, &line, io, &ret))
			break ;
		ft_putendl_fd(line, fd);
		free_pointer(line);
	}
	free_pointer(line);
	return (ret);
}
