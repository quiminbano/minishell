/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:08:15 by corellan          #+#    #+#             */
/*   Updated: 2023/04/03 12:44:50 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_d_quot(char *variable)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (variable[i] != '\0')
	{
		if (variable[i] == 34)
			j++;
		i++;
	}
	return (j);
}

static void	ft_replace_quot(char *copy, char **variable, int *i, int *j)
{
	if (copy[(*i)] == 34)
	{
		(*variable)[(*j)] = '\\';
		(*j) += 1;
	}
	(*variable)[(*j)] = copy[(*i)];
	(*i) += 1;
	(*j) += 1;
}

void	check_and_process_d_quotes(char	**variable)
{
	int		quots;
	int		len;
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quots = count_d_quot((*variable));
	if (quots == 0)
		return ;
	len = ft_strlen((*variable));
	copy = ft_strdup((*variable));
	if (copy == NULL)
		return ;
	free((*variable));
	((*variable)) = (char *)malloc(sizeof(char) * (len + quots + 1));
	if ((*variable) == NULL)
		return ;
	while (copy[i] != '\0')
		ft_replace_quot(copy, &(*variable), &i, &j);
	(*variable)[j] = '\0';
	free(copy);
}
