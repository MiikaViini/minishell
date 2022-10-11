/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mviinika <mviinika@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 08:59:36 by mviinika          #+#    #+#             */
/*   Updated: 2022/10/11 13:23:43 by mviinika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
 #include <sys/stat.h>
# include <signal.h>
# include "../libft/libft.h"
# include <dirent.h>
# include <pwd.h>
# include <unistd.h>

# define MAX_VAR 1024
# define MAX_PATH 1024
# define MAX_LINE 4096

# define MSHELL "minishell"

# define E_EXE "error occured during execution"
# define E_NOTF "command not found"
# define E_NOTVAL "variable name must begin with a letter."
# define E_ARGNOTVAL "please enter arguments in format 'name=value'."
# define E_NOTALNUM "variable name must contain alphanumeric characters."
# define E_QUOT "invalid quoting, try again"
# define E_NOEX "no such file or folder"
# define E_NOPERM "permission denied"
# define E_NODIR "is not a directory"
# define E_NULLVAR "variable doesnt have a value"

typedef struct s_env
{
	char	**env;
	char	**path;
}			t_env;

int	check_exec(char **input, int rb, char **builtins, t_env *env);
int	do_echo(char **input, t_env *env);
size_t	ft_linecount(char **arr);
char	*user_expansion(char *input);
/*
**QUOTES
*/
int	is_single_quote(char c);
int	is_double_quote(char c);
int	is_quote(char c);
int	check_quotes(char *input);
int	is_expansion(char *str);

/*
**EXPANSIONS
*/
char	*replace_expansion(char *word, char **env, char *input);

/*
**PARSING
*/
char	**parse_input(char *input, char **env);
int	do_unsetenv(char **input, t_env *env);
int	do_setenv(char **input, t_env *env);
int do_env(char **input, t_env *env);
int do_cd(char **input, t_env *env);

int check_validity(char **input);
int check_equalsign(char *input);
char **get_path(char **env);
int	check_command(char **input, char **path, char **env);
void update_env(char **env, char *input, char *var);
char *dollar_expansion(char *expanded, char *word, char **env, int len);

/** MEMORY HANDLING **/
void	free_strarr(char **strarr);

void	error_print(char *word, char *command,char* e_msg);

typedef int	(*t_builtins)(char **input, t_env *env);

static const t_builtins g_builtins[6] = {
	do_echo,
	do_cd,
	do_setenv,
	do_unsetenv,
	do_env,
	NULL
};
#endif
