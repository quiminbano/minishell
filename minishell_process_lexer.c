/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_process_lexer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:38 by corellan          #+#    #+#             */
/*   Updated: 2023/03/28 12:23:29 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_work_in_args_lexer(char **ar, char **te, int tok, t_lex_i *idx)
{
	int	*i;
	int	*j;
	int	sp;
	int	l_sstr;

	i = &(idx->i);
	j = &(idx->j);
	if ((ft_wordcount_space(ar[(*j)]) > 1) && (tok > 0 && tok < 5))
	{
		sp = ft_count_space(ar[(*j)]);
		l_sstr = ft_strlen_w_space(ar[(*j)] + sp);
		te[(*i) - 1] = ft_strjoin_free(te[(*i) - 1], (ar[(*j)] + sp + l_sstr));
		te[(*i)] = (char *)malloc(sizeof(char) * (sp + l_sstr + 1));
		if (te[(*i)] == NULL)
			return ;
		ft_strlcpy(te[(*i)], ar[(*j)], (sp + l_sstr + 1));
	}
	else
		te[(*i)] = ft_strdup(ar[(*j)]);
	(*i)++;
	(*j)++;
}

/*In this function, we start to process the strings we are gonna have in our
2D-array with the command processed. We pass the element of the list to the
function ft_work_in_arg, to know how many strings from the original 2D array
we need to join to form the processed strings. */

static char	**ft_process_lexer_aux(char **ar, char **te, int le, t_lexer **lex)
{
	t_lexer	*lexer;
	t_lex_i	idx;

	idx.i = 0;
	idx.j = 0;
	lexer = (*lex);
	if (lexer != NULL && lexer->token != 0)
		idx.i = 1;
	while (idx.i < le)
	{
		ft_work_in_args_lexer(ar, te, lexer->token, &idx);
		if (lexer->next != NULL)
			lexer = lexer->next;
	}
	lexer = (*lex);
	if (lexer != NULL)
		ft_free_list_lexer(&lexer);
	ft_free_split(ar);
	return (te);
}

/*This function process the line in case of the arguments are separated by
"". The function casts in the linked list t_args between what indexes of the
2D array (**array) there is an space in the original string. if a number is
repeated in the linked list (for example 1->2->2->3) it means that there is
combinations of "" or '' in the middle of the text, and we need to create
empty strings in the processed 2D-array with arguments. The amount of strings
we are going to create, are gonna be the length of the linked list.*/

char	**ft_process_lexer(char **arg, char *str)
{
	t_lexer	*lex;
	char	**temp;
	int		len;
	int		flag;

	lex = NULL;
	flag = 0;
	ft_tokens_recognition(str, &lex);
	len = ft_listsize_lexer(&lex);
	if (lex != NULL && lex->token != 0)
	{
		flag = 1;
		len = len + 1;
	}
	temp = (char **)malloc(sizeof(char *) * (len + 1));
	if (temp == NULL)
		return (NULL);
	temp[len] = NULL;
	if (flag == 1)
		temp[0] = ft_strdup("");
	return (ft_process_lexer_aux(arg, temp, len, &lex));
}
