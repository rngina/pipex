/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:40:13 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/13 13:20:20 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <errno.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
	char	**path;
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
	char	*limiter;
	int		flag;
	int		exit_code;
	int		no_infile;
}		t_pipex;

int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	*ft_strcat(char *dest, char *src);
char	**ft_split(char *s, char c);
int		ft_strchr(char *s, int c);
char	*ft_substr(char *s, int start, int len);
void	*ft_memcpy(void *dest, void *src, int n);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s);

void	set_path(char **envp, t_pipex *pipex);
int		openfile(char *file, int flag, t_pipex *pipex);
char	*make_command(char *path, char *argv);
char	*set_path_command(t_pipex *pipex, int num);

void	free_all(t_pipex *pipex);
void	heredoc_err(void);

void	init_pipex(t_pipex *pipex, char **argv, char **envp);
void	first_process(t_pipex *pipex, char **envp, int *pid);
void	second_process(t_pipex *pipex, char **envp, int *pid);
void	process(t_pipex *pipex, char **envp, int *pid1, int *pid2);

int		get_next_line(int fd, char **line, char **buffer);

void	init_pipex_hd(t_pipex *pipex, char **argv, char **envp);
void	heredoc(t_pipex *pipex);
int		openfile_hd(char *file, int flag);

#endif