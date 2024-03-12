/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lexical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 22:31:51 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 21:44:36 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	checks if the quotes are properly closed.
*/

int	ft_check_quotes(char c, int quotecheck)
{
	if (c == '\'' && quotecheck == NOQUOTE)
		quotecheck = SINGLEQ;
	else if (c == '\"' && quotecheck == NOQUOTE)
		quotecheck = DOUBLEQ;
	else if (c == '\'' && quotecheck == SINGLEQ)
		quotecheck = NOQUOTE;
	else if (c == '\"' && quotecheck == DOUBLEQ)
		quotecheck = NOQUOTE;
	return (quotecheck);
}
