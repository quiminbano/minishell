/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:09:21 by corellan          #+#    #+#             */
/*   Updated: 2023/03/07 19:21:51 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_custom_split("Hola a todos \"Espero \\'se encuentren\" bien'");
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
	return (0);
}