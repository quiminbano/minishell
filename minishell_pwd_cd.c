/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:10:18 by hel-hosr          #+#    #+#             */
/*   Updated: 2023/03/10 15:41:52 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*	print working directory path
	print error if fail.
*/
int	ft_pwd(void)
{
	char	path[1024];

	if (getcwd(path, sizeof(path)))
		printf("%s\n",path);
	else
		perror("Path unavailable: ");
	return (3);
}

/*
	str = everything typed after "cd"
	path = it takes str, and if a space is found, everything after it is cut, as in the original cd
	if we have a space after the path and some other text after the space, cd would still work, taking 
	in consideration the path before the space.
	e.g in: cd ./desktop/application/ garbage text
	"garbage text" will be ignored and the path "./desktop/application/" will apply
*/
int	ft_cd(char *s, int i)
{
	char	*str;
	char	**path;

	str = ft_strdup(s + i + 3);
	path = ft_split(str, ' ');
	if (chdir(path[0]) == -1)
		printf("minishell: cd: %s: %s\n", path[0], strerror(errno));
	free(str);
	ft_free_split(path);
	return (3);
}