/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:49:39 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/09 11:09:12 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exit(t_config *config)
{
	int	code;

	code = config->error_code;
	write(2, "exit\n", 5);
	ft_lstclear(&config->ls_env);
	ft_lstclear(&config->ls_exp);
	free_config(config);
	free_pointer(config->working_dir);
	free_pointer(config->old_working_dir);
	exit(code);
}

void	minishell_interactive(t_config *config)
{
	while (1)
	{
		ft_set_signal_handlers(config);
		config->command_input = readline(PROMPT);
		if ((ft_strlen(config->command_input) == 4
				&& !ft_strncmp("exit", config->command_input, 4))
			|| !config->command_input)
			ms_exit(config);
		ft_parse_input(config);
		if (lst_size_cmd(config->pre_cmds) > 0)
			config->error_code = ms_execute(config);
		free_config(config);
	}
}

void	minishell_noninteractive(t_config *config)
{
	char	**arg_input;
	int		i;

	i = 0;
	arg_input = ft_split(config->command_input, ';');
	free_pointer(config->command_input);
	if (arg_input == NULL)
	{
		printf("no argument specified");
		ms_exit(config);
	}
	while (arg_input[i])
	{
		config->command_input = arg_input[i++];
		if ((ft_strlen(config->command_input) == 4
				&& !ft_strncmp("exit", config->command_input, 4))
			|| !config->command_input)
			ms_exit(config);
		ft_parse_input(config);
		if (lst_size_cmd(config->pre_cmds) > 0)
			config->error_code = ms_execute(config);
		free_config(config);
	}
	exit(config->error_code);
}

void	ft_minishell(t_config *config, bool interactive)
{
	if (interactive == true)
		minishell_interactive(config);
	else
		minishell_noninteractive(config);
}

int	main(int ac, char **av, char **env)
{
	t_config	config;
	bool		interactive;

	interactive = true;
	ft_memset(&config, 0, sizeof(t_config));
	config.pre_cmds = NULL;
	config.command_input = NULL;
	config.token_list = NULL;
	config.process_id = -1;
	config.error_code = 0;
	if (ac >= 3)
	{
		interactive = false;
		config.command_input = ft_strdup(av[2]);
	}
	init_env(env, &config);
	init_wd(&config);
	ft_minishell(&config, interactive);
	return (0);
}

/*
	It is necessary to create the main with 3 arguments: ac, av and env;
	env: is for the enviroment variables;
*/
