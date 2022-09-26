/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:26:19 by ksura             #+#    #+#             */
/*   Updated: 2022/09/26 14:32:38 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_ms *ms, char **envp)
{
	t_ms_list	*tmp;
	size_t	len;
	
	len = 0;
	tmp = ms->tokenlist;
	if (b_pwd(ms->tokenlist->token, envp))
		return ;
	b_export(ms);
	b_unset(ms);
	while(tmp)
	{
		len = ft_strlen(tmp->token);
		if (b_env(tmp->token, ms) && len < 3)
		{
			tmp = tmp->next;
			break;
		}
		tmp = tmp->next;
	}
	return ;
}
