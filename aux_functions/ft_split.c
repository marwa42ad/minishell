/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:30:11 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/07 12:06:51 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdup_l(const char *src, size_t len)
{
	char	*dst;
	size_t	index;

	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	index = 0;
	while (index < len)
	{
		dst[index] = src[index];
		index++;
	}
	dst[len] = '\0';
	return (dst);
}

static size_t	str_2d_len(const char *str, char sep)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && (*str == sep))
			str++;
		if (*str)
			count++;
		while (*str && !(*str == sep))
			str++;
	}
	return (count);
}

static size_t	find_char_index(const char *str, char c)
{
	size_t	index;

	index = 0;
	while (str[index] && str[index] != c)
		index++;
	return (index);
}

char	**allocate_str_array(const char *str, char c)
{
	char	**arr_str;

	arr_str = malloc(sizeof(char *) * (str_2d_len(str, c) + 1));
	if (!arr_str)
		return (NULL);
	return (arr_str);
}

char	**split_str(const char *str, char c, char **arr_str)
{
	int		index[2];
	size_t	word_len;

	ft_memset(index, 0, sizeof(index));
	while (str[index[1]])
	{
		while (str[index[1]] && str[index[1]] == c)
			index[1]++;
		if (str[index[1]])
		{
			word_len = find_char_index(&str[index[1]], c);
			arr_str[index[0]] = ft_strdup_l(&str[index[1]], word_len);
			if (!arr_str[index[0]])
			{
				while (index[0] > 0)
					free(arr_str[--index[0]]);
				free(arr_str);
				return (NULL);
			}
			index[0]++;
			index[1] += word_len;
		}
	}
	arr_str[index[0]] = NULL;
	return (arr_str);
}
