/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:08:42 by corellan          #+#    #+#             */
/*   Updated: 2023/03/01 13:03:32 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*str;
	int		i;

	i = 0;
	while (1)
	{
		str = readline("minishell>> ");
		printf("%s\n", str);
		free(str);
		i = 0;
	}
	return (0);
}