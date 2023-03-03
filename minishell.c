/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:08:42 by corellan          #+#    #+#             */
/*   Updated: 2023/03/03 17:38:09 by corellan         ###   ########.fr       */
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
		if (ft_strncmp("exit\0", str, 5) == 0 || ft_strncmp("exit ", str, 5) == 0)
		{
			if (ft_wordcount_exit(str) > 1)
			printf("%d\n", ft_wordcount_exit(str));
		}
		printf("%s\n", str);
		free(str);
	}
	return (0);
}