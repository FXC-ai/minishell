/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 15:46:23 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(void)
{
	char    *line;
	
	signal_handler();
	while(42)
	{
		line = readline("$ ");
		add_history(line);
		lexer(line);
	}
	return (0);
}