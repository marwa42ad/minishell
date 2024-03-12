/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:07:07 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 23:41:21 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	index;

	if (num == 0)
		return (0);
	index = 0;
	while (str1[index] == str2[index] && str1[index] != '\0')
	{
		if (index < (num - 1))
			index++;
		else
			return (0);
	}
	return ((unsigned char)(str1[index]) - (unsigned char)(str2[index]));
}
