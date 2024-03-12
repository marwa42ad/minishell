/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:17:36 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/26 12:56:29 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *str, int c)
{
	char	temp;

	temp = (char)c;
	while (*str != '\0')
	{
		if (*str == temp)
			return ((char *)str);
		str++;
	}
	if (*str == '\0' && temp == 0)
		return ((char *)str);
	return (NULL);
}
