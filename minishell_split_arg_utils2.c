/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split_arg_utils2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:38:45 by corellan          #+#    #+#             */
/*   Updated: 2023/03/07 19:15:26 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy_arg(char *d, char const *s, size_t size, t_sp_arg *sp)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	if (size == 0)
		return (len);
	else
	{
		while ((i < (size - 1)) && s[i] != '\0')
		{
			if (sp->t == 1 && s[i] == '\\' && (s[i + 1] == 39))
				i++;
			else if (sp->t == 2 && s[i] == '\\' && (s[i + 1] == 34))
				i++;
			d[j] = s[i];
			i++;
			j++;
		}
		d[j] = '\0';
		return (len);
	}
}

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
