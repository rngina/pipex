/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:33:28 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/09 19:02:07 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex_hd(t_pipex *pipex, char **argv, char **envp)
{
	int		i;
	char	*copy_limiter;

	set_path(envp, pipex);
	pipex->limiter = argv[2];
	i = ft_strchr(pipex->limiter, '\0');
	copy_limiter = pipex->limiter;
	pipex->limiter = (char *)malloc(sizeof(char) * (ft_strlen(copy_limiter) + 2));
	ft_memcpy(pipex->limiter, copy_limiter, i);
	pipex->limiter[i] = '\n';
	pipex->limiter[i + 1] = '\0';
	pipex->cmd1 = ft_split(argv[3], ' ');
	pipex->cmd2 = ft_split(argv[4], ' ');
	pipex->flag = 1;
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
		printf("%s   %s   %d\n", line, pipex->limiter, ft_strcmp(line, pipex->limiter));
		if (!(ft_strcmp(line, pipex->limiter)))
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
