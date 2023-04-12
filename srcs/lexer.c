/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:39:34 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/12 15:19:13 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	int     i;
	int		nbr_cmds;

    i = 0;

	result = ft_split_lexer(str, c);
	if (result == NULL)
		return ;
    while (result[i])
    {   
        cut_end_space(&(result[i]));
        i++;
    }

	normalize_with_space(result);
	
	//normalize_arguments_order(result);
	

	parse_dollar(result, env);

	parse_redirection_right(result);
	
	

    if (result[1] == NULL)
	{
		process_redirection(result[0], env, 1);
		//return (0);
	}
	else
	{
		nbr_cmds = size_tab(result);
		ms_pipe2(result, nbr_cmds, env);
	}
	//return (result);
}