/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:01:50 by corellan          #+#    #+#             */
/*   Updated: 2023/03/07 19:21:39 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strlen_char(char const *str, size_t *sto, t_sp_arg *sp)
{
	size_t	i;

	i = 0;
	sp->p = 0;
	sp->q = 0;
	sp->t = 0;
	if (str[i] == 39)
		i = ft_len_single_quot(str, &(*sto), &(*sp));
	else if (str[i] == 34)
		i = ft_len_double_quot(str, &(*sto), &(*sp));
	if (sp->p == 0)
	{
		while ((str[i] != 32 && str[i] != 39 && str[i] != 34) && \
			(str[i] != '\0'))
		{
			if (str[i] == '\\' && (str[i + 1] == 39 || str[i + 1] == 34))
			{
				i += 2;
				sp->q += 1;
				continue ;
			}
			i++;
		}
	}
	return (i - (sp->q));
}

static int	ft_incrementer_wc(const char *str, int *i, int *j)
{
	if (str[(*i)] == '\\' && str[(*i) + 1] == 39)
		(*i) += 1;
	else if (str[(*i)] == '\\' && str[(*i) + 1] == 34)
		(*i) += 1;
	else if (str[(*i)] == 39 && ft_check_single_quot(str, &(*i), &(*j)) == 1)
		return (0);
	else if (str[(*i)] == 34 && ft_check_double_quot(str, &(*i), &(*j)) == 1)
		return (0);
	if ((str[(*i)] == 39 && str[(*i) + 1] == 39) || \
		(str[(*i)] == 34 && str[(*i) + 1] == 34))
	{
		(*i) += 2;
		return (0);
	}
	else if (str[(*i)] != 32 && (str[(*i) + 1] == 32 || str[(*i) + 1] == '\0'))
	{
		(*j)++;
		(*i)++;
		return (0);
	}
	else
		(*i)++;
	return (0);
}

static size_t	ft_wordcount(char const *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
		ft_incrementer_wc(str, &i, &j);
	return (j);
}

static char	**ft_custom_split_aux(char const *s, char **ar, size_t sto)
{
	size_t		temp;
	size_t		character;
	t_sp_arg	sp;
	size_t		i;

	i = 0;
	sp.p = 0;
	sp.q = 0;
	sp.t = 0;
	while (i < ft_wordcount(s))
	{
		temp = ft_strlen_char((s + sto), &sto, &sp);
		character = ft_count_char_arg((s + sto + temp + sp.p + sp.q));
		ar[i] = (char *)malloc(sizeof(char) * (temp + 1));
		if (ar[i] == NULL)
			return (ft_custom_split_free(ar, i));
		ft_strlcpy_arg(ar[i++], (s + sto), (temp + sp.q + 1), &sp);
		sto = sto + (temp + character + sp.p + sp.q);
	}
	ar[i] = NULL;
	return (ar);
}

char	**ft_custom_split(char const *s)
{
	char	**array;
	size_t	i;
	size_t	store;

	i = ft_wordcount(s);
	store = ft_count_char_arg(s);
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (array == NULL)
		return (NULL);
	return (ft_custom_split_aux(s, array, store));
}
