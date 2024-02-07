/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:01:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/07 12:30:11 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipex *pipex, char **argv, char **envp)
{
	pipex->infile_fd = openfile(argv[1], 0);
	pipex->outfile_fd = openfile(argv[4], 1);
	if (pipex->infile_fd == -1 || pipex->outfile_fd == -1)
		exit(1);
	dup2(pipex->infile_fd, STDIN_FILENO);
	dup2(pipex->outfile_fd, STDOUT_FILENO);
	set_path(envp, pipex);
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
}

void	first_process(int fd[2], t_pipex *pipex, char **envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
	if (*pid == 0)
	{
		pipex->path1 = set_path_command(pipex, 1);
		if (access(pipex->path1, F_OK))
			perror(pipex->path1);
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(pipex->path1, pipex->cmd1, envp);
			exit(1);
		}
	}
}

void	second_process(int fd[2], t_pipex *pipex, char **envp, int *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
	if (*pid == 0)
	{
		pipex->path2 = set_path_command(pipex, 2);
		if (access(pipex->path2, F_OK))
			perror(pipex->path2);
		else 
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			close(fd[0]);
			execve(pipex->path2, pipex->cmd2, envp);
			exit(1);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		fd[2];
	int		pid1;
	int		pid2;

	if (argc == 5)
	{
		init_pipex(&pipex, argv, envp);
		if (pipe(fd) == -1)
			return (1);
		first_process(fd, &pipex, envp, &pid1);
		if (pid1 != 0)
			second_process(fd, &pipex, envp, &pid2);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		if (pid1 != 0)
			waitpid(pid2, NULL, 0);
		free_all(&pipex);
	}
}
