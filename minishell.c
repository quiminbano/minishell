/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:08:42 by corellan          #+#    #+#             */
/*   Updated: 2023/03/03 14:05:32 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_i_need_to_leave(void)
{
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (str != (void *)0 && ft_strlen(str) > 0)
			add_history(str);
		if (str == (void *)0)
		{
			ft_i_need_to_leave();
			exit(0);
		}
		printf("%s\n", str);
		free(str);
	}
	return (0);
}