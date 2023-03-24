/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:01:50 by corellan          #+#    #+#             */
/*   Updated: 2023/03/24 17:18:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function counts the length of the strings to be processed. The number to
be returned depends of the kind of string to be processed.*/

static size_t	ft_strlen_char(char const *str, size_t *sto, t_sp_arg *sp)
{
	size_t	i;

	i = 0;
	if (str[i] == 39)
		i = ft_len_single_quot(str, &(*sto), &(*sp));
	else if (str[i] == 34)
		i = ft_len_double_quot(str, &(*sto), &(*sp));
	if (sp->p == 0)
	{
		sp->q = 0;
		while ((str[i] != 32 && str[i] != 39 && str[i] != 34) && \
			(str[i] != '\0'))
		{
			if (str[i] == '\\' && (str[i + 1] != 124 && str[i + 1] != 60 && \
				str[i + 1] != 62 && str[i + 1] != '\0'))
			{
				i += 1;
				sp->q += 1;
			}
			i++;
		}
	}
	return (i - (sp->q));
}

/*This auxiliar function helps to count how many string needs to be
processed. It also prevents some situations such as many ''''' or 
"""" written in a row to be counts as words.*/

static int	ft_incrementer_wc(const char *str, int *i, int *j)
{
	if ((str[(*i)] == 39 && str[(*i) + 1] == 39) || \
		(str[(*i)] == 34 && str[(*i) + 1] == 34))
	{
		(*i) += 2;
		return (0);
	}
	if ((str[(*i)] != 32 && str[(*i)] != 39 && str[(*i)] != 34) && \
		(str[(*i) + 1] == 32 || str[(*i) + 1] == 39 || str[(*i) + 1] == 34 || \
		str[(*i) + 1] == '\0'))
	{
		(*j)++;
		(*i)++;
		return (0);
	}
	else
	{
		if ((check_char_now(str, (*i)) == 1) && \
			(check_char_after(str, ((*i) + 1)) == 1))
			(*j)++;
		(*i)++;
	}
	return (0);
}

/*This function process how many string we need to process splitting
the big string.*/

static size_t	ft_wordcount(char const *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && ((str[i + 1] == 39) || str[i + 1] == 34))
			i += 1;
		else if (str[i] == 39 && ft_check_single_quot(str, &i, &j) == 1)
			continue ;
		else if (str[i] == 34 && ft_check_double_quot(str, &i, &j) == 1)
			continue ;
		ft_incrementer_wc(str, &i, &j);
	}
	return (j);
}

/*This function processes and allocates the needed amount of memory
to create every string after spliting. temp counts how many characters
are gonna be written per string. character counts how many characters
should be skipped to process the following string. sto helps to skip
characters to process the next string. sp.p, sp.q, and sp.q helps to
handle edge cases such as text between "" or '' (sp.p), if there is
an \ character to be skipped (sp.q) or the kind of text to be handled
(sp.t). */

static char	**ft_custom_split_aux(char const *s, char **ar, size_t sto)
{
	size_t		temp;
	size_t		character;
	t_sp_arg	sp;
	size_t		i;

	i = 0;
	while (i < ft_wordcount(s))
	{
		sp.p = 0;
		sp.q = 0;
		sp.t = 0;
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

/*This function initialize the 2D-array to split the text*/

char	**ft_custom_split(char const *s)
{
	char	**array;
	size_t	i;
	size_t	store;

	i = ft_wordcount(s);
	printf("%zu\n", i);
	store = ft_count_char_arg(s);
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (array == NULL)
		return (NULL);
	return (ft_custom_split_aux(s, array, store));
}
