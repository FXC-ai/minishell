/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:39:34 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/06 18:00:15 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"






char **lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	int     i;

    i = 0;

	result = ft_split_lexer(str, c);
	if (result == NULL)
		return (0);
    while (result[i])
    {   
        cut_end_space(&(result[i]));
        i++;
    }

	normalize_with_space(result);

	parse_dollar(result, env);

    if (result[1] == NULL)
	{
		process_redirection(result[0], env, 1);
		return (0);
	}

	ms_pipe2(result,env);

	return (result);
}