/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura@student.42wolfsburg.de <ksura@studen +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:31:26 by kaheinz           #+#    #+#             */
/*   Updated: 2022/09/26 11:36:18 by ksura@student.42 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *command;

void	handler_quit(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\b\b\n", 1);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	
	struct	sigaction sa;
	pid_t	pid;
	t_ms	*ms;
	int	env_lst_size;

	(void) argc;
	(void) argv;
	pid = getpid();
	ft_printf("pid is %d\n", pid);
	ms = malloc(sizeof(t_ms));
	env_lst_size = creating_env_list(envp, ms);
	while (1)
	{
		ms->tokenlist = ft_tokennew("something", "first", 0);
		sa.sa_handler = &handler_quit;
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_IGN);
		command = readline("cli prompt >> ");
		if (command == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}			
		else if (command && *command)
		{
			b_exit(command);
			add_history(command);
			ms->lex = tokenice(command, ms->tokenlist, envp);
		}
		if (command)
			free (command);
		if (ms->lex.error == 0)
		{
			execute(ms->tokenlist, ms, envp);
			env_lst_size = b_export(ms, env_lst_size);
			env_lst_size = b_unset(ms, env_lst_size);
		}
			printing_tokens(ms->tokenlist);
		freeing_tokens(ms);
		// cmd_path = get_cmd_path(command, envp);
	}
	freeing_all(ms);
	free(command);
	free (ms);
	return 0;
}

int	creating_env_list(char **envp, t_ms *ms)
{
	int	i;
	t_env	*new;

	i = 0;
	while(envp[i])
	{
		new = ft_envvnew(envp[i]);
		ft_envvadd_back(&ms->env_list, new);
		i++;
        }
	return (i);
}
