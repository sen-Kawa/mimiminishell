/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/10/15 09:57:42 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	freeing_tokens(t_ms *ms)
{
	t_ms_list	*temp;

	while (ms->tokenlist != NULL)
	{
		temp = ms->tokenlist;
		ms->tokenlist = ms->tokenlist->next;
		free(temp);
	}
}

void	freeing_all(t_ms *ms)
{
	t_env	*tenv;

	freeing_tokens(ms);
	while (ms->env_list != NULL)
	{
		tenv = ms->env_list;
		ms->env_list = ms->env_list->next;
		free(tenv);
	}
}

int	pipe_check(char *command, t_lex *lex, t_ms_list *tokens)
{
	if (command[lex->start + lex->i - 1] == '|'
		&& command[lex->start + lex->i - 2] == ' ')
	{
		tokens->section++;
		return (1);
	}
	else if (command[lex->start + lex->i - 1]
		== '|' && command[lex->start + lex->i - 2] != ' ')
	{
		lex->error = 2;
		return (1);
	}
	return (0);
}
/*
DESCRIPTION
Makes Nodes out of Commandline returned by readline

RETURN
void

PARAMETERS

EXTERNAL FUNCTIONS
ft_substr(), ft_tokennew(), ft_tokenaddback(), ft_strlen()
*/

t_lex	*tokenice(char *command, t_ms *ms)
{
	char		*part;
	t_ms_list	*newbe;
	t_lex		*lex;

	lex = malloc(sizeof(t_lex));
	ms->lex = lex;
	ms->lex->i = 0;
	ms->lex->start = 0;
	ms->lex->error = 0;
	ms->lex->length = ft_strlen(command);
	while (command[ms->lex->start] == ' ')
		ms->lex->start++;
	while (command[ms->lex->start + ms->lex->i] && *command)
	{
		if (ms->lex->start + ms->lex->i <= ms->lex->length)
		{
			if (command[ms->lex->start + ms->lex->i] == ' '
				|| command[ms->lex->start + ms->lex->i] == 124)
			{
				if (ms->lex->i > 0)
				{
					part = ft_substr(command, ms->lex->start, ms->lex->i);
					newbe = ft_tokennew(part, "space");
					ft_tokenadd_back(&ms->tokenlist, newbe);
				}
				if (command[ms->lex->start + ms->lex->i] == 124)
				{
					newbe = ft_tokennew("|", "space");
					ft_tokenadd_back(&ms->tokenlist, newbe);
					ms->lex->i++;
				}
				while (command[ms->lex->start + ms->lex->i] == ' ')
					ms->lex->i++;
				ms->lex->start = ms->lex->start + ms->lex->i;
				ms->lex->i = -1;
			}
			ms->lex = beforequotes(command, ms->lex, ms->tokenlist);
		}
		ms->lex = double_quotes(command, ms);
		ms->lex = single_quotes(command, ms);
		if (ms->lex->error == 1)
		{
			write(1, "ksh: syntax error, quotes missing\n", 35);
			return (ms->lex);
		}
		if (ms->lex->error == 2)
			write(1, "ksh: syntax error, space missing\n", 34);
		ms->lex->i++;
	}
	if (ms->lex->i > 0)
	{
		part = ft_substr(command, ms->lex->start, ms->lex->i);
		newbe = ft_tokennew(part, "space_before");
		ft_tokenadd_back(&ms->tokenlist, newbe);
	}
	sections(ms);
	dollarizing(ms);
	dollar_double(ms->tokenlist, ms);
	return (ms->lex);
}
/*

void	init_lex()
{

}*/
