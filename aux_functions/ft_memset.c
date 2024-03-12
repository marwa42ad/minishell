/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:21:27 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/02 15:42:03 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *b, int symbol, size_t len)
{
	int				i;
	unsigned char	*ptrbyte;

	i = 0;
	ptrbyte = b;
	while (i < (int)len)
	{
		ptrbyte[i] = symbol;
		i++;
	}
	return (b);
}
