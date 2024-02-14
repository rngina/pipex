/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:34:23 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/13 13:56:49 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fp(t_pipex *pipex, char **envp)
{
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execve(pipex->path1, pipex->cmd1, envp);
	exit(1);
}

void	sp(t_pipex *pipex, char **envp)
{
	dup2(pipex->fd[0], STDIN_FILENO);
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	execve(pipex->path2, pipex->cmd2, envp);
	exit(127);
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
		{
			if (errno == ENOENT)
			{
				ft_putstr_fd(*(pipex->cmd1), STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
			}
			else
				perror(pipex->path1);
		}
		else
			fp(pipex, envp);
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
			if (errno == ENOENT)
			{
				ft_putstr_fd(*(pipex->cmd2), STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
			}
			else
				perror(pipex->path2);
			pipex->exit_code = 127;
		}
		else
			sp(pipex, envp);
	}
}

void	process(t_pipex *pipex, char **envp, int *pid1, int *pid2)
{
	int	wstatus;

	wstatus = -1;
	if (pipe(pipex->fd) == -1)
		exit(1);
	if (!(pipex->no_infile))
		first_process(pipex, envp, pid1);
	if (*pid1 != 0)
		second_process(pipex, envp, pid2);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (pipex->flag == 1)
		unlink(".heredoc_tmp");
	free_all(pipex);
	waitpid(*pid1, NULL, 0);
	if (*pid1 != 0)
	{
		waitpid(*pid2, &wstatus, 0);
		if (WIFEXITED(wstatus))
		{
			exit(WEXITSTATUS(wstatus));
		}
	}
}

// void	process(t_pipex *pipex, char **envp, int *pid1, int *pid2)
// {
// 	int	wstatus;

// 	if (pipe(pipex->fd) == -1) {
// 		perror("pipe");
// 		exit(1);
// 	}

// 	first_process(pipex, envp, pid1);

// 	// Second process
// 	if (*pid1 != 0)
// 		second_process(pipex, envp, pid2);

// 	close(pipex->fd[0]);
// 	close(pipex->fd[1]);
// 	if (pipex->flag == 1)
// 		unlink(".heredoc_tmp");
// 	free_all(pipex);

// 	waitpid(*pid1, NULL, 0);
// 	if (*pid1 != 0) {
// 		waitpid(*pid2, &wstatus, 0);
// 		if (WIFEXITED(wstatus)) {
// 			exit(WEXITSTATUS(wstatus));
// 		}
// 	}
// }
