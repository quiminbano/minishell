/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_argc2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:19:28 by corellan          #+#    #+#             */
/*   Updated: 2023/04/05 14:38:11 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_here_doc(char ***arr, t_lexer **lex, t_env *env)
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
		i++;
		temp = temp->next;
	}
}