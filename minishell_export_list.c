/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:06:30 by corellan          #+#    #+#             */
/*   Updated: 2023/03/13 13:55:39 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function frees the t_export list.*/

void	ft_free_list_export(t_export **lst)
{
	t_export	*temp;
	t_export	*temp2;

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

/*This function adds a new node to the t_export linked list.*/

static t_export	*ft_listnew_export(int content)
{
	t_export	*new;

	new = (t_export *)malloc(sizeof(t_export));
	if (new == NULL)
		return (NULL);
	new->index = content;
	new->next = NULL;
	return (new);
}

/*This function adds the number num as a last node of the list.*/

void	ft_add_to_list_export(t_export **begin, int num)
{
	t_export	*new;
	t_export	*iter;

	iter = *begin;
	new = ft_listnew_export(num);
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

int	ft_listsize_export(t_export **lst)
{
	int			i;
	t_export	*temp;

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

void	ft_print_list_export(t_export **a)
{
	t_export	*temp;

	temp = *a;
	while (temp != NULL)
	{
		ft_printf("%d -> ", temp->index);
		temp = temp->next;
	}
	ft_printf("\n");
}
