/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_lexer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:01:50 by corellan          #+#    #+#             */
/*   Updated: 2023/03/20 18:05:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_char(char const *str)
{
	size_t	i;

	i = 0;
	while (check_char(str, i) == 1)
	{
		i++;
	}
	return (i);
}

static size_t	ft_strlen_char(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && check_char(str, i) == 0)
	{
		if (str[i] == 39)
			i = ft_len_s_quot_lexer(str, i);
		else if (str[i] == 34)
			i = ft_len_d_quot_lexer(str, i);
		else
			i++;
	}
	return (i);
}

static size_t	ft_wordcount(char const *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39 && ft_check_s_quot_lexer(str, &(i)) == 1)
			i = (i + 1 - 1);
		else if (str[i] == 34 && ft_check_d_quot_lexer(str, &(i)) == 1)
			i = (i + 1 - 1);
		else if (str[i] == '\\' && check_char(str, (i + 1)) == 1)
			i += 2;
		if (check_char(str, i) == 0 && (check_char(str, (i + 1)) == 1 \
			|| str[i + 1] == '\0'))
			j++;
		i++;
	}
	return ((size_t)j);
}

static char	**ft_split_free(char **array, size_t i)
{
	while (i > 0)
	{
		free(array[i--]);
		array[i] = NULL;
	}
	free(array);
	return (NULL);
}

char	**ft_split_lexer(char const *s)
{
	char	**array;
	size_t	i;
	size_t	temp;
	size_t	character;
	size_t	store;

	i = ft_wordcount(s);
	store = ft_count_char(s);
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < ft_wordcount(s))
	{
		temp = ft_strlen_char((s + store));
		character = ft_count_char((s + store + temp));
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
