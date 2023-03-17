/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_args_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:06:30 by corellan          #+#    #+#             */
/*   Updated: 2023/03/17 15:11:53 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function frees the t_echo list.*/

void	ft_free_list_args(t_args **lst)
{
	t_args	*temp;
	t_args	*temp2;

	temp2 = (*lst)->next;
	temp = (*lst);
	while (temp->next != NULL)
	{
		free(temp);
		temp = temp2;
		temp2 = temp2->next;
	}
	free(temp);
}

/*This function adds a new node to the t_echo linked list.*/

static t_args	*ft_listnew_args(int content)
{
	t_args	*new;

	new = (t_args *)malloc(sizeof(t_args));
	if (new == NULL)
		return (NULL);
	new->pos = content;
	new->next = NULL;
	return (new);
}

/*This function adds the number num as a last node of the list.*/

void	ft_add_to_list_args(t_args **begin, int num)
{
	t_args	*new;
	t_args	*iter;

	iter = *begin;
	new = ft_listnew_args(num);
	if (*begin == NULL)
		*begin = new;
	else
	{
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
}

/*This function measure the length of the list.*/

int	ft_listsize_args(t_args **lst)
{
	int		i;
	t_args	*temp;

	i = 0;
	temp = *lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

/*This function prints every member of the list. This function was made to
debug.*/

void	ft_print_list_args(t_args **a)
{
	t_args	*temp;

	temp = *a;
	while (temp != NULL)
	{
		ft_printf("%d -> ", temp->pos);
		temp = temp->next;
	}
	ft_printf("\n");
}
