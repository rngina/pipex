/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:09:18 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/06 16:13:15 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (fd > -1 && s)
	{
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
	}
}

void	free_path(t_pipex **pipex)
{
	char	**temp;
	int		i;

	temp = (*(pipex))->path;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

void	free_commands(t_pipex **pipex)
{
	char	**temp;
	int		i;

	temp = (*(pipex))->cmd1;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	temp = (*(pipex))->cmd2;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

void	free_all(t_pipex *pipex)
{
	//free(pipex->path1);
	free(pipex->path2);
	free_path(&pipex);
	free_commands(&pipex);
}
