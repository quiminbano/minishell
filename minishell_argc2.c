/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:19:28 by corellan          #+#    #+#             */
/*   Updated: 2023/04/05 16:49:20 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_here_doc(char ***arr, t_lexer **lex, t_env *env)
{
	t_lexer	*temp;
	int		i;

	temp = (*lex);
	i = 1;
	if (temp->token == 0)
		temp = temp->next;
	while (((*arr)[i] != NULL) && (temp != NULL))
	{
		if (temp->token == 3)
			here_doc(&((*arr)[i]), &(*env));
		if (g_should_process == 0)
			break ;
		i++;
		temp = temp->next;
	}
	if (g_should_process == 0)
	{
		g_should_process = 1;
		ft_free_split(*(arr));
		ft_free_list_lexer(&(*lex));
		return (1);
	}
	return (0);
}
