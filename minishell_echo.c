/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:00:43 by corellan          #+#    #+#             */
/*   Updated: 2023/03/08 22:06:34 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This auxiliar function helps to count how many string needs to be
processed. It also prevents some situations such as many ''''' or 
"""" written in a row to be counts as words.*/

static int	ft_incrementer_echo(const char *str, int *i, int *j, t_echo **e)
{
	if ((str[(*i)] == 39 && str[(*i) + 1] == 39) || \
		(str[(*i)] == 34 && str[(*i) + 1] == 34))
	{
		(*i) += 2;
		return (0);
	}
	else if ((str[(*i)] != 32 && str[(*i)] != 39 && str[(*i)] != 34) && \
		(str[(*i) + 1] == 32 || str[(*i) + 1] == 39 || str[(*i) + 1] == 34 || \
		str[(*i) + 1] == '\0'))
	{
		(*j)++;
		(*i)++;
		return (0);
	}
	else
	{
		if (str[(*i)] == 32)
			ft_add_to_list(&(*e), (*j));
		(*i)++;
	}
	return (0);
}

/*This function process how many string we need to process splitting
the big string.*/

static size_t	ft_wordcount_echo(char const *str, t_echo **echo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\' && ((str[i + 1] == 39) || str[i + 1] == 34))
			i += 1;
		else if (str[i] == 39 && ft_check_single_quot(str, &(i), &(j)) == 1)
			continue ;
		else if (str[(i)] == 34 && ft_check_double_quot(str, &(i), &(i)) == 1)
			continue ;
		ft_incrementer_echo(str, &i, &j, &(*echo));
	}
	return (j);
}

static int	ft_second_arg_echo_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	return (i);
}

static void	ft_echo_aux(char **array, t_echo **begin, int i)
{
	t_echo	*echo;

	echo = (*begin);
	if (echo != NULL)
		echo = echo->next;
	if (ft_second_arg_echo_check(array[1]) < (int)ft_strlen(array[1]))
	{
		write(1, array[1], ft_strlen(array[1]));
		if (echo != NULL)
		{
			if (2 == echo->pos)
				write(1, " ", 1);
		}
	}
	while (array[i] != NULL)
	{
		write(1, array[i], ft_strlen(array[i]));
		if (array[i + 1] != NULL && i == echo->pos)
			write(1, " ", 1);
		i++;
		if (echo != NULL)
			echo = echo->next;
	}
}

int	ft_echo(char *str)
{
	char	**array;
	int		i;
	t_echo	*echo;

	i = 2;
	echo = NULL;
	array = ft_custom_split(str);
	if (array[1] == NULL)
	{
		write(1, "\n", 1);
		ft_free_split(array);
		return (3);
	}
	ft_wordcount_echo(str, &(echo));
	ft_echo_aux(array, &echo, i);
	if (ft_second_arg_echo_check(array[1]) < (int)ft_strlen(array[1]))
		write(1, "\n", 1);
	ft_free_split(array);
	if (echo != NULL)
		ft_free_list(&echo);
	return (3);
}