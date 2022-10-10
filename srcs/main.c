/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:31:26 by kaheinz           #+#    #+#             */
/*   Updated: 2022/10/10 18:38:01 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"
//#include <sys/siginfo.h>


void	handler_quit(int sig, siginfo_t *info, void *ucontext)
{
		(void)info;
	t_ms	*ms;
	ms = (t_ms *)ucontext;
		ms->exit_status = 130;
//		ft_printf("sig info %i", info->si_value);
	if (sig == SIGINT)
	{
//	ft_printf("si status %i\n", info->si_code);
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\b\b\n", 1);
		rl_redisplay();
		ft_printf("exit %i\n", ms->exit_status);
		
	}
}

void	init(t_ms	*ms)
{
	ms->pipes_struct->fd_file[0] = -1;
	ms->pipes_struct->fd_file[1] = -1;
	ms->pipes_struct->fd_file[2] = -1;
	ms->pipes_struct->fd_file[3] = -1;
}

int	skip_space(char *command)
{
	int		i;

	i = 0;
	while (command[i] != 0 && (command[i] == ' ' || command[i] == '\t'))
		i++;
	if (command[i] == '\0')
		return (1);
	return (0);
}


int	main(int argc, char **argv, char **envp)
{
	struct	sigaction sa;
	char *command;
	pid_t	pid;
	t_ms	*ms;

	(void) argc;
	(void) argv;
	pid = getpid();
	ft_printf("pid is %d\n", pid);
	ms = malloc(sizeof(t_ms));
	ms->pipes_struct = malloc(sizeof(t_pipes));
	creating_env_list(envp, ms);
	while (1)
	{
	//	sa.sa_handler = &handler_quit;
		sa.sa_flags = SA_SIGINFO;
		sa.sa_sigaction = &handler_quit;
		sigaction(SIGINT, &sa, NULL);
//		pause();
		signal(SIGQUIT, SIG_IGN);
//		ft_printf("exit in loop %i\n", ms->exit_status); 
		command = readline("ksh >> ");
		init(ms);
		if (command == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}			
		else if (command && *command)
		{
			if (skip_space(command) == 0)
			{
				add_history(command);
				ms->lex = tokenice(command, ms, envp);
				 printing_tokens(ms->tokenlist);
				if (ms->lex->error == 0)
				{
					execution(ms);
					//printing_tokens(ms->tokenlist);
				}
					
				freeing_tokens(ms);
			}
		}
		if (command)
			free (command);
		if (ms->pipes_struct->fd_file[0])
			close(ms->pipes_struct->fd_file[0]);
		if (ms->pipes_struct->fd_file[1])
			close(ms->pipes_struct->fd_file[1]);
//		printing_tokens(ms->tokenlist);
//		freeing_tokens(ms);
	}
	freeing_all(ms);
	free(command);
	free (ms);
	return 0;
}

void	creating_env_list(char **envp, t_ms *ms)
{
	t_env	*new;

	ms->env_lst_size = 0;
	while(envp[ms->env_lst_size])
	{
		new = ft_envvnew(envp[ms->env_lst_size]);
		ft_envvadd_back(&ms->env_list, new);
		ms->env_lst_size++;
	}
}
