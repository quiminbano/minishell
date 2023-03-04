/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:08:42 by corellan          #+#    #+#             */
/*   Updated: 2023/03/04 17:58:08 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_start(void)
{
	pid_t		pid;
	char		**str;
	extern char	**environ;

	str = ft_split("clear", ' ');
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		execve("/usr/bin/clear", str, environ);
	else
	{
		wait(NULL);
		ft_free_split(str);
		printf("Welcome to minishell. Developed by corellan and hel-hosr. ");
		printf("Hive Helsinki. 2023.\n");
	}
	return (0);
}

int	main(void)
{
	char	*str;
	t_exit	exit;

	if (ft_start() == 1)
		return (1);
	while (1)
	{
		str = readline("minishell$ ");
		exit.r = ft_line_checker(str, &(exit.ret));
		if (exit.r == 0)
			return (0);
		else if (exit.r == 1)
			return (exit.ret);
		else if (exit.r == 2)
			return (255);
		else if (exit.ret == 3)
			continue ;
		printf("%s\n", str);
		free(str);
	}
	return (0);
}