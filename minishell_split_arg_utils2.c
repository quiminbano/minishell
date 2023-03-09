/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_arg_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:38:45 by corellan          #+#    #+#             */
/*   Updated: 2023/03/09 18:23:18 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*This is a modification of the ft_strlcpy from libft. It was modified to avoid
copying the \ character in certain contitions. ft_strlcpy avoid copying the \ 
character when a text starts and finish with "" and there is a \" in the middle 
of the text. It also skips the \ when a text starts and finish wirh '' and there 
is a \' in the middle of the text. Finally, it skips the \ character when the
text starts and finish with a different character than ' or ", but there is
an \0, \t or \n in the middle of the text. */

size_t	ft_strlcpy_arg(char *d, char const *s, size_t size, t_sp_arg *sp)
{
	sp->i = 0;
	sp->j = 0;
	sp->len = ft_strlen(s);
	if (size == 0)
		return (sp->len);
	else
	{
		while ((sp->i < (size - 1)) && s[sp->i] != '\0')
		{
			if (sp->t == 1 && s[sp->i] == '\\' && (s[sp->i + 1] == 39))
				(sp->i)++;
			else if (sp->t == 2 && s[sp->i] == '\\' && (s[sp->i + 1] == 34))
				(sp->i)++;
			else if (sp->t == 0 && s[sp->i] == '\\' && (s[sp->i + 1] == 't' || \
				s[sp->i + 1] == 'n' || s[sp->i + 1] == '0' || \
				s[sp->i + 1] == 39 || s[sp->i + 1] == 34))
				(sp->i)++;
			d[sp->j] = s[sp->i];
			(sp->i)++;
			(sp->j)++;
		}
		d[sp->j] = '\0';
	}
	return (sp->len);
}

/*This function frees the split created in case of error*/

char	**ft_custom_split_free(char **array, size_t i)
{
	while (i > 0)
	{
		free(array[i--]);
		array[i] = NULL;
	}
	free(array);
	return (NULL);
}
