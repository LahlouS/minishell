/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slahlou <slahlou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:13:14 by lchan             #+#    #+#             */
/*   Updated: 2022/08/08 13:17:11 by slahlou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	*g_lob_ptr;

void	__init_msh(t_data *msh_data)
{
	errno = 0;
	msh_data->log_fd = 0;
	msh_data->fds = NULL;
	//msh_data->last_status = ft_strdup("0");
	msh_data->env = NULL;
	msh_data->expt = NULL;
	msh_data->user_input = NULL;
	msh_data->lexer = NULL;
	msh_data->parser = NULL;
}

void	__init_expt(t_data *msh_data)
{
	msh_data->expt = ft_calloc(sizeof(char *), 2);
	if (msh_data->expt)
		*msh_data->expt = ft_calloc(sizeof(char), 2);
	msh_data->expt++;
	*(msh_data->expt) = NULL;
}

void	__init_env(t_data *msh_data, char **envp)
{
	int		envp_size;
	char	**env;

	envp_size = (ft_strtablen(envp) + 1);
	env = ft_calloc(sizeof(char *), envp_size + 2);
	if (env)
	{
		*env = ft_calloc(sizeof(char), 2);
		if (*env)
		{
			*(*(env + 0) + 0) |= envp_size;
			*(*(env + 0) + 1) |= envp_size >> 8;
		}
		env++;
		*(env) = ft_strdup("?=0");
		env++;
		while(*envp)
		{
			*(env) = ft_strdup(*(envp));
			env++;
			envp++;
		}
		*env = NULL;
	}
	msh_data->env = env - envp_size;
}

void	__set_msh_data(t_data *msh_data, char **envp)
{
	__init_msh(msh_data);
	__init_env(msh_data, envp);
	__init_expt(msh_data);
}






/*******************************************************************/

char	*__readline_add_history(t_data *msh_data, char *prompt)
{
	char	*usr_input;

	usr_input = NULL;
	while (!usr_input)
	{
		usr_input = readline(prompt);
		if (!usr_input)
		{
			write(1, "exit\n", 5);
			__ultimate_free(msh_data, 0, 1);
		}
		else if (!*usr_input)
			ft_free_char(&usr_input);
	}
	add_history(usr_input);
	return (usr_input);
}

void	__signal_handler3(int sig)
{
	if (sig == SIGINT)
	{
		__ultimate_free((t_data *)g_lob_ptr, 0, 0);
		exit(0);
	}
}

void	__signal_handler2(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
}

void	__signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main (int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	(void) envp;
	t_data			msh_data;

	signal(SIGINT, &__signal_handler);
	__set_msh_data(&msh_data, envp);
	g_lob_ptr = &msh_data;
	while (1)
	{
		msh_data.user_input = __readline_add_history(&msh_data, FIRST_PROMPT);
		msh_data.lexer = lexer(msh_data.user_input);
		msh_data.parser = __parser(msh_data.lexer, &msh_data.parser);
		//msh_data.parser = __parser(msh_data.lexer);

		msh_data.parser = __expand(msh_data.parser, msh_data.env);

		__el_imperator(&msh_data, msh_data.parser);
		//__visual_print_splcmd(msh_data.parser, msh_data.lexer);
		__ultimate_free(&msh_data, T_DATA_HALF, 0);
	}
	__ultimate_free(&msh_data, 0, 0);
}

// lier builtin et child --> done DONE
// unset doit ausssi unset dans l export DONE
// fermer fd 0 et 1 dans les childs apres les avoir dup DONE

// message d'erreur doivent tous imprimer dans strerr
// unset : voir si on peut utiliser la meme fonction check syntax que export DONE

// relecture
// test
// norme
//push














/****************** visual ******************/
 		//__visual_print_splcmd(msh_data.parser, msh_data.lexer);
		//printf("msh_data->last_status = %s\n", msh_data.last_status);

//<$USER >$_ <infile >$""USER cmd1 cmd2$USER | $$"|"   "|"       $'"USER"' $"'$USER'" | cat -eaf -qwe $USER


/*
//test'$USER' $"USER" $'USER' "$USER" $ "'$USER'" "$'USER'" $$$USER $"$'USER" "$$$USER" '$$$USER' $"$USER'''" --> input
//test$USER USER USER slahlou $ 'slahlou' $'USER' 474255slahlou $'USER 474255slahlou $$$USER slahlou''' --> bash output
//
// erreur sur :
// $'USER'
// "'$USER'"$;
// "$'USER'"
// ""$"U'S'ER'$',,,$USER$$'U'SR" --> input
// U'S'ER'$',,,slahlou474255'U'SR  --> bash output
// """U'S'ER'$',,,slahlou$$'U'SR" --> minishell output //seems OK
// "$'USER', U S E'$'R :$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$" --> input
// $'USER', U S E'$'R :$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$ --> bash output
// "$'USER', U S E'$'R :$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$'$" --> minishell output //seems OK
// $"$'USER" -->input
// $'USER -->bash output
// $'USER -->  minishell output //seems OK
// $2USER
// $2USER$2USER
// $2USER'$2USER'
// $$"USER"
*/


//wdljfskv;.`1@;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;.wE/
//valgrind --trace-children=yes --track-fds=yes --suppressions=sup_rl_error ./minishell < /dev/urandom
//valgrind --trace-children=yes --track-fds=yes --suppressions=sup_rl_error --show-leak-kinds=all ./minishell < /dev/urandom

// {
//    ignore_libreadline
//    Memcheck:Leak
//    ...
//   obj:/usr/lib/x86_64-linux-gnu/libreadline.so.8.0
// }

// {
//    leak readline
//    Memcheck:Leak
//    match-leak-kinds: reachable
//    ...
//    fun:readline
// }

// {
//    leak history
//    Memcheck:Leak
//    match-leak-kinds: reachable
//    ...
//    fun:add_history
// }
