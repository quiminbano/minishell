/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:09:21 by corellan          #+#    #+#             */
/*   Updated: 2023/03/09 18:28:16 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_custom_split("'hello");
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
	ft_free_split(array);
	return (0);
}
