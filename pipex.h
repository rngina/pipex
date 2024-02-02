/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:40:13 by rtavabil          #+#    #+#             */
/*   Updated: 2024/02/02 12:38:10 by rtavabil         ###   ########.fr       */
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

typedef struct s_pipex
{
	int		infile_fd;
	int		outfile_fd;
	char	**path;
	char	**cmd1;
	char	**cmd2;
}		t_pipex;

int		ft_strncmp(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *s);
char	**ft_split(char *s, char c);

void	ft_putstr_fd(char *s, int fd);

#endif