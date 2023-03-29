/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:31:55 by fcoindre          #+#    #+#             */
/*   Updated: 2023/03/29 17:36:06 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/header.h"

/*static int delimiter_parse(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

*/
/*static char *get_delimiter(char *str)
{
	int i;
	char    *result;
	int	tmp;

printf("STR %s\n", str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			
			i += 2;
			printf("STR %c", str[i]);
			while (str[i] && str[i] == ' ')
				i++;
			tmp = i;
			while (str[i] && str[i] != ' ')
				i++;
			result = malloc(i - tmp + 2);
			printf("%d\n", i - tmp + 1);
			i = tmp;
			tmp = 0;
			while (str[i] && str[i] != ' ')
				result[tmp++] = str[i++];
			result[tmp] = '\n';
			result[tmp + 1] = '\0';
			printf("RESULTdel[0] %s\n", result);
			return (result);
		}
		i++;
	}
	return (NULL);
}*/

void	execute_command(char **parsed_args, int in_fd, int out_fd, char *env[])
{
	if (fork() == 0)
	{
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		(void) env;
		
		//print_tab(parsed_args);
		//printf("parsed_args[0]%s\n", parsed_args[0]);
		execve(normalize_cmd(parsed_args[0], env), parsed_args, env);
		//execvp(parsed_args[0], parsed_args);
		perror(parsed_args[0]);
		exit(1);
	}
}

void	execute_command_2(char **parsed_args, int in_fd, int out_fd, char *env[])
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	execve(normalize_cmd(parsed_args[0], env), parsed_args, env);
	perror(parsed_args[0]);
	exit(1);
}

static int process_delimiter(char *del)
{
    char buffer[1024];
    ssize_t rdd;
    int fd;
    char *del_n = ft_strjoin(del, "\n");

    free(del);
    fd = open("TMPDOC", O_TRUNC | O_CREAT | O_WRONLY, 0777);

    rdd = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    while (rdd > 0)
    {
        buffer[rdd] = '\0';
		//printf("OK\n");
        if (ft_strcmp(del_n, buffer) == 0)
        {
			//printf("OK!\n");
            break;
        }
        write(fd, buffer, rdd);
        rdd = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
    }
    close(fd);
    fd = open("TMPDOC", O_RDONLY);
    unlink("TMPDOC");

    return fd;
}


int process_redirection(char *str, char *env[], int mode)
{
    int in_fd = STDIN_FILENO;
    int out_fd = STDOUT_FILENO;
    char **parsed_args;
	int	r;
    parsed_args = ft_split_lexer(str, ' ');
	
    char **current_command = parsed_args;
	print_tab(current_command);
    while (*parsed_args)
    {
		//printf("%s\n", *parsed_args);
        if (ft_strcmp(*parsed_args, ">") == 0)
        {
            *parsed_args = NULL;
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (in_fd == -1)
			{
				perror("open");
				return -1;
			}
            parsed_args++;
        }
        else if (ft_strcmp(*parsed_args, ">>") == 0)
        {
            *parsed_args = NULL;
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (in_fd == -1)
			{
				perror("open");
				return -1;
			}
            parsed_args++;
        }
        else if (ft_strcmp(*parsed_args, "<") == 0)
        {
            *parsed_args = NULL;
            in_fd = open(*(parsed_args + 1), O_RDONLY);
			
			if (in_fd == -1)
			{
				perror("open");
				return -1;
			}
            parsed_args++;
        }
        else if (ft_strcmp(*parsed_args, "<<") == 0)
        {
			//print_tab(parsed_args);

            *parsed_args = NULL;
			//print_tab((parsed_args + 1));
            in_fd = process_delimiter(*(parsed_args + 1));
			//current_command++;
			//printf("LINE %s\n", *(parsed_args + 1));
            parsed_args += 2;
        }
        else
        {
            parsed_args++;
        }
    }
	r = is_builtins(*current_command);
	if (r == 1)
		echo_process(current_command);
	else if (r == 2)
		cd_process(current_command);
	else if (r == 3)
		pwd_process(current_command);
	else if (r == 4)
		export_process(current_command, env);
	else if (r == 5)
		export_process(current_command, env);
	else if (r == 6)
		export_process(current_command, env);
	else if (r == 7)
		exit_process();
	else
	{
		print_tab(current_command);
		if (mode)
			execute_command(current_command, in_fd, out_fd, env);
		else
			execute_command_2(current_command, in_fd, out_fd, env);
	}
    	
    if (in_fd != STDIN_FILENO)
    {
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO)
    {
        close(out_fd);
    }
    wait(NULL);
    return (out_fd);
}