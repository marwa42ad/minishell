/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:52:06 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/09 10:23:25 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_str_output(char *str)
{
	ft_putendl_fd(str, STDOUT_FILENO);
}

int	pwd_builtin(t_config *config)
{
	char	path_name[PATH_MAX];
	char	*cwd_name;

	if (config->working_dir != NULL)
	{
		print_str_output(config->working_dir);
		return (EXIT_SUCCESS);
	}
	cwd_name = getcwd(path_name, PATH_MAX);
	if (cwd_name != NULL)
	{
		print_str_output(cwd_name);
		return (EXIT_SUCCESS);
	}
	display_error("pwd", strerror(errno));
	return (EXIT_FAILURE);
}
