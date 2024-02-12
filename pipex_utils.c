/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:25:15 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/12 16:37:20 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_path(char **envp, t_pipex *pipex)
{
	char	*buffer;

	buffer = NULL;
	if (envp != NULL)
	{
		while (*envp && buffer == NULL)
		{
			if (!ft_strncmp(*envp, "PATH=", 5))
				buffer = *envp + 5;
			envp++;
		}
	}
	if (buffer == NULL)
	{
		pipex->path = NULL;
		return ;
	}
	pipex->path = ft_split(buffer, ':');
}

int	openfile(char *file, int flag, t_pipex *pipex)
{
	if (flag == 0)
	{
		if (access(file, F_OK | R_OK))
		{
			perror(file);
			pipex->flag = 1;
			pipex->exit_code = 1;
			return (open(".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0777));
		}
		pipex->flag = 0;
		return (open(file, O_RDONLY));
	}
	else if (flag == 1)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777));
	pipex->flag = 1;
	return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0777));
}

char	*make_command(char *path, char *argv)
{
	char	*command;
	int		i;
	int		j;

	command = (char *)malloc(sizeof(char) * (ft_strlen(path) \
	+ ft_strlen(argv) + 2));
	i = 0;
	while (path[i])
	{
		command[i] = path[i];
		i++;
	}
	command[i] = '/';
	i++;
	j = 0;
	while (argv[j] != '\0')
	{
		command[i + j] = argv[j];
		j++;
	}
	command[i + j] = '\0';
	return (command);
}

char	*set_path_command(t_pipex *pipex, int num)
{
	char	*pcmd;
	char	**command_copy;
	char	**path_copy;

	command_copy = pipex->cmd1;
	if (num == 2)
		command_copy = pipex->cmd2;
	path_copy = pipex->path;
	while (*(path_copy))
	{
		pcmd = make_command(*(path_copy), *(command_copy));
		if (access(pcmd, F_OK) == 0)
			return (pcmd);
		free(pcmd);
		path_copy++;
	}
	return (*(command_copy));
}

void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->exit_code = 0;
	pipex->infile_fd = openfile(argv[1], 0, pipex);
	pipex->outfile_fd = openfile(argv[4], 1, pipex);
	if (pipex->infile_fd == -1 || pipex->outfile_fd == -1)
		exit(1);
	dup2(pipex->infile_fd, STDIN_FILENO);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	set_path(envp, pipex);
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->limiter = NULL;
}
