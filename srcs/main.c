/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/29 14:36:13 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int is_interactive = 0;

void disable_ctrl_chars()
{
    struct termios attributes;

    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

int	check_entry(char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (0);
	add_history(line);
	if (ft_strncmp(line, " ", ft_strlen(line)) == 0)
		return (0);
	return (1);
}

void	wait_for_input(char *env[])
{
	char    *line;
	signal_handler();
	while(42)
	{
		line = readline("$ ");
		//disable_ctrl_chars();
		if (line == NULL)
		{
			write(1, "exit\n", 5);
            break;
        }
		is_interactive = 1;
		if (check_entry(line))
		{
			lexer(line, env);
		}
		is_interactive = 0;
	}
}

int	main(int ac, char **argv, char *env[])
{
	struct termios		tm;
	(void) argv;
	(void) ac;
	
	
	
	int fd = open("debug2.log", O_WRONLY | O_APPEND);
	//ft_putstr_fd("gekjgekgfjkgfkfgjkhdfsjkhdfjdfsj\n", fd_debug);

	close(fd);




	if (tcgetattr(STDIN_FILENO, &tm) == -1)
		return (-1);
	tm.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tm) == -1)
		return (-1);
	wait_for_input(env);
	return (0);
}
