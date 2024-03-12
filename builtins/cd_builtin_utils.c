/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:34:09 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 13:45:46 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_dest_home(char *const *args)
{
	return (args == NULL || !args[1] || ft_isspace(args[1][0])
			|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0);
}

void	update_wds(t_config *data, char *wd)
{
	set_env(data, ft_strdup("OLDPWD"),
		ft_strdup(ft_retrieve_env_value(data, "PWD")));
	set_env(data, ft_strdup("PWD"), ft_strdup(wd));
	if (data->old_working_dir)
	{
		free(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		free(data->working_dir);
		data->working_dir = ft_strdup(wd);
	}
	free(wd);
}

bool	chdir_errno_mod(char *path)
{
	if (errno == ESTALE)
		errno = ENOENT;
	display_detailed_err("cd", path, strerror(errno));
	return (false);
}
