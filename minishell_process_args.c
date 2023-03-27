/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:13:14 by corellan          #+#    #+#             */
/*   Updated: 2023/03/27 10:33:01 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function creates a string to be in the processed 2D-array joining more 
than one string from the original 2D-array. Of course, the start of the string
needs to be created with ft_strdup.*/

static void	ft_work_in_arg_aux(char **array, int pos, int *j, char **str)
{
	int	flag;

	flag = 0;
	while ((*j) < pos)
	{
		if (flag == 0)
		{
			(*str) = ft_strdup(array[(*j)]);
			flag = 1;
		}
		else
			(*str) = ft_strjoin_free((*str), array[(*j)]);
		(*j)++;
	}
}

/*This function decides how to process the strings. if the difference between 
the number that is in the list (pos) and the index of the last string joined
from the original split in the previous iteration (*j). if the difference 
between pos and (*j) is 1, we copy the string as it is from the original
2D-array. if pos and (*j) has the same value, it means that we need to create
an empty string (because in the original line a "" or '' is comming). if
the difference between pos and (*j) is more than one, the function goes to
the ft_work_in_arg_aux. */

static char	*ft_work_in_arg(char **array, int pos, int *j)
{
	char		*str;

	if ((pos - (*j)) == 1)
	{
		str = ft_strdup(array[(*j)]);
		(*j) += 1;
		return (str);
	}
	else if (pos == (*j))
	{
		str = ft_strdup("");
		return (str);
	}
	else
		ft_work_in_arg_aux(array, pos, &(*j), &str);
	return (str);
}

/*In this function, we start to process the strings we are gonna have in our
2D-array with the command processed. We pass the element of the list to the
function ft_work_in_arg, to know how many strings from the original 2D array
we need to join to form the processed strings. */

static char	**ft_process_arg_aux(char **ar, char **tem, int len, t_args **arg)
{
	t_args	*args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = (*arg);
	while (i < len)
	{
		tem[i] = ft_work_in_arg(ar, args->pos, &j);
		if (args->next != NULL)
			args = args->next;
		i++;
	}
	args = (*arg);
	if (args != NULL)
		ft_free_list_args(&args);
	ft_free_split(ar);
	return (tem);
}

/*This function process the line in case of the arguments are separated by
"". The function casts in the linked list t_args between what indexes of the
2D array (**array) there is an space in the original string. if a number is
repeated in the linked list (for example 1->2->2->3) it means that there is
combinations of "" or '' in the middle of the text, and we need to create
empty strings in the processed 2D-array with arguments. The amount of strings
we are going to create, are gonna be the length of the linked list.*/

char	**ft_process_arg(char **array, char *str)
{
	t_args	*args;
	char	**temp;
	int		len;

	args = NULL;
	ft_wordcount_args(str, &args);
	len = ft_listsize_args(&args);
	temp = (char **)malloc(sizeof(char *) * (len + 1));
	if (temp == NULL)
		return (NULL);
	temp[len] = NULL;
	return (ft_process_arg_aux(array, temp, len, &args));
}
