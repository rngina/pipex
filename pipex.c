/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:34:23 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/12 16:07:52 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	first_process(t_pipex *pipex, char **envp, int *pid)
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
			dup2(pipex->fd[1], STDOUT_FILENO);
			close(pipex->fd[0]);
			close(pipex->fd[1]);
			execve(pipex->path1, pipex->cmd1, envp);
			exit(1);
		}
	}
}

void	second_process(t_pipex *pipex, char **envp, int *pid)
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
		{
			perror(pipex->path2);
			pipex->exit_code = 127;
		}
		else
		{
			dup2(pipex->fd[0], STDIN_FILENO);
			close(pipex->fd[1]);
			close(pipex->fd[0]);
			execve(pipex->path2, pipex->cmd2, envp);
			exit(127);
		}
	}
}

void	process(t_pipex *pipex, char **envp, int *pid1, int *pid2)
{
	int	wstatus;

	if (pipe(pipex->fd) == -1)
		exit(1);
	first_process(pipex, envp, pid1);
	waitpid(*pid1, NULL, 0);
	if (*pid1 != 0)
		second_process(pipex, envp, pid2);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (pipex->flag == 1)
		unlink(".heredoc_tmp");
	free_all(pipex);
	if (*pid1 != 0)
	{
		waitpid(*pid2, &wstatus, 0);
		if (WIFEXITED(wstatus))
		{
			exit(WEXITSTATUS(wstatus));
		}
	}
}
