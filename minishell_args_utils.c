/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_args_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:23:24 by corellan          #+#    #+#             */
/*   Updated: 2023/03/24 16:52:57 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function is similar to ft_check_single_quot. The difference in this one
is, ft_check_s_quot_args add the value of (*j) to the t_args linked list if
there is an space after the ' character in the string splitted. */

static int	ft_check_s_quot_args(char const *str, int *i, int *j, t_args **ar)
{
	int	k;

	k = ((*i) + 1);
	if (str[k] == 39)
		return (0);
	while (str[k] != 39 && str[k] != '\0')
		k++;
	if (str[k] == '\0')
		return (0);
	else
	{
		(*i) = (k + 1);
		(*j) += 1;
		if (str[(*i)] == 32 || str[(*i)] == '\0')
			ft_add_to_list_args(&(*ar), (*j));
	}
	return (1);
}

/*This function is similar to ft_check_single_quot. The difference in this one
is, ft_check_s_quot_args add the value of (*j) to the t_args linked list if
there is an space after the " character in the string splitted. */

static int	ft_check_d_quot_args(char const *str, int *i, int *j, t_args **ar)
{
	int	k;

	k = ((*i) + 1);
	if (str[k] == 34)
		return (0);
	while (str[k] != 34 && str[k] != '\0')
	{
		if (str[k] == '\\' && str[k + 1] == 34)
			k++;
		k++;
	}
	if (str[k] == '\0')
		return (0);
	else
	{
		(*i) = (k + 1);
		(*j) += 1;
		if (str[(*i)] == 32 || str[(*i)] == '\0')
			ft_add_to_list_args(&(*ar), (*j));
	}
	return (1);
}

static void	ft_increment_args_aux(const char *str, int *i, int *j, t_args **ar)
{
	if ((check_char_now(str, (*i)) == 1) && \
		(check_char_after(str, ((*i) + 1)) == 1))
	{
		(*j)++;
		if (str[(*i) + 1] == ' ' || str[(*i) + 1] == '\0')
			ft_add_to_list_args(&(*ar), (*j));
	}
	(*i)++;
}

/*This auxiliar function is similar to ft_incrementer in the ft_custom_split.
The difference between them are that, We store the value of word where it is
an space character (*j) in t. We store this value in the list t_args. We do 
that with the ft_add_to_list function. */

static int	ft_incrementer_args(const char *str, int *i, int *j, t_args **ar)
{
	if ((str[(*i)] == 39 && str[(*i) + 1] == 39) || \
		(str[(*i)] == 34 && str[(*i) + 1] == 34))
	{
		(*i) += 2;
		if (str[(*i)] == 32 || str[(*i)] == '\0')
			ft_add_to_list_args(&(*ar), (*j));
		return (0);
	}
	else if ((str[(*i)] != 32 && str[(*i)] != 39 && str[(*i)] != 34) && \
		(str[(*i) + 1] == 32 || str[(*i) + 1] == 39 || str[(*i) + 1] == 34 || \
		str[(*i) + 1] == '\0'))
	{
		(*j)++;
		(*i)++;
		if (str[(*i)] == 32 || str[(*i)] == '\0')
			ft_add_to_list_args(&(*ar), (*j));
		return (0);
	}
	else
		ft_increment_args_aux(str, &(*i), &(*j), &(*ar));
	return (0);
}

/*This function is similar to ft_wordcount in the ft_custom_split.  The
differences between them are that, in this function we pass the linked
list (t_args) as a double pointer, to store the word value where we there is
an space character between the words.*/

size_t	ft_wordcount_args(char const *str, t_args **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && ((str[i + 1] == 39) || str[i + 1] == 34))
			i += 1;
		else if ((str[i] == 39) && \
			(ft_check_s_quot_args(str, &(i), &(j), &(*args)) == 1))
			continue ;
		else if ((str[(i)] == 34) && \
			(ft_check_d_quot_args(str, &(i), &(j), &(*args)) == 1))
			continue ;
		ft_incrementer_args(str, &i, &j, &(*args));
	}
	return (j);
}
