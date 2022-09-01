/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:36 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 19:08:16 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libraries/libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

# define BUFFER_S 100000
# define T_DATA_SIZE 7
# define T_DATA_HALF 3
# define FIRST_PROMPT "minishell-1.0$ "
# define LEXER_PROMPT "> "
# define METACHAR "|<>"
# define LOG_META "|&"
# define RED_META "<>"
# define HD_EXP "1\n"
# define HD_NOT_EXP "0\n"

extern void	*g_lob_ptr;

/**************************lexer struct********************************/
enum e_lexer_error
{
	ERR_SET_PTR = 1,
	ERR_SOLO_QUOTE,
	ERR_SYNTAX,
	ERR_SYNTAX_PIPE,
};

enum e_lexer_type_token
{
	TYPE_LEXER_WORD = 1,
	LEX_OP_LOGIC,
	LEX_OP_REDIR,
	LEX_SYNTAX_ERR
};

typedef struct s_lexer_token
{
	unsigned int	index;
	int				type;
	char			*start;
	char			*end;
	size_t			length;
}				t_lexer_token;

/***************************parsing struct****************************/
enum	e_parser_io_type
{
	IN_D = 1,
	HERE_D,
	PIPE_IN,
	OUT_D,
	OUT_D_APP,
	PIPE_OUT
};

enum	e_parser_cmd_type
{
	CMD_OUT,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXP,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT,
	CMD_ERR
};

typedef struct s_io
{
	int		type;
	char	*arg;
	int		fd;
	t_list	*stock;
	t_list	*here_buffer;
}				t_io;

typedef struct s_cmd
{
	int		type;
	int		size;
	char	**cmd_words;
	t_list	*cmd_lst;
}				t_cmd;

typedef struct s_splcmd
{
	t_io			in;
	t_io			out;
	t_cmd			cmd;
	struct s_splcmd	*next;
}	t_splcmd;

/*************************** main struct ****************************/
typedef struct s_data
{
	char			**env;
	char			**expt;
	char			*user_input;
	t_llist			*lexer;
	t_splcmd		*parser;
	int				*fds;
}t_data;

/************************ function proto *************************/

/**************** msh_data init *********************/
void		__set_msh_data(t_data *msh_data, char **envp);
void		__parser_update_status(t_data *msh_data, int status);

/*************** lexer *********************/
int			lexer_set_ptrs(char **start, char **end);
void		lexer_make(t_llist **lexer, char *str);
int			lexer_error(int error_id, t_lexer_token *current);
int			lexer_type_checker(t_llist **lexer_head, t_lexer_token *tmp_nod);

//void			lexer_add_history(t_llist *read_lst);
t_llist		*lexer(char *usr_input);

/*************** parser *********************/
t_splcmd	*__parser(t_llist *lexer, t_splcmd **parser);
int			__pars_io(t_io *in, t_io *out, t_llist *lexer);
t_list		*__get_stock(t_io *io, int type);
int			__pars_cmd(t_cmd *cmd, t_llist *lexer);
char		*__here_d_unquote_limit(char *arg);
void		__here_d_parse_lim(t_io *io);
void		__save_io_arg(t_io *io);

/*************** expander *******************/
t_splcmd	*__expand(t_splcmd *parser, char **env);
char		*__expand_string(char *str, char **env, int opt);
char		*__get_expand(char *start, int len, char **env);
char		*__is_expandable(char *str, char *quote_flag);
char		*__is_hd_expandable(char *str);
char		*__add_exp_to_str(char *str, char **start, char *end, char *expand);
void		__add_exp_split_str(char *str, int start, int len_expand);
char		**__cmdtab_init(t_list *cmd_lst);

/*************** imperator********************/
int			__los_bambinos_del_imperator(t_data *msh_data,
				t_splcmd *parser, int *fds, int left_size);
void		__join_path(char **env, t_cmd *cmd);
int			__imperial_open_files(t_splcmd *parser, int *in_fd, int *out_fd);
void		__imperial_open_heredoc(t_io *in, int *fds);
int			__imperial_redirect(t_splcmd *parser, int *fds, int fd_i);
int			__el_imperator(t_data *msh_data, t_splcmd *parser);

/*************** free *********************/
void		__ultimate_free(t_data *msh_data, int exit_opt, int bambinos);
void		__free_u_parse(t_data *msh_data);
void		__free_u_lexer(t_data *msh_data);
void		__free_u_user_input(t_data *msh_data);
void		__free_u_rl_history(t_data *msh_data);
void		lexer_free(t_llist **lexer);
void		t_llist_free(t_llist **lexer);
void		__t_list_free(t_list **lst);
void		__free_parse(t_splcmd **head);

/*********** signal ************/
void		__signal_handler(int sig);
void		__signal_handler2(int sig);
void		__signal_handler3(int sig);

/*********** builtins ************/

int			__echo_funk(t_data *msh_data, t_splcmd *parser, int opt);
int			__cd_funk(t_data *msh_data, t_splcmd *parser, int opt);
char		*__size_shifter(int size);
int			__pwd_funk(t_data *msh_data, t_splcmd *parser, int opt);
int			__export_funk(t_data *msh_data, t_splcmd *parser, int opt);
int			__export_var(char **args, t_data *msh_data);
char		**__add_var(char *var, char **tab, int opt);
int			__unset_funk(t_data *msh_data, t_splcmd *parser, int opt);
int			__env_funk(t_data *msh_data, t_splcmd *parser, int opt);
int			__check_syntax(char *var);
int			__get_env_size(char *env_size);
void		__execve_builtin(t_data *msh_data, t_splcmd *parser, int opt);

#endif
