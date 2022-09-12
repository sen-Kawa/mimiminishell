/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksura <ksura@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:29:34 by ksura             #+#    #+#             */
/*   Updated: 2022/09/12 14:37:00 by kaheinz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	tokenice(char *command, t_ms_list *tokens)
{
	int	i;
	int	length;
	int	start;
	char *part;
	t_ms_list	*newbe;
	
	i = 0;
	start = 0;
	length = ft_strlen(command);
	printf("The Length is:%i", length);
	while (command[i] == ' ')
		i++;
	start = start + i;
	while(command[start + i] && *command)
	{
		if (start + i <= length)
		{
			if (command[start + i] == ' ')
			{
				while (command[start + i] == ' ')
					i++;
				part = ft_substr(command, start, i);
				newbe = ft_tokennew(part, NULL);
				// free(part);
				ft_tokenadd_back(&tokens, newbe);
				start = start + i;
				i = -1;
			}
		}
		i++;
	}
	part = ft_substr(command, start, i);
	newbe = ft_tokennew(part, NULL);
	// free(part);
	ft_tokenadd_back(&tokens, newbe);
}
