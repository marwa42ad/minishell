/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:30:35 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/28 21:16:25 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This function will get the currently working directory and store it.
	The fisrt value of OLDPWD is the current working directory.
*/
void	init_wd(t_config *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->working_dir = ft_strdup(wd);
	if (data->working_dir == NULL)
		return ;
	if (ft_retrieve_env_value(data, "OLDPWD") != NULL)
	{
		data->old_working_dir = \
		ft_strdup(ft_retrieve_env_value(data, "OLDPWD"));
		if (data->old_working_dir == NULL)
			return ;
	}
	else
	{
		data->old_working_dir = ft_strdup(wd);
		if (data->old_working_dir == NULL)
			return ;
	}
	return ;
}
