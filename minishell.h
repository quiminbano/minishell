/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corellan <corellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 10:15:56 by corellan          #+#    #+#             */
/*   Updated: 2023/03/25 13:01:24 by corellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <sys/errno.h>
# define BUFFER 1024
# define NORM_START 0
# define RE_IN 1 // <
# define RE_OUT 2 // >
# define RERE_IN 3 // <<
# define RERE_OUT 4 // >>
# define PIPE 5 // |
# define IN_OUT 6 // <>

typedef struct s_lexer
{
	int				token;
	int				i_split;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_lex_i
{
	int	i;
	int	j;
}	t_lex_i;

typedef struct s_env
{
	char	**env;
	char	oldpwd[BUFFER];
	char	newpwd[BUFFER];
	int		level;
	int		flag;
	char	*new_str;
	int		set_f;
	int		exit_stts;
	int		is_inside;
}	t_env;

typedef struct s_sp_arg
{
	int		p;
	int		q;
	int		t;
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	temp;
}	t_sp_arg;

typedef struct s_args
{
	int				pos;
	struct s_args	*next;
}	t_args;

typedef struct s_export
{
	int				index;
	struct s_export *next;
}	t_export;

void		ft_copy_env(t_env *env, char **envp);
void		handle_shortcuts(void);
int 		handle_ctrlD(char *str, t_env *env);
void		collect_args(char *st, t_env *env);
void		handle_exlamation(t_env *env, char *st, int i);
char		*ft_strjoin_c(char *s1, char const c);
int			ft_wordcount_space(char const *str);
int			ft_find_word_array(char **array, char *needle);
int			ft_array_len(char **array);
long long	ft_atoll(char const *str);
int			ft_count_space(char *str);
int			ft_strlen_w_space(char const *str);
int			ft_am_i_valid_number(char const *str);
int			ft_am_i_a_number(char *str);
int			ft_line_checker(char *st, int *ret, t_env *env);
int			ft_error_pipe(char *str);
int			ft_check_symbols(char const *str);
int			ft_exit_check(char **array, char *str, int *ret, t_env *env);
char		**ft_custom_split(char const *s);
int			ft_check_single_quot(char const *str, int *i, int *j);
int			ft_check_double_quot(char const *str, int *i, int *j);
size_t		ft_len_single_quot(char const *s, size_t *st, t_sp_arg *sp);
size_t		ft_len_double_quot(char const *s, size_t *st, t_sp_arg *sp);
size_t		ft_count_char_arg(char const *str);
char		**ft_custom_split_free(char **array, size_t i);
size_t		ft_strlcpy_arg(char *d, char const *s, size_t size, t_sp_arg *sp);
int			check_char_now(const char *str, int i);
int			check_char_after(const char *str, int i);
int			ft_echo(char **array, t_env *env);
size_t		ft_wordcount_args(char const *str, t_args **args);
void		ft_add_to_list_args(t_args **begin, int num);
int			ft_listsize_args(t_args **lst);
void		ft_free_list_args(t_args **lst);
void		ft_print_list_args(t_args **a);
int			ft_pwd(t_env *env);
int			ft_cd(char **path, t_env *env);
int			ft_env(t_env *env, char **array);
void		ft_add_variables(t_env *env, char *variable);
void		ft_add_variables_copy_back(t_env *env, char **array, int i);
int			ft_export(t_env *env, char **array);
void		ft_add_to_list_export(t_export **begin, int num);
int			ft_listsize_export(t_export **lst);
void		ft_free_list_export(t_export **lst);
void		ft_decide_what_print(char **array, t_export **exp);
void		ft_sort_and_print_strings(char **array);
void		ft_putstr_export(char *st, int fd);
int			ft_check_first_variable(char *variable);
void		ft_print_list_export(t_export **a);
int			ft_unset(t_env *env, char **array);
char		*is_var_available(char *substr, t_env *env);
int			check_char(const char *str, int i);
int			ft_check_s_quot_lexer(char const *str, int *i);
int			ft_check_d_quot_lexer(char const *str, int *i);
size_t		ft_len_s_quot_lexer(char const *s, int i, int *flag);
size_t		ft_len_d_quot_lexer(char const *s, int i, int *flag);
void		ft_free_list_lexer(t_lexer **lst);
void		ft_add_to_list_lexer(t_lexer **begin, int num, int index);
int			ft_listsize_lexer(t_lexer **lst);
void		ft_print_list_lexer(t_lexer **a);
void		ft_tokens_recognition(char const *str, t_lexer **lex);
int 		ft_run_commands(char **cmd, t_env *env);
char		**ft_split_lexer(char const *s);
char		**ft_process_lexer(char **arg, char *str);

#endif