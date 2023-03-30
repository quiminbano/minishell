/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_lexer_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:51:03 by corellan          #+#    #+#             */
/*   Updated: 2023/03/30 16:00:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char(const char *str, int i)
{
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	else
		return (0);
}

/*This function helps to check how many words are in the string
to split when there are single quotaations in the string.*/

int	ft_check_s_quot_lexer(char const *str, int *i)
{
	int	k;

	k = ((*i) + 1);
	while (str[k] != 39 && str[k] != '\0')
		k++;
	if (str[k] == '\0')
		return (0);
	else
		(*i) = (k);
	return (1);
}

/*This function helps to check how many words are in the string
to split when there are double quotaations in the string.*/

int	ft_check_d_quot_lexer(char const *str, int *i)
{
	int	k;

	k = ((*i) + 1);
	while (str[k] != 34 && str[k] != '\0')
	{
		if (str[k] == '\\' && str[k + 1] == 34)
			k++;
		k++;
	}
	if (str[k] == '\0')
		return (0);
	else
		(*i) = (k);
	return (1);
}

/*This function return the length, of the part of the string to be splitted, 
when the text is inside single quotation marks (''). It also set up a flag
(sp->p) to know if the string has a double quotation mark in the beginning and 
the end of the string.*/

size_t	ft_len_s_quot_lexer(char const *s, int i, int *flag)
{
	size_t	k;

	k = (i + 1);
	while (s[k] != 39 && s[k] != '\0')
		k++;
	if (s[k] == '\0')
		return (1);
	k = k + 1;
	(*flag) = 1;
	return (k);
}

/*This function return the length, of the part of the string to be splitted, 
when the text is inside double quotation marks (""). It also set up a flag
(sp->p) to know if the string has a double quotation mark in the beginning and 
the end of the string.*/

size_t	ft_len_d_quot_lexer(char const *s, int i, int *flag)
{
	size_t	k;

	k = (i + 1);
	while (s[k] != 34 && s[k] != '\0')
	{
		if (s[k] == '\\' && s[k + 1] == 34)
			k++;
		k++;
	}
	if (s[k] == '\0')
		return (1);
	k = k + 1;
	(*flag) = 1;
	return (k);
}
