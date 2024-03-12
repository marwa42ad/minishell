/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:45:03 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 21:48:23 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks access and permissions for each command path to find
a valid path to binay files for a command.
Returns the valid path to a command binary or NULL if no valid path is found.
*/
static char	*find_valid_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (cmd_path == NULL)
		{
			display_error("malloc", "an unexpected error occured");
			return (NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_pointer(cmd_path);
		i++;
	}
	return (NULL);
}

/* get_paths_from_env:
*	Attempts to extract paths from the PATH environment variable.
*	Returns an array of paths on success. On failure, returns NULL.
*/
static char	**get_paths_from_env(t_config *data)
{
	char	**env_paths;
	char	*path_value;

	path_value = ft_retrieve_env_value(data, "PATH");
	if (path_value == NULL)
		return (NULL);
	env_paths = ft_split(path_value, ':');
	return (env_paths);
}

/* get_cmd_path:
*	Searches the PATH environment variable for the location of the given
*	command's binary file.
*	Returns the path to the command binary file. NULL if no valid path
*	is found.
*/
char	*get_cmd_path(t_config *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (name == NULL)
		return (NULL);
	env_paths = get_paths_from_env(data);
	if (env_paths == NULL)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (cmd == NULL)
	{
		free_str_tab(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	if (cmd_path == NULL)
	{
		free_pointer(cmd);
		free_str_tab(env_paths);
		return (NULL);
	}
	return (cmd_path);
}
