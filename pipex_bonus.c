/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:33:28 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/13 14:07:44 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex_hd(t_pipex *pipex, char **argv, char **envp)
{
	pipex->exit_code = 0;
	pipex->no_infile = 0;
	pipex->flag = 0;
	set_path(envp, pipex);
	pipex->limiter = argv[2];
	pipex->cmd1 = ft_split(argv[3], ' ');
	pipex->cmd2 = ft_split(argv[4], ' ');
}

int	hd(t_pipex *pipex, int *fd, char **buffer, char **line)
{
	char	*copy_line;
	int		i;

	write(1, "pipe heredoc> ", 15);
	if (get_next_line(STDIN_FILENO, line, buffer) < 0)
		exit(1);
	i = ft_strchr(*line, '\n');
	if (i != -1)
	{
		copy_line = ft_strdup(*line);
		copy_line[i] = '\0';
	}
	if (!(ft_strncmp(copy_line, pipex->limiter, ft_strlen(pipex->limiter) + 1)))
	{
		free(*line);
		free(copy_line);
		return (0);
	}
	write(*fd, *line, ft_strlen(*line));
	free(*line);
	free(copy_line);
	return (1);
}

void	heredoc(t_pipex *pipex)
{
	int			fd;
	char		*line;
	static char	*buffer;
	int			ret;

	fd = openfile(".heredoc_tmp", 2, pipex);
	if (fd < 0)
		heredoc_err();
	ret = 1;
	while (ret == 1)
		ret = hd(pipex, &fd, &buffer, &line);
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
			pid1 = -1;
			pid2 = -1;
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
