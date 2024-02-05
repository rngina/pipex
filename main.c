/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:01:12 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/05 18:53:28 by rtavabil         ###   ########.fr       */
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

int	openfile(char *file, int flag)
{
	if (flag == 0)
	{
		if (access(file, F_OK | R_OK))
		{
			perror(file);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC));
}

char	*make_command(char *path, char *argv)
{
	char	*command;
	int		i;
	int		j;

	command = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(argv) + 2));
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

char	*set_path_command_1(t_pipex *pipex)
{
	char	*pcmd1;
	char	**path_copy;

	path_copy = pipex->path;
	while (*(path_copy))
	{
		pcmd1 = make_command(*(path_copy), *(pipex->cmd1));
		if (access(pcmd1, F_OK) == 0)
		{
			return (pcmd1);
		}
		free(pcmd1);
		path_copy++;
	}
	if (access(*(pipex->cmd1), F_OK))
	{
		perror(*(pipex->cmd1));
	}
	return (*(pipex->cmd1));
}

char	*set_path_command_2(t_pipex *pipex)
{
	char	*pcmd1;
	char	**path_copy;

	path_copy = pipex->path;
	while (*(path_copy))
	{
		pcmd1 = make_command(*(path_copy), *(pipex->cmd2));
		if (access(pcmd1, F_OK) == 0)
		{
			return (pcmd1);
		}
		free(pcmd1);
		path_copy++;
	}
	return (*(pipex->cmd2));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		fd1;
	int		fd2;

	if (argc == 5)
	{
		fd1 = openfile(argv[1], 0);
		fd2 = openfile(argv[4], 1);
		if (fd1 == -1 || fd2 == -1)
			exit(1);
		pipex.cmd1 = ft_split(argv[2], ' ');
		pipex.cmd2 = ft_split(argv[3], ' ');
		set_path(envp, &pipex);
		pipex.path1 = set_path_command_1(&pipex);
		pipex.path2 = set_path_command_2(&pipex);
		printf("__________\n");
		printf("first command path %s\n", pipex.path1);
		printf("second command path %s\n", pipex.path2);
		printf("first fd %d\n", fd1);
		printf("second fd %d\n", fd2);
		printf("first command %s\n", *(pipex.cmd1));
		printf("second command %s\n", *(pipex.cmd2));
		free(pipex.path1);
		free(pipex.path2);
		free_path(&pipex);
		free_commands(&pipex);
	}
}

// int	main(p)
// {
// 	int	fd[2];
// 	int	x;
// 	int	id;

// 	if (pipe(fd) == -1)
// 	{
// 		printf("Pipe did not work correctly\n");
// 		return (1);
// 	}
// 	id = fork();
// 	if (id == 0)
// 	{
// 		scanf("%d", &x);
// 		close(fd[0]);
// 		write(fd[1], &x, sizeof(int));
// 		close(fd[1]);
// 	}
// 	else 
// 	{
// 		close(fd[1]);
// 		read(fd[0], &x, sizeof(int));
// 		printf("i got %d from a child\n", x);
// 		close(fd[0]);
// 	}
// }


//int main() {
//     // Define the path to the executable
//     char *programPath = "/usr/sbin/ifconfig";

//     // Create an array to hold the command-line arguments
//     char *args[] = {programPath, NULL};

//     // Use execve() to replace the current process image
//     if (execve(programPath, args, NULL) == -1) {
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }

//     // This code is not reached if execve() is successful

//     return 0;
// }
