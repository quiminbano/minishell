/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:31:46 by corellan          #+#    #+#             */
/*   Updated: 2023/03/13 17:21:03 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_export(char *st, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (st == NULL)
	{
		write(fd, "(null)", 6);
		return ;
	}
	write(fd, "declare -x ", 11);
	while (st[i] != '\0')
	{
		ft_putchar_fd(st[i], fd);
		if (st[i] == '=')
		{
			write(fd, "\"", 1);
			flag = 1;
		}
		i++;
		if (st[i] == '\0' && flag == 1)
			write(fd, "\"", 1);		
	}
	write(fd, "\n", 1);
}

void	ft_decide_what_print(char **array, t_export **exp)
{
	t_export	*temp;
	int			temp1;

	temp = (*exp);
	while (temp->next != NULL)
	{
		if (ft_strncmp(array[temp->index], array[temp->next->index], \
			2147483647LL) > 1)
		{
			temp1 = temp->index;
			temp->index = temp->next->index;
			temp->next->index = temp1;
			temp = (*exp);
		}
		else
			temp = temp->next;
	}
	temp = (*exp);
	while (temp != NULL)
	{
		ft_putstr_export(array[temp->index], 1);
		temp = temp->next;
	}
}

void	ft_sort_and_print_strings(char **array)
{
	int				i;
	unsigned char	j;
	t_export		*exp;

	i = 0;
	j = 0;
	exp = NULL;
	while (j < 128)
	{
		while (array[i] != NULL)
		{
			if (array[i][0] == j)
				ft_add_to_list_export(&exp, i);
			i++;
		}
		if (ft_listsize_export(&exp) == 1)
			ft_putstr_export((array[exp->index]), 1);
		else if (ft_listsize_export(&exp) > 1)
			ft_decide_what_print(array, &exp);
		j++;
		i = 0;
		if (exp != NULL)
			ft_free_list_export(&(exp));
		exp = NULL;
	}
}