/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:33:28 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/12 15:38:33 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex_hd(t_pipex *pipex, char **argv, char **envp)
{
	set_path(envp, pipex);
	pipex->limiter = argv[2];
	pipex->cmd1 = ft_split(argv[3], ' ');
	pipex->cmd2 = ft_split(argv[4], ' ');
}

void	heredoc(t_pipex *pipex)
{
	int			fd;
	char		*line;
	static char	*buffer;

	fd = openfile(".heredoc_tmp", 2, pipex);
	if (fd < 0)
		heredoc_err();
	while (1)
	{
		write(1, "here_doc> ", 9);
		if (get_next_line(STDIN_FILENO, &line, &buffer) < 0)
			exit(1);
		if (!(ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter) + 1)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(buffer);
	close(fd);
	pipex->infile_fd = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile_fd < 0)
		heredoc_err();
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		pid1;
	int		pid2;

	if (argc == 6)
	{
		if (!(ft_strcmp(argv[1], "here_doc")))
		{
			init_pipex_hd(&pipex, argv, envp);
			heredoc(&pipex);
			unlink(".heredoc_tmp");
			dup2(pipex.infile_fd, STDIN_FILENO);
			pipex.outfile_fd = openfile(argv[5], 2, &pipex);
			dup2(pipex.outfile_fd, STDOUT_FILENO);
			process(&pipex, envp, &pid1, &pid2);
		}
	}
	else
	{
		ft_putstr_fd("Invalid number of arguments\n", STDOUT_FILENO);
		return (1);
	}
}
