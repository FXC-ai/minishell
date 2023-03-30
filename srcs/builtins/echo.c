/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:11:00 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/30 16:24:53 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void echo_process(char **current_command)
{
	int	i;
	int has_flag;
	i = 1;
	has_flag = 0;
	if (ft_strcmp(current_command[i], "-n") == 0)
	{
		has_flag = 1;
		i++;
	}
    while (current_command[i])
	{
		printf("%s ", current_command[i]);
		i++;
    }
    if (has_flag == 0) 
	{
        printf("\n");
    }
}