/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:07:07 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 23:41:27 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_min(int a, int b)
{
	if (a >= b)
		return (b);
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	int				strlengh;
	int				min;
	unsigned int	aux;
	int				i;

	if (s == NULL)
		return (NULL);
	strlengh = ft_strlen(s);
	min = ft_min(len, (strlengh - start));
	if (min < 0)
		min = 0;
	aux = start;
	i = 0;
	ptr = (char *)malloc((min + 1) * sizeof(char));
	if (ptr == NULL || s == NULL)
		return (NULL);
	while (start < (min + aux))
	{
		ptr[i] = s[start];
		start++;
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
