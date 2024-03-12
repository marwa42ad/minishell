/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:17:00 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 23:42:02 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_join;
	size_t	index;
	size_t	idx_join;

	if (s1 && !s2)
		return ((char *)s1);
	if (!s1 && s2)
		return ((char *)s2);
	if (!s1 && !s2)
		return (NULL);
	str_join = (char *)malloc(sizeof(char) * ft_strlen(s1) + sizeof(char)
			* ft_strlen(s2) + 1);
	if (!str_join)
		return (NULL);
	index = 0;
	idx_join = 0;
	while (s1[index] != '\0')
	{
		str_join[index] = s1[index];
		index++;
	}
	while (s2[idx_join] != '\0')
		str_join[index++] = s2[idx_join++];
	str_join[index] = '\0';
	return (str_join);
}
