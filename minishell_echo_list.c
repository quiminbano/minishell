/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:06:30 by corellan          #+#    #+#             */
/*   Updated: 2023/03/08 21:06:20 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_list(t_echo **lst)
{
	t_echo	*temp;
	t_echo	*temp2;

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

static t_echo	*ft_listnew(int content)
{
	t_echo	*new;

	new = (t_echo *)malloc(sizeof(t_echo));
	if (new == NULL)
		return (NULL);
	new->pos = content;
	new->next = NULL;
	return (new);
}

void	ft_add_to_list(t_echo **begin, int num)
{
	t_echo	*new;
	t_echo	*iter;

	iter = *begin;
	new = ft_listnew(num);
	if (*begin == NULL)
		*begin = new;
	else
	{
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
}

int	ft_listsize(t_echo **lst)
{
	int		i;
	t_echo	*temp;

	i = 0;
	temp = *lst;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	ft_print_list(t_echo **a)
{
	t_echo	*temp;

	temp = *a;
	while (temp != NULL)
	{
		ft_printf("%d -> ", temp->pos);
		temp = temp->next;
	}
	ft_printf("\n");
}
