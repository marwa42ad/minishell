/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:28:13 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 13:29:59 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_option_set(char *arg)
{
	int	n;

	n = 0;
	if (arg[n] != '-')
		return (false);
	n++;
	while (arg[n] && arg[n] == 'n')
		n++;
	if (arg[n] == '\0')
		return (true);
	return (false);
}

void	print_output(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

static void	print_echo_arguments(char *const *args,
	bool has_n_option, int arg_num)
{
	ft_putstr_fd(args[arg_num], STDOUT_FILENO);
	if (args[arg_num + 1])
		print_output(' ');
	else if (!args[arg_num + 1] && (has_n_option == false))
		print_output('\n');
}

static void	echo_print_args(char **args, bool has_n_option, int arg_num)
{
	if (args[arg_num] == NULL)
	{
		if (has_n_option == false)
			print_output('\n');
		return ;
	}
	else
	{
		while (args[arg_num] != NULL)
		{
			print_echo_arguments(args, has_n_option, arg_num);
			arg_num++;
		}
	}
}

int	echo_builtin(char **args)
{
	int		arg_num;
	bool	n_flag;

	n_flag = false;
	arg_num = 1;
	while (args[arg_num] && is_n_option_set(args[arg_num]))
	{
		n_flag = true;
		arg_num++;
	}
	echo_print_args(args, n_flag, arg_num);
	return (EXIT_SUCCESS);
}
