/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:36:34 by pbalbino          #+#    #+#             */
/*   Updated: 2023/12/03 16:36:50 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n < 0)
		n = n * (-1);
	while (n > 9)
	{
		n = n / 10;
		len++;
	}
	return (len + 1);
}

char	*ft_allocation(long *temp, int *len)
{
	char	*str;

	str = 0;
	if (*temp < 0)
	{
		*temp = *temp * (-1);
		str = malloc((*len + 2) * sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '-';
		str[*len + 1] = 0;
	}
	else
	{
		str = malloc((*len + 1) * sizeof(char));
		if (str == NULL)
			return (NULL);
		str[(*len)--] = 0;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	temp;

	temp = n;
	len = ft_intlen((long)n);
	str = ft_allocation(&temp, &len);
	if (str == NULL)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (temp > 0)
	{
		str[len] = (temp % 10) + 48;
		temp = temp / 10;
		len--;
	}
	return (str);
}
