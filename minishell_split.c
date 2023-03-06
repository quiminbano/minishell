/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:01:50 by corellan          #+#    #+#             */
/*   Updated: 2023/03/06 19:13:37 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_char(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] == c)
	{
		i++;
	}
	return (i);
}

static size_t	ft_strlen_char(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static size_t	ft_wordcount(char const *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1] == 39)
			continue ;
		else if (str[i] == '\\' && str[i + 1] == 34)
			continue ;
		else if (str[i] == 39 && ft_check_single_quot(str, &i, &j) == 1)
			continue ;
		else if (str[i] == 34 && ft_check_double_quot(str, &i, &j) == 1)
			continue;
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static char	**ft_custom_split_free(char **array, size_t i)
{
	while (i > 0)
	{
		free(array[i--]);
		array[i] = NULL;
	}
	free(array);
	return (NULL);
}

char	**ft_custom_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	temp;
	size_t	character;
	size_t	store;

	i = ft_wordcount(s, c);
	store = ft_count_char(s, c);
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < ft_wordcount(s, c))
	{
		temp = ft_strlen_char((s + store), c);
		character = ft_count_char((s + store + temp), c);
		array[i] = (char *)malloc(sizeof(char) * (temp + 1));
		if (array[i] == NULL)
			return (ft_split_free(array, i));
		ft_strlcpy(array[i], (s + store), (temp + 1));
		store = store + (temp + character);
		i++;
	}
	array[i] = NULL;
	return (array);
}
