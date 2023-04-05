/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_list2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:40:27 by corellan          #+#    #+#             */
/*   Updated: 2023/04/05 11:01:12 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_c_redic_in_a_row(t_lexer **a)
{
	t_lexer	*temp;
	int		i;

	i = 0;
	temp = (*a);
	while (temp != NULL && ((temp->token > 0 && temp->token < 5) || \
		(temp->token == 6)))
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

t_lexer	*ft_lexlast(t_lexer **lst)
{
	t_lexer	*temp;

	temp = *lst;
	if (lst == NULL || *lst == NULL)
		return (NULL);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}
