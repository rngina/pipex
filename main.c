/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:01:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/02 12:38:07 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	set_path(char **envp, t_pipex **pipex)
// {
// 	char	*buffer;

// 	buffer = NULL;
// 	if (envp != NULL)
// 	{
// 		while (*envp && buffer == NULL)
// 		{
// 			if (!ft_strncmp(*envp, "PATH=", 5))
// 				buffer = *envp + 5;
// 			envp++;
// 		}
// 	}
// 	if (buffer == NULL)
// 	{
// 		(*pipex)->path = NULL;
// 		return ;
// 	}
// 	(*pipex)->path = ft_split(buffer, ':');
// }

int	main()
{
	int	fd[2];
	int	x;
	int	id;
	
	if (pipe(fd) == -1)
	{		
		printf("Pipe did not work correctly\n");
		return (1);
	}
	id = fork();
	if (id == 0)
	{
		scanf("%d", &x);
		close(fd[0]);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else 
	{
		close(fd[1]);
		read(fd[0], &x, sizeof(int));
		printf("i got %d from a child\n", x);
		close(fd[0]);
	}
}
