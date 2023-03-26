/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 20:06:30 by corellan          #+#    #+#             */
/*   Updated: 2023/03/23 14:55:06 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This function frees the t_lexer list.*/

void	ft_free_list_lexer(t_lexer **lst)
{
	t_lexer	*temp;
	t_lexer	*temp2;

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

/*This function adds a new node to the t_lexer linked list.*/

static t_lexer	*ft_listnew_lexer(int content, int index)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (new == NULL)
		return (NULL);
	new->token = content;
	new->i_split = index;
	new->next = NULL;
	return (new);
}

/*This function adds the number num as a last node of the list.*/

void	ft_add_to_list_lexer(t_lexer **begin, int num, int index)
{
	t_lexer	*new;
	t_lexer	*iter;

	iter = *begin;
	new = ft_listnew_lexer(num, index);
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

int	ft_listsize_lexer(t_lexer **lst)
{
	int			i;
	t_lexer	*temp;

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

void	ft_print_list_lexer(t_lexer **a)
{
	t_lexer	*temp;

	temp = *a;
	while (temp != NULL)
	{
		ft_printf("%d -> ", temp->token);
		temp = temp->next;
	}
	ft_printf("\n");
	temp = *a;
	while (temp != NULL)
	{
		ft_printf("%d -> ", temp->i_split);
		temp = temp->next;
	}
	ft_printf("\n");
}
