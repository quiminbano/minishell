/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:09:21 by corellan          #+#    #+#             */
/*   Updated: 2023/03/21 16:34:39 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_lexer	*tok;

	tok = NULL;
	ft_tokens_recognition("<>", &tok);
	ft_print_list_lexer(&tok);
	ft_free_list_lexer(&tok);
	return (0);
}
