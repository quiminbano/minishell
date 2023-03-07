/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hosr <hel-hosr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:15:56 by corellan          #+#    #+#             */
/*   Updated: 2023/03/07 16:11:43 by hel-hosr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_exit
{
	int	r;
	int	ret;
}	t_exit;

# include "libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/stat.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>

int			ft_wordcount_argc(char const *str);
int			ft_count_space(char const *str);
long long	ft_atoll(char const *str);
int			ft_am_i_valid_number(char const *str);
int			ft_am_i_a_number(char *str);
int			ft_line_checker(char *str, int *ret);
int			ft_check_symbols(char const *str);
int			ft_exit_check(char *str, int *ret);
void		handle_shortcuts(void);


#endif