/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:30:27 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/08 15:05:23 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	change_current_directory(t_config *data, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (ret == NULL)
	{
		display_detailed_err("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno));
		ret = ft_strjoin(data->working_dir, "/");
		tmp = ret;
		ret = ft_strjoin(tmp, path);
		free_pointer(tmp);
	}
	else
		ret = ft_strdup(cwd);
	update_wds(data, ret);
	return (true);
}

int	cd_to_home(t_config *config)
{
	char	*path;

	path = ft_retrieve_env_value(config, HOME_ENV);
	if (path == NULL || *path == '\0' || ft_isspace(*path))
	{
		display_error("cd", "HOME not set");
		return (EXIT_FAILURE);
	}
	return (!change_current_directory(config, path));
}

int	cd_to_old_pwd(t_config *config)
{
	char	*path;

	path = ft_retrieve_env_value(config, OLD_PWD_ENV);
	if (!path)
	{
		display_error("cd", "OLDPWD not set");
		return (EXIT_FAILURE);
	}
	return (!change_current_directory(config, path));
}

int	cd_builtin(t_config *config, char **args)
{
	if (is_dest_home(args) == true)
		return (cd_to_home(config));
	if (args[2] != NULL)
	{
		display_detailed_err("cd", args[1], "No such file or directory");
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
		return (cd_to_old_pwd(config));
	return (!change_current_directory(config, args[1]));
}
