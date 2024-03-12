/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_outfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:32:16 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 15:18:02 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_infile_outfile(t_in_outfiles *inout)
{
	if (inout == NULL
		|| (inout->infile == NULL && inout->outfile == NULL))
		return (true);
	if ((inout->infile != NULL && inout->fd_in == -1)
		|| (inout->outfile != NULL && inout->fd_out == -1))
		return (false);
	return (true);
}
