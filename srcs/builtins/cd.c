/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/30 18:34:57 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void cd_process(char **parsed_args)
{
    if (parsed_args[1] == NULL) 
    {
        return;
    }
    else 
    {
        if (chdir(parsed_args[1]) != 0) 
        {
            perror("cd");
            return;
        }
    }
}