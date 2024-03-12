/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:04:13 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 12:07:19 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split(const char *str, char c)
{
	char	**arr_str;

	if (!str)
		return (NULL);
	arr_str = allocate_str_array(str, c);
	if (!arr_str)
		return (NULL);
	return (split_str(str, c, arr_str));
}
