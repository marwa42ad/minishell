/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:47:25 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/08 22:15:02 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**decompose_argument(char *arg)
{
	char	**var_parts;
	char	*equal_index;
	int		i;

	i = 0;
	equal_index = ft_strchr(arg, '=');
	var_parts = malloc(sizeof * var_parts * (2 + 1));
	var_parts[i] = ft_substr(arg, 0, equal_index - arg);
	i = i + 1;
	var_parts[i] = ft_substr(equal_index, 1, ft_strlen(equal_index));
	i = i + 1;
	var_parts[i] = NULL;
	return (var_parts);
}

int	process_env_var(t_config *data, char *const *args, int i, char **name_value)
{
	int	ret;

	while (args[i])
	{
		if (is_valid_env(args[i]) == false)
		{
			display_detailed_err("export", args[i], "not a valid identifier");
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			name_value = decompose_argument(args[i]);
			set_env(data, ft_strdup(name_value[0]), ft_strdup(name_value[1]));
			free_str_tab(name_value);
		}
		i++;
	}
	return (ret);
}

int	ex_env_builtin(t_config *data, char **args)
{
	t_list	*env_item;
	char	*line_name;

	if (args && args[1])
	{
		display_error("env", "too many arguments");
		return (2);
	}
	if (data == NULL || data->ls_env == NULL)
		return (EXIT_FAILURE);
	env_item = data->ls_env;
	while (env_item)
	{
		write (2, "declare -x ", 11);
		line_name = ft_strjoin(env_item->name, "=");
		if (env_item->value != NULL)
			build_env_string(env_item, line_name);
		else
		{
			ft_putendl_fd(line_name, STDOUT_FILENO);
			free_pointer(line_name);
		}
		env_item = env_item->next;
	}
	return (EXIT_SUCCESS);
}

int	export_builtin(t_config *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	tmp = NULL;
	if (args[i] == NULL)
	{
		return (ex_env_builtin(data, NULL));
	}
	else
		ret = process_env_var(data, args, i, tmp);
	return (ret);
}
