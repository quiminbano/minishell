/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_args_lexer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:18:18 by corellan          #+#    #+#             */
/*   Updated: 2023/03/24 11:36:22 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_fill_list_lexer(char const *str, int i, int j, t_lexer **lex)
{
	if (str[i] == '\0')
		return ;
	else if (str[i] == '>' && str[i + 1] != '>')
		ft_add_to_list_lexer(&(*lex), RE_OUT, j);
	else if (str[i] == '<' && str[i + 1] != '<')
		ft_add_to_list_lexer(&(*lex), RE_IN, j);
	else if (str[i] == '>' && str[i + 1] == '>')
		ft_add_to_list_lexer(&(*lex), RERE_OUT, j);
	else if (str[i] == '<' && str[i + 1] == '<')
		ft_add_to_list_lexer(&(*lex), RERE_IN, j);
	else if (str[i] == '|' && str[i + 1] != '|')
		ft_add_to_list_lexer(&(*lex), PIPE, j);
	else if (str[i] == '<' && str[i + 1] == '>')
		ft_add_to_list_lexer(&(*lex), IN_OUT, j);
}

static void	ft_check_first_arg(char const *str, t_lexer **lex)
{
	if (str[0] == '\0')
		return ;
	if (str[0] == '>' && str[1] != '>')
		ft_add_to_list_lexer(&(*lex), RE_OUT, 0);
	else if (str[0] == '<' && str[1] != '<')
		ft_add_to_list_lexer(&(*lex), RE_IN, 0);
	else if (str[0] == '>' && str[1] == '>')
		ft_add_to_list_lexer(&(*lex), RERE_OUT, 0);
	else if (str[0] == '<' && str[1] == '<')
		ft_add_to_list_lexer(&(*lex), RERE_IN, 0);
	else if (str[0] == '<' && str[1] == '>')
		ft_add_to_list_lexer(&(*lex), IN_OUT, 0);
	else
		ft_add_to_list_lexer(&(*lex), NORM_START, 0);
}

void	ft_tokens_recognition(char const *str, t_lexer **lex)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	ft_check_first_arg(str, &(*lex));
	while (str[i] != '\0')
	{
		if (str[i] == 39 && ft_check_s_quot_lexer(str, &(i)) == 1)
			i = (i + 1 - 1);
		else if (str[i] == 34 && ft_check_d_quot_lexer(str, &(i)) == 1)
			i = (i + 1 - 1);
		else if (str[i] == '\\' && check_char(str, (i + 1)) == 1)
			i += 2;
		if ((str[i] == '\0') || (check_char(str, i) == 0 && \
			(check_char(str, (i + 1)) == 1 || str[i + 1] == '\0')))
			j++;
		if (str[i] != '\0')
			i++;
		if (k != j)
			ft_fill_list_lexer(str, i, j, &(*lex));
		k = j;
	}
}